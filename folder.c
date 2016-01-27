//==========================================================================\
// folder.c : gestisce la listbox di selezione dei folder                   |
// int SetPath(PFILESPECS pfsp);                                            |
// VOID FillDirList(HWND hwnd, PATTMAN pam);                                |
// VOID QueryCurrentPath(PSZ pszPath, PSZ pszFile);                         |
// VOID ProcessFolderSelection(HWND hwnd, MPARAM mp1, PATTMAN pam);         |
// BOOL SetTempPath(PSZ pszTmpPath);                                        |
//==========================================================================/

#define INCL_WIN
#define INCL_DOSFILEMGR
#define INCL_DOSMISC
#include <os2.h>
#include <listbox.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"


//==========================================================================\
// imposta la directory di lavoro secondo l'argomento introdotto            |
// assegna a pszFile il nome del file o '\' se l'argomento Š una directory  |
// parametri:                                                               |
// PSZ pszPath = nome del nuovo path                                        |
// PSZ pszFile = nome del file                                              |
// PFILESTATUS3 pfs = puntatore s struttura informazioni file               |
// risultato:                                                               |
// int rc = TRUE in caso di errore, FALSE in caso di successo               |
//==========================================================================/

int SetPath(PFILESPECS pfsp) {
   char* slash;
   char* cursor = pfsp->pszPath;

   pfsp->fs.attrFile = FILE_DIRECTORY;
   // se manca aggiunge slash dopo lettera drive
   if (pfsp->pszPath[2] != '\\') {
      char newCh = '\\'; char swap; cursor += 2;
      do {swap = *cursor; *cursor = newCh; newCh = swap;} while (*cursor++);
      cursor = pfsp->pszPath;
   } /* endif */

   // determina se l'argomento Š file o directory
   if (pfsp->pszPath[3]) { // se non Š solo [D:\] trova ultimo "\" di pszPath
      while (*cursor) {if (*cursor == '\\') slash = cursor; ++cursor;}
      if (isWildCh(slash)) { // se ci sono caratteri jolly assume sia un file
         pfsp->fs.attrFile = 0;
      } else {
         if (*(slash + 1)) { // controlla che non ci sia slash finale
            if (DosQueryPathInfo(pfsp->pszPath, FIL_STANDARD,
                                 (PVOID)&pfsp->fs, sizeof(FILESTATUS3)))
               return 1;
         } else { // se c'Š uno slash finale Š sicuramente una directory
            *slash = 0;
         } /* endif */
      } /* endif */
   } /* endif */

   // separa nome file e directory
   if (pfsp->fs.attrFile & FILE_DIRECTORY) {    // se directory mette come
      pfsp->pszFile[0] = '\\'; pfsp->pszFile[1] = 0;      // nome file "\"
   } else {
      sstrcpy(pfsp->pszFile, slash + 1);                // ricava nome file
      if (slash == &pfsp->pszPath[2]) *++slash = 0;
      else *slash = 0;
   } /* endif */

   if (DosSetCurrentDir(pfsp->pszPath))           // cambia directory
      return 1;
   return 0;
}


//==========================================================================\
// ottiene la lista delle directory presenti e riempie la list box          |
// parametri:                                                               |
// HWND hwnd      = handle della finestra principale                        |
// PSZ pszPath    = path completo                                           |
// PUSHORT pusDir = indice directory corrente nella listbox                 |
// BOOL extsel    = TRUE selez estesa, FALSE selez singola                  |
// BOOL dir       = TRUE selez tutti i file solo se argomento = directory   |
// PSZ pszFile    = nome file corrente ('\' = file_directory)               |
//==========================================================================/

VOID FillDirList(HWND hwnd, PATTMAN pam) {
   APIRET  rc     = 0 ;
   HDIR    hDir   = HDIR_CREATE;
   FILEFINDBUF3 fBuf  ;
   ULONG   ulSC   = 1 ;
   PSZ pszDir = pam->fsp.pszPath;   // nome delle singole directory del path
   PSZ pszCur = pam->fsp.pszPath;   // puntatore alla stringa fileSpecs
   SHORT idx = 0;                   // indice item inserito
   char swap;

   MyDlgLboxDeleteAll(hwnd, LB_FOLDER);            // svuota la listbox PATH
   MyDlgLboxDeleteAll(hwnd, LB_FILE);              // svuota la listbox file
   
   // inserisce item corrispondente alla lettera del drive
   pszCur += 3;
   swap = *pszCur;
   *pszCur = 0;
   pam->fsp.currDir = 0;
   DlgLboxInsertItem(hwnd, LB_FOLDER, LIT_FIRST, pszDir);
   *pszCur = swap;
   pszDir = pszCur;

   while (*pszCur) {            // per ogni directory facente parte del path
      if (*pszCur == '\\') {    // crea un item incrementando indent e
         *pszCur = 0;
         pam->fsp.currDir++;
         DlgLboxInsertItem(hwnd, LB_FOLDER, LIT_END, pszDir);
         *pszCur++ = '\\';
         pszDir = pszCur;
      } /* endif */
      ++pszCur;
   } /* endwhile */
   if (*pszDir) {
      pam->fsp.currDir++;
      DlgLboxInsertItem(hwnd, LB_FOLDER, LIT_END, pszDir);
   } // end if
   MyDlgLboxSelectItem(hwnd, LB_FOLDER, pam->fsp.currDir);//selez dir corrente
   pam->fsp.sPrvDir = pam->fsp.currDir;              // memorizza dir corrente
   // riempie la lista dei file e delle directory
   rc = DosFindFirst("*", &hDir, ANYFILE, &fBuf,
                     sizeof(fBuf), &ulSC, FIL_STANDARD);
   while (!rc) {
      if (sstrcmp(fBuf.achName, "..")) {
         if (fBuf.attrFile & FILE_DIRECTORY &&
             !(fBuf.achName [0] == '.' && !fBuf.achName [1])) {
            DlgLboxInsertItem(hwnd, LB_FOLDER, LIT_END, fBuf.achName);
         // inserimento file
         } else {
            idx = DlgLboxInsertItem(hwnd, LB_FILE, LIT_SORTASCENDING,
                                    fBuf.achName);
            // determina se il file deve essere selezionato :
            // directory con opzione sel automatica tutti i file (tranne ".")
            if (pam->pro.sel.extsel && pam->pro.sel.dir &&
                pam->fsp.pszFile[0] == '\\' &&
                !(fBuf.achName[0] == '.' && !fBuf.achName[1])) {
               MyDlgLboxSelectItem(hwnd, LB_FILE, idx);
            // Š una dir ma senza selez automatica x cui seleziona solo "."
            } else if (pam->fsp.pszFile[0] == '\\' &&
                       fBuf.achName[0] == '.' && !fBuf.achName[1]) {
               MyDlgLboxSelectItem(hwnd, LB_FILE, idx);
            // Š stato specificato il nome di un file o Š dir ma non Autosel
            } else if (WildCmp(pam->fsp.pszFile, fBuf.achName)) {
               MyDlgLboxSelectItem(hwnd, LB_FILE, idx);
            } /* endif */
         } /* endif */
      } /* endif */
      rc = DosFindNext (hDir, &fBuf, sizeof fBuf, &ulSC);
   } // end while
   DosFindClose(hDir);
   ProcessFileSelection(hwnd, pam);
}


//==========================================================================\
// Imposta pszPath e pszFile secondo i dati della directory corrente        |
//==========================================================================/

VOID QueryCurrentPath(PSZ pszPath, PSZ pszFile) {
   ULONG drive;
   ULONG ulSize;

   DosQueryCurrentDisk(&drive, &ulSize);
   *pszPath++ = drive + 'A' - 1;
   *pszPath++ = ':';
   *pszPath++ = '\\';
   ulSize = 253;
   DosQueryCurrentDir(0, pszPath, &ulSize);
   if (pszFile != NULL) {
      *pszFile++ = '\\';
      *pszFile = 0;
   } /* endif */
}


//==========================================================================\
// elaborazione conseguente alla selezione di un folder                     |
//==========================================================================/

VOID ProcessFolderSelection(HWND hwnd, MPARAM mp1, PATTMAN pam) {
   SHORT currIdx, i;

   currIdx =  DlgLboxQuerySelectedItem(hwnd, LB_FOLDER);  // dir selezionata
   i = currIdx;
   if (pam->LMsel) return;  // se la selezione deriva da un altro messaggio
   if (!isChanged(hwnd, pam)) {
      if (i < pam->fsp.currDir) {      // se una dir gerarchicamente superiore
         sstrcpy(pam->fsp.pszPath, "..");      // aggiunge "\.." tante volte
         while (++i < pam->fsp.currDir) {      // fino ad arrivare alla nuova
            sstrcat(pam->fsp.pszPath, "\\.."); // dir selezionata
         } /* endwhile */
      } else {                  // altrimenti ricava il nome nuova dir
         DlgLboxQueryItemText(hwnd, LB_FOLDER, currIdx, pam->fsp.pszPath, 256);
      } /* endif */
      pam->fsp.psSel[1] = -2;          // forza aggiornamento dati
      DosSetCurrentDir (pam->fsp.pszPath); // si sposta nella nuova dir
      QueryCurrentPath(pam->fsp.pszPath, pam->fsp.pszFile);//scrive nuovo path
      FillDirList(hwnd, pam);          // riempie la list box dei folder
   } else {                            // riseleziona directory precedente
      MyDlgLboxSelectItem(hwnd, LB_FOLDER, pam->fsp.sPrvDir);
   } /* endif */
}


//==========================================================================\
// crea directory temporanea                                                |
// PSZ pszTmpPath contiene inizialmente il path completo dell'applicazione  |
//                al termine contiene path dir temporanea                   |
// valore restituito:                                                       |
// TRUE = successo, FALSE = errore                                          |
//==========================================================================/

BOOL SetTempPath(PSZ pszTmpPath) {
   int i = -9999999;
   PSZ pszEnv;
   HDIR    hDir   = HDIR_CREATE;
   FILEFINDBUF3 fBuf  ;
   ULONG   ulSC   = 1 ;

   // cerca dir %temp% o %tmp% se non trova nessuno delle 2 usa dir corrente
   if ((!DosScanEnv("TMP", &pszEnv) || !DosScanEnv("TEMP", &pszEnv)) && 
       !DosFindFirst(pszEnv, &hDir, ANYFILE, &fBuf,         // %TMP% esiste?
                     sizeof(fBuf), &ulSC, FIL_STANDARD)) {
      sstrcpy(pszTmpPath, pszEnv);
   } else {
      PSZ pszCur;
      pszEnv = pszTmpPath;
      while (*pszEnv) {
         if (*pszEnv == '\\') pszCur = pszEnv;
         pszEnv++;
      } /* endwhile */
      *pszCur = 0;
   } // end if
   pszEnv = pszTmpPath;  // crea dir temp in pam->pszTmpPath
   while (*pszEnv++);         // aggiunge slash finale
   *(pszEnv - 1) = '\\';
   do {             // loopa finch‚ non riesce a creare directory
      i2str(i++, pszEnv); 
   } while (DosCreateDir(pszTmpPath, NULL) && i < 0); /* enddo */
   return (i != 0);
}
