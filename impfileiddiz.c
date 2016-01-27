// impfileiddiz.c:

#define INCL_WIN
#include <os2.h>
#include <stdlib.h>
#include <efdlg.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"


//==========================================================================\
// ShowFileIdDiz: importa il file file_id.diz dagli archivi                 |
// parametri:                                                               |
// HWND hwnd 
// valore restituito:                                                       |
// TRUE successo: FALSE errore           |
//==========================================================================/

BOOL ShowFileIdDiz(HWND hwnd, PATTMAN pam) {
   int i;

   if ((i = FindExt(pam)) < 0) {   // controlla che il file sia un archivio
      PMPrint(hwnd, ERR_UNSUPPORTED);    // riconosciuto, se non Š tale mostra
      return FALSE;                // msg errore e termina
   } // end if
   return ExtractFileIdDiz(hwnd, pam, i); // estrae file_id.diz dall'archivio
}


//==========================================================================\
// ExtractFileIdDiz: assegna alla struttura PROGDETAILS gli opportuni valori|
// e estrae la descrizione dall'archivio.                                   |
// parametri:                                                               |
// HWND hwnd, PATTMAN pam,                                                  |
// int i = indice nell'array di programi di scompattazione                  |
// valore restituito:                                                       |
// TRUE successo, FALSE errore                                              |
//==========================================================================/

BOOL ExtractFileIdDiz(HWND hwnd, PATTMAN pam, int i) {
   PROGDETAILS prgdet;
   CHAR achParms[300];
   prgdet.Length = sizeof(PROGDETAILS);
   prgdet.progt.progc = PROG_WINDOWABLEVIO;
   prgdet.progt.fbVisible = SHE_INVISIBLE;
   prgdet.pszTitle = NULL;
   prgdet.pszExecutable = (PSZ)pam->pro.imp.unarc.pui +
                             pam->pro.imp.unarc.pui[i].ulProg;
   if ((prgdet.pszParameters = GetParms(hwnd, achParms, pam,
                                        (PSZ)pam->pro.imp.unarc.pui +
                                        pam->pro.imp.unarc.pui[i].ulImp,
                                        (PSZ)pam->pro.imp.unarc.pui +
                                        pam->pro.imp.unarc.pui[i].ulParms))
       == NULL) return FALSE;
   prgdet.pszStartupDir = pam->pszTmpPath;
   prgdet.pszIcon = NULL;
   prgdet.pszEnvironment = NULL;
   prgdet.swpInitial.x = 0;
   prgdet.swpInitial.y = 0;
   prgdet.swpInitial.cx = 0;
   prgdet.swpInitial.cy = 0;
   prgdet.swpInitial.fl = SWP_HIDE;
   pam->hSt[WSTART_IMP_FID] = WinStartApp(hwnd, &prgdet, NULL, NULL,
                                    SAF_INSTALLEDCMDLINE | SAF_STARTCHILDAPP);
   return TRUE;
}


//==========================================================================\
// ReadFileIdDiz: chiamato quando il programma di scompattazione avviato    |
// con WinStartApp termina. Legge il contenuto del file_id.diz              |
// (eventualmente troncandolo a 32 KB) in memoria. Se l'importazione Š      |
// automatica o Š stata impostata dal pulsante import, visualizza i dati    |
// nella finestra opportuna, altrimenti li salva direttamente               |
// parametri:                                                               |
// MPARAM mp2 riporta il valore di terminazione del programma esterno       |
// valore restituito:                                                       |
// TRUE successo, FALSE errore                                              |
//==========================================================================/

BOOL ReadFileIdDiz(HWND hwnd, PATTMAN pam, MPARAM mp2) {
   if (!LONGFROMMP(mp2)) { // se l'applicazione Š terminata correttamente
      HFILE hf;
      ULONG ulRc;
      ULONG cbRead;
      FILESTATUS3 fst;
      PSZ buffer;
      PSZ cursor;
      int i = FindExt(pam);           // trova nome file estratto

      cursor = pam->pszTmpPath;       // ricava path completo file estratto
      while (*++cursor);
      *cursor++ = '\\';
      sstrcpy(cursor, (PSZ)pam->pro.imp.unarc.pui +
              pam->pro.imp.unarc.pui[i].ulImp);
      // apre file estratto
      if (DosOpen(pam->pszTmpPath, &hf, &ulRc, 0, FILE_NORMAL, FILE_OPEN,
                  OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE, NULL)) {
         PMPrint(hwnd, ERR_UNOPEN_FIDIZ);
         return FALSE;
      } // end if                 - ricava dimensione file estratto
      DosQueryFileInfo(hf, FIL_STANDARD, &fst, sizeof(FILESTATUS3));
      // se la dimensione Š > di 32KB la tronca
      cbRead = (fst.cbFile > 0x7fff)? 0x7fff: fst.cbFile;
      // allocazione x lettura file estratto
      if ((buffer = malloc((size_t)0x10000L)) == NULL) {
         PMPrint(hwnd, ERR_ALLOC_FIDIZ);
         return FALSE;
      } // endif
      DosRead(hf, buffer, cbRead, &ulRc);
      fst.attrFile = FILE_NORMAL;        // resetta attributi file
      DosSetFileInfo(hf, FIL_STANDARD, &fst, sizeof(FILESTATUS3));
      DosClose(hf);
      DosDelete(pam->pszTmpPath);        // cancella file
      *--cursor = 0;                     // cancella file dal percorso tmp
      if (pam->sMenuFrom == LB_FILE ||
          pam->sMenuFrom == BTN_IMP ||     // se non Š import da menu
          pam->pro.gen.ronly ||            // o se in ogni caso deve solo
          pam->pro.imp.view) {             // mostrare il testo importato
         DisplayImportedData(hwnd, pam, buffer, ulRc);
         WinSendMsg(hwnd, WM_PROC_READY, MPFROMLONG(MN_ID_DIZ),
                    MPFROMLONG(LIT_ERROR));   // non loopa i restanti file
      } else { // import da menu con salvataggio automatico
         if (pam->sMenuFrom == EF_SUBJ) {
            WinSetDlgItemText(hwnd, EF_SUBJ, buffer);
            DlgEFQueryChanged(hwnd, EF_SUBJ);
            WriteSubject(hwnd, pam->fsp.pszFile, buffer);
         } else {
            ShowAttr(hwnd, MLE_COMNT, buffer, &ulRc);
            WriteComments(hwnd, pam->fsp.pszFile, buffer);
         } // endif          -- processa file successivo
         WinSendMsg(hwnd, WM_PROC_READY, MPFROMLONG(MN_ID_DIZ), MPFROMLONG(0L));
      } // end if
      free(buffer);
   } else {
      PMPrint(hwnd, ERR_UNARC_PRG);         // passa al successivo file:
      WinSendMsg(hwnd, WM_PROC_READY, MPFROMLONG(MN_ID_DIZ), MPFROMLONG(0L));
   } /* endif */
   return FALSE;
}


//========================================================================\
// FindExt: riporta l'indice nell'array di strutture, cui punta           |
// UNARCDATA.pui, del programma di scompattazione adatto al file corrente |
// in caso di mancata corrispondenza viene restituito il valore di -1     |
//========================================================================/

int FindExt(PATTMAN pam) {
   int i;
   for (i = 0; i < pam->pro.imp.unarc.ulItems; i++) {
      if (WildCmp((PSZ)pam->pro.imp.unarc.pui +
                  pam->pro.imp.unarc.pui[i].ulExt, pam->fsp.pszFile))
         return i;
   } /* endfor */
   return -1;
}


//========================================================================\
// ImportFileIdDiz: importa il file_id.diz per tutti i file selezionati   |
//                  se in modalit… readonly o viewonly richiama la        |
//                  funzione ShowFileIdDiz().
//                  Se ci sono pi— file selezionati avvia la serie di     |
//                  processi di estrazione e salvataggio spedendo il msg  |
//                  WM_PROC_READY.
//========================================================================/


MRESULT ImportFileIdDiz(HWND hwnd, PATTMAN pam) {
   // se readonly o viewonly visualizza solo decrizione file corrente
   if (pam->pro.gen.ronly || pam->pro.imp.view)
      ShowFileIdDiz(hwnd, pam);
   else      // sovrascrive eventuali descrizioni gi… presenti
      WinSendMsg(hwnd, WM_PROC_READY, MPFROMLONG(MN_ID_DIZ),
                 MPFROMLONG(LIT_FIRST));
   return (MRESULT) FALSE;
}
