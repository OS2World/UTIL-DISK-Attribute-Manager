//==========================================================================\
// import.c : funzioni per l'importazione di descrizioni esterne al file    |
//==========================================================================/

#define INCL_WIN
#include <os2.h>
#include <stdlib.h>
#include <mledlg.h>
#include <efdlg.h>
#include <listbox.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"


//==========================================================================\
// ImportFileData: determina sorgente di importazione e importa i dati      |
// parametri:                                                               |
// HWND hwnd                                                                |
// PATTMAN pam                                                              |
// valore restituito:                                                       |
// BOOL: TRUE = dati importati - FALSE = nessun dato importato              |
//==========================================================================/

BOOL ImportFileData(HWND hwnd, PATTMAN pam) {
   
   // controlla la modalit… di importazione
   switch (pam->pro.imp.def_imp) {
      case RADIO_IMP_4:       // importazione file descript.ion
         return Show4Dos(hwnd, pam);
      case RADIO_FILE_ID_DIZ: // importazione da archivio
         return ShowFileIdDiz(hwnd, pam);
      case RADIO_USER_DEF:    // importazione definita dall'utente
         return ShowUserDef(hwnd, pam);
      case RADIO_IMP_OTHER:   // mostra dialogo selezione sorgente importazione
         return ShowOther(hwnd, pam);
      default: // modalit… selezione automatica sorgente importazione
         if (pam->pro.imp.quattro[0] && Show4Dos(hwnd, pam)) return TRUE;
         if (ShowFileIdDiz(hwnd, pam)) return TRUE;
         if (pam->pro.imp.ftoimp[0] &&
             pam->pro.imp.xtrprog[0] &&
             pam->pro.imp.xtrparms[0] &&
             ShowUserDef(hwnd, pam)) return TRUE;
         break;
   } /* endswitch */
   return FALSE;
}


//==========================================================================\
// DisplayImportedData: mostra i dati importati secondo le opzioni          |
//                      selezionate nel blocco preferenze, eventualmente    |
//                      copia i dati negli EAs                              |
// parametri:                                                               |
// HWND hwnd, PATTMAN pam                                                   |
// PSZ pszBuf = indirizzo buffer contenente i dati                          |
// ULONG ulSize = dimensione dati                                           |
// valore restituito:                                                       |
// TRUE = successo, FALSE = errore                                          |
//==========================================================================/

BOOL DisplayImportedData(HWND hwnd, PATTMAN pam, PSZ pszData, ULONG ulSize) {
   ULONG ulMaxLen;
   VOID *buffer;
   BOOL saveattr = !(pam->pro.imp.view || pam->pro.gen.ronly);
   BOOL rc;

   // se non Š view mode o read only alloca memoria x scrittura EAs
   if (saveattr) {
      if ((buffer = malloc((size_t)0x00010000L)) == NULL) {
         PMPrint(hwnd, ERR_ALLOC_READ_ATTR);
         return FALSE;
      } // end if
   } // end if
   if (pam->pro.imp.imp_to == RADIO_TO_AUTO) {  // determina target import
      ulMaxLen = pam->pro.gen.subj > 0? pam->pro.gen.subj:
                                        -pam->pro.gen.subj;
      if (ulSize > ulMaxLen)  // se troppo lungo
         ulMaxLen = RADIO_TO_CMNT;
   } else {
      ulMaxLen = pam->pro.imp.imp_to;
   } /* endif */
   // se Š stato originato da una selezione del menu contestuale
   if (pam->sMenuFrom == EF_SUBJ || pam->sMenuFrom == MLE_COMNT)
      ulMaxLen = pam->sMenuFrom;
   if (ulMaxLen == RADIO_TO_CMNT || ulMaxLen == MLE_COMNT) { // imp to comment
      ShowAttr(hwnd, MLE_COMNT, pszData, &ulSize);
      if (saveattr)
         rc = WriteComments(hwnd, pam->fsp.pszFile, buffer);
   } else {                                     // import to subject
      WinSetDlgItemText(hwnd, EF_SUBJ, pszData);
      DlgEFQueryChanged(hwnd, EF_SUBJ);
      if (saveattr)         // copia negli EAs
         rc = WriteSubject(hwnd, pam->fsp.pszFile, buffer);
   } /* endif */
   if (saveattr) free(buffer);
   return rc;
}


//==========================================================================\
//                      |
// parametri:                                                               |
// 
// valore restituito:                                                       |
//            |
//==========================================================================/

MRESULT ProcessReady(HWND hwnd, MPARAM mp1, MPARAM mp2) {
   static HWND HWrite;
   static int idx;
   int i;
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   // se Š il primo file selezionato avvia dialogo progresso
   if (LONGFROMMP(mp2) == LIT_FIRST) {
      HWrite = WinLoadDlg(HWND_DESKTOP, hwnd, ProgDlgProc,
                           NULLHANDLE, WRITE_DLG, NULL);
      idx = LIT_FIRST;
   } // end if
   // se non ci sono pi— file selezionati termina il loop
   if (LONGFROMMP(mp2) == LIT_ERROR ||
       (idx = DlgLboxQueryNextSelItem(hwnd, LB_FILE, idx)) == LIT_NONE) {
      WinDestroyWindow(HWrite);
      // WinDismissDlg(HWrite, FALSE);
      return (MRESULT) FALSE;
   } // end if
   // rileva il nome del file selezionato corrispondente a mp2
   DlgLboxQueryItemText(hwnd, LB_FILE, idx, pam->fsp.pszFile, 256);
   if (LONGFROMMP(mp1) == MN_ID_DIZ) { // estrazione file_id.diz
      if ((i = FindExt(pam)) < 0) {    // controlla che il file sia un arc
         PMPrint(hwnd, ERR_UNSUPPORTED); // riconosciuto altrimenti prosegue
         WinSendMsg(hwnd, WM_PROC_READY, MPFROMLONG(MN_ID_DIZ), MPFROMLONG(0)); // con il successivo
         return (MRESULT) FALSE;
      } // end if
      ExtractFileIdDiz(hwnd, pam, i);
      WinSetDlgItemText(HWrite, WRITE_FILE, pam->fsp.pszFile);
   } else {
      ShowUserDef(hwnd, pam);
      WinSetDlgItemText(HWrite, WRITE_FILE, pam->fsp.pszFile);
   } /* endif */
   return (MRESULT) FALSE;
}
