// impudef.c:

#define INCL_WIN
#include <os2.h>
#include <stdlib.h>
#include "efdlg.h"
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"


//==========================================================================\
// ShowUserDef: importa il file creato da un programma definito dall'utente |
// parametri:                                                               |
// HWND hwnd, PATTMAN pam                                                   |
// valore restituito:                                                       |
// TRUE successo: FALSE errore                                              |
//==========================================================================/

BOOL ShowUserDef(HWND hwnd, PATTMAN pam) {
   PROGDETAILS prgdet;
   CHAR achParms[300];
   prgdet.Length = sizeof(PROGDETAILS);
   prgdet.progt.progc = PROG_WINDOWABLEVIO;
   prgdet.progt.fbVisible = SHE_INVISIBLE;
   prgdet.pszTitle = NULL;
   prgdet.pszExecutable = pam->pro.imp.xtrprog;
   if ((prgdet.pszParameters = GetParms(hwnd, achParms, pam,
                                        pam->pro.imp.ftoimp,
                                        pam->pro.imp.xtrparms))
       == NULL) return FALSE;
   prgdet.pszStartupDir = pam->pszTmpPath;
   prgdet.pszIcon = NULL;
   prgdet.pszEnvironment = NULL;
   prgdet.swpInitial.x = 0;
   prgdet.swpInitial.y = 0;
   prgdet.swpInitial.cx = 0;
   prgdet.swpInitial.cy = 0;
   prgdet.swpInitial.fl = SWP_HIDE;
   pam->hSt[WSTART_UDEF] = WinStartApp(hwnd, &prgdet, NULL, NULL,
                                    SAF_INSTALLEDCMDLINE | SAF_STARTCHILDAPP);
   return TRUE;
}


//==========================================================================\
// ReadUserDef: chiamato quando il programma definito dall'utente, avviato  |
// con WinStartApp termina. Legge il contenuto del file definito            |
// (eventualmente troncandolo a 32 KB) in memoria. Se l'importazione Š      |
// automatica o Š stata impostata dal pulsante import, visualizza i dati    |
// nella finestra opportuna, altrimenti li salva direttamente               |
// parametri:                                                               |
// MPARAM mp2 riporta il valore di terminazione del programma esterno       |
// valore restituito:                                                       |
// TRUE successo, FALSE errore                                              |
//==========================================================================/

BOOL ReadUserDef(HWND hwnd, PATTMAN pam, MPARAM mp2) {
   if (!LONGFROMMP(mp2)) { // se l'applicazione Š terminata correttamente
      HFILE hf;
      ULONG ulRc;
      ULONG cbRead;
      FILESTATUS3 fst;
      PSZ buffer;
      PSZ cursor;
      BOOL rc;

      cursor = pam->pszTmpPath;       // ricava path completo file estratto
      while (*++cursor);
      *cursor++ = '\\';
      sstrcpy(cursor, pam->pro.imp.ftoimp);
      // apre file estratto
      if (DosOpen(pam->pszTmpPath, &hf, &ulRc, 0, FILE_NORMAL, FILE_OPEN,
                  OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE, NULL)) {
         PMPrint(hwnd, ERR_OPEN_UDEF);
         return FALSE;
      } // end if                 - ricava dimensione file estratto
      DosQueryFileInfo(hf, FIL_STANDARD, &fst, sizeof(FILESTATUS3));
      // se la dimensione Š > di 32KB la tronca
      cbRead = (fst.cbFile > 0x7fff)? 0x7fff: fst.cbFile;
      // allocazione x lettura file estratto
      if ((buffer = malloc((size_t)0x10000L)) == NULL) {
         PMPrint(hwnd, ERR_ALLOC_UDEF);
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
         rc = DisplayImportedData(hwnd, pam, buffer, ulRc);
         WinSendMsg(hwnd, WM_PROC_READY, MPFROMLONG(MN_ID_UDEF),
                    MPFROMLONG(LIT_ERROR));
      } else { // import da menu con salvataggio automatico
         if (pam->sMenuFrom == EF_SUBJ) {
            WinSetDlgItemText(hwnd, EF_SUBJ, buffer);
            DlgEFQueryChanged(hwnd, EF_SUBJ);
            WriteSubject(hwnd, pam->fsp.pszFile, buffer);
         } else {
            ShowAttr(hwnd, MLE_COMNT, buffer, &ulRc);
            WriteComments(hwnd, pam->fsp.pszFile, buffer);
         } // end if
         WinSendMsg(hwnd, WM_PROC_READY, MPFROMLONG(MN_ID_UDEF),
                    MPFROMLONG(LIT_FIRST));
      } // end if 
      free(buffer);
      return rc;
   } else {
      PMPrint(hwnd, ERR_UDEF_PRG);
      WinSendMsg(hwnd, WM_PROC_READY, MPFROMLONG(MN_ID_UDEF), MPFROMLONG(0L));
   } /* endif */
   return FALSE;
}


//==========================================================================\
// selezione da menu
//==========================================================================/

MRESULT ImportUserDef(HWND hwnd, PATTMAN pam) {
   // se readonly o viewonly visualizza solo decrizione file corrente
   if (pam->pro.gen.ronly || pam->pro.imp.view)
      ShowUserDef(hwnd, pam);
   else      // sovrascrive eventuali descrizioni gi… presenti
      WinSendMsg(hwnd, WM_PROC_READY, MPFROMLONG(MN_ID_UDEF),
                 MPFROMLONG(LIT_FIRST));
   return (MRESULT) FALSE;
}
