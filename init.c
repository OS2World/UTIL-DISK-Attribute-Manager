//==========================================================================\
// init.c : funzioni parsing argomenti, lettura file INI e inizializzazione |
// finestra dialogo                                                         |
// int ParseArgs(int argc, char** argv, PATTMAN pam);                       |
// MRESULT InitDlg(HWND hwnd, PATTMAN pam);                                 |
//==========================================================================/

#define INCL_WIN
#define INCL_DOSFILEMGR
#define INCL_DOSMISC
#include <os2.h>
#include <stdlib.h>
#include <mledlg.h>
#include <EFDlg.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"


//==========================================================================\
// controlla gli argomenti, memorizzando il nome del file INI in            |
// "pam->pszProfile", se Š specificato un file o directory come parametro   |
// si sposta nel path specificato, se tale path corrisponde ad un drive     |
// inesistente visualizza una message box "drive not ready" e restituisce   |
// 1 se in tale MsgBox si preme "Abort"                                     |
// int argc    = numero argomenti                                           |
// char** argv = puntatore ad array di stringhe argomenti                   |
// PATTMAN pam = puntatore alla struttura ATTMAN                            |
//==========================================================================/

int ParseArgs(int argc, char** argv, PATTMAN pam) {

   pam->fsp.pszFile[0] = 0;  // x riconoscere in seguito validit… argomenti
   // ottiene percorso completo eseguibile (usa pszTmpPath temporaneamente)
   DosQueryPathInfo(argv[0], FIL_QUERYFULLNAME, (PVOID)pam->pszTmpPath, 256);
   GetDefaultProfile(pam->pszTmpPath, pam->pszProfile); //nome ini default
   if (!SetTempPath(pam->pszTmpPath)) {       // crea dir temporanea
      PMPrint(HWND_DESKTOP, ERR_TMP_DIR);
      return 1;
   } // end if
   for (++argv; argc > 1; argc--, argv++) {         
      if ((**(argv) == '-' || **(argv) == '/') &&   // file ini alternativo
          (*(*argv + 1) == 'P' || *(*argv + 1) == 'p')) {
         DosQueryPathInfo(*argv + 2, FIL_QUERYFULLNAME,
                          (PVOID)pam->pszProfile, 256);
      } else {                                      // argomento nomefile
         if (*(*argv + 1) == ':') {                 // se specifica drive
            sstrcpy(pam->fsp.pszPath, *argv);
            if (SetDisk(HWND_DESKTOP, **argv, &pam->fsp.hpfs)) {
               QueryCurrentPath(pam->fsp.pszPath, pam->fsp.pszFile);
               return 0;
            } /* endif */
            if (SetPath(&pam->fsp))        // imposta nuova dir di lavoro
               PMPrint(HWND_DESKTOP, PSZ_INVARGS);
         } else {
            DosQueryPathInfo(*argv, FIL_QUERYFULLNAME,
                             (PVOID)pam->fsp.pszPath, 256);
            if (SetPath(&pam->fsp))        // imposta nuova dir di lavoro
               PMPrint(HWND_DESKTOP, PSZ_INVARGS);
         } // endif
      } // endif
   } /* endfor */
   return 0;
}


//==========================================================================\
// inizializzazione dialogo                                                 |
// Parametri:                                                               |
// HWND hwnd       = handle finestra principale                             |
// PATTMAN pam     = puntatore struttura dati generali programma            |
//==========================================================================/

MRESULT InitDlg(HWND hwnd, PATTMAN pam) {
   SWP minSwp;
   HWND hTmp;                 // handle temporaneo usato per il subclassing
   PFNWP pfnwpOld;            // procedura default controllo da subclassare

   WinSetWindowPtr(hwnd, QWL_USER, pam);
   // inizializza array pam->fsp.psSel a dimensione 1 valore -1
   if ((pam->fsp.psSel = malloc(4000)) == NULL) {
      PMPrint(HWND_DESKTOP, ERR_ALLOC_SELFILES);
      ProcessTermination(hwnd, FALSE);
      return (MRESULT)FALSE;
   } /* endif */
   pam->fsp.psSel[0] = -1; pam->fsp.psSel[1] = -3;
   // alloca array swp controlli finestra principale
   if ((pam->pro.gen.pswp = malloc((size_t)(32 * sizeof(SWP)))) == NULL) {
      PMPrint(HWND_DESKTOP, ERR_ALLOC_SWPARRAY);
      ProcessTermination(hwnd, FALSE);
      return (MRESULT)FALSE;
   } // endif  --- imposta flag usata in EnableBrowsing x determinare se Š la
   pam->pro.gen.pswp[24].y = 0; // prima occorrenza di browse mode
   // rileva formato data e separatori data e ora
   GetDateTimePref(&pam->fsp);
   // carica in memoria le icone
   pam->hIco = WinLoadPointer(HWND_DESKTOP, 0, MAIN_ICON);
   pam->hOpen = WinLoadPointer(HWND_DESKTOP, 0, FLD_OPEN);
   pam->hClose = WinLoadPointer(HWND_DESKTOP, 0, FLD_CLOSE);
   WinSendMsg(hwnd, WM_SETICON, (MPARAM)pam->hIco, NULL);
   //carica in memoria il menu
   pam->hMMain = WinLoadMenu(HWND_OBJECT, 0, MENU_MAIN);
   pam->hMEdit = WinLoadMenu(HWND_OBJECT, 0, MENU_EDIT);
   // setta lo stile di Import e Report a MS_CONDITIONALCASCADE
   SetMenuCondCascadeStyle(pam->hMMain, SUBMN_REPORT);
   SetMenuCondCascadeStyle(pam->hMEdit, SUBMN_REPORT);
   SetMenuCondCascadeStyle(pam->hMEdit, SUBMN_IMPORT);
   // imposta le scelte di default di import e report
   SetMenuDefaults(pam->hMEdit, SUBMN_REPORT, pam->pro.rep.repmode, pam->pro.rep.repmode);
   SetMenuDefaults(pam->hMMain, SUBMN_REPORT, pam->pro.rep.repmode, pam->pro.rep.repmode);
   SetMenuDefaults(pam->hMEdit, SUBMN_IMPORT, pam->pro.imp.def_imp, pam->pro.imp.def_imp);
   // abilita-disabilita le varie voci del menu di importazione
   EnableImportMenuItems(hwnd, pam, &pam->pro);
   // subclassa il titolo della finestra
   Subclass(hwnd, FID_TITLEBAR, NewTitleWinProc);
   // subclassa l'entryfield subject
   Subclass(hwnd, EF_SUBJ, NewEFWinProc);
   // procedura speciale per la listboxfile
   SubclassFileList(hwnd, pam, FileBoxWinProc);
   pam->sMenuFrom = TRUE; // x fare rilevare WM_MOUSEMOVE alla proc subcassate
   // setta il limite del campo immissione subject
   SetSubjectLimit(hwnd, pam->pro.gen.subj);
   // cambia lo stile delle varie finestre secondo se readonly o edit mode
   SwitchEditMode(hwnd, pam->pro.gen.ronly, pam);
   // setta un nuovo font memorizzandone la massima larghezza e altezza
   SetDialogFont(hwnd, &pam->pro.gen, TRUE);
   // resetta l'attrib di selezione estesa della Lbox File
   SwitchSelectionMode(hwnd, pam->pro.sel.extsel);
   // setta lo stile della listbox folder a LS_OWNERDRAW
   WinSetWindowBits(WinWindowFromID(hwnd, LB_FOLDER), QWL_STYLE,
                                    LS_OWNERDRAW, LS_OWNERDRAW);
   // abilita o disabilita il modo di browsing
   EnableBrowsing(hwnd, pam, (pam->pro.sel.browse && (!pam->pro.sel.browsedir ||
                  (pam->pro.sel.browsedir && pam->fsp.pszFile[0] == '\\'))));
   // mostra finestra princip programma (dimens settate in EnableBrowsing())
   WinSetWindowPos(hwnd, HWND_BOTTOM, pam->pro.swp.x, pam->pro.swp.y, 0, 0,
                   SWP_MOVE | SWP_SHOW);
   // se non si Š introdotto un nome file valido come argomento
   if (!*pam->fsp.pszFile) {
      // se si Š scelto di reimpostare la precedente dir di lavoro
      // e il drive della precedente dir Š valido
      if (pam->pro.gen.lastPath[0] &&
         !SetDisk(HWND_DESKTOP, pam->pro.gen.lastPath[0], &pam->fsp.hpfs)) {
         sstrcpy(pam->fsp.pszPath, pam->pro.gen.lastPath); // copia prec path
         if (SetPath(&pam->fsp)) // se non riesce ad impostarlo assume
            QueryCurrentPath(pam->fsp.pszPath, pam->fsp.pszFile);// path corr
      } else {
         QueryCurrentPath(pam->fsp.pszPath, pam->fsp.pszFile);
         pam->fsp.hpfs = isHPFS(*pam->fsp.pszPath);
      } // end if
   } /* endif */
   // mostra/nasconde data-ora creazione e ultimo accesso secondo FS
   DlgShowCtl(hwnd, STB_CREATED, pam->fsp.hpfs);
   DlgShowCtl(hwnd, STB_ACCESSED, pam->fsp.hpfs);
   FillDriveList(hwnd, pam);// riempie la listbox drive - listbox folder
   FillDirList(hwnd, pam);
   // inizializza a NULLHANDLE l'handle del dialogo preferenze
   pam->pro.hPref = NULLHANDLE;
   // rileva versione del sistema operativo
   DosQuerySysInfo(QSV_VERSION_MINOR, QSV_VERSION_MINOR, &pam->pro.ulVer,
                   sizeof(ULONG));
   return (MRESULT) FALSE;
}      
