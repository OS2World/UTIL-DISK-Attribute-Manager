//==========================================================================\
// attributes.c : funzioni generiche interfacciamento OrdAtrrs.C EAs.c      |
// per la lettura/scrittura attributi estesi e ordinari                     |
// LONG GetAttr(HWND hwnd, PFILESPECS pfsp);                                |
// BOOL WriteNewAttr(HWND hwnd, PATTMAN pam);                               |
// BOOL WriteSubject(HWND hwnd, PSZ pszFile, PVOID buffer);                 |
// BOOL WriteKeyPhrases(HWND hwnd, PSZ pszFile, PVOID buffer);              |
// BOOL WriteComments(HWND hwnd, PSZ pszFile, PVOID buffer);                |
// VOID ReadMle(HWND hwnd, ULONG ctrlID, CHAR *buffer, ULONG *ulData);      |
// VOID ShowAttr(HWND hwnd, ULONG ctrlID, CHAR *buffer, ULONG *ulData);     |
//==========================================================================/

#define INCL_WIN
#include <os2.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <listbox.h>
#include <MleDlg.h>
#include <EFDlg.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"


//==========================================================================\
// mostra gli attributi ordinari, data/ora file  e .SUBJECT, .COMMENTS e    |
// .KEYPHRASES del file specificato                                         |
// HWND hwnd   = handle finestra principale                                 |
// PSZ pszFile = nome file di cui si vogliono leggere gli attributi         |
//==========================================================================/

LONG GetAttr(HWND hwnd, PFILESPECS pfsp) {
   VOID *buffer;
   ULONG ulData;
   LONG rc = 0;

   if ((buffer = malloc((size_t)0x00010000L)) == NULL) {
      PMPrint(hwnd, ERR_ALLOC_READ_ATTR);
      return -1;
   } // endif
   GetOrdAttrs(hwnd, pfsp);
   GetEa(pfsp->pszFile, ".KEYPHRASES", 11, buffer, &ulData);
   ulData = Attr2Text(buffer, ulData, 1);
   ShowAttr(hwnd, MLE_KEY, buffer, &ulData);
   GetEa(pfsp->pszFile, ".COMMENTS", 9, buffer, &ulData);
   rc += ulData;
   ulData = Attr2Text(buffer, ulData, 1);
   ShowAttr(hwnd, MLE_COMNT, buffer, &ulData);
   GetEa(pfsp->pszFile, ".SUBJECT", 8, buffer, &ulData);
   rc += ulData;
   ulData = Attr2Text(buffer, ulData, 1);
   ulData = ulData > 2 ? ulData - 2 : 0;
   *(((PUCHAR)buffer) + ulData) = 0x0;
   pfsp->subjChanged = -1;
   WinSetDlgItemText(hwnd, EF_SUBJ, buffer);
   DosFreeMem(buffer);
   return rc;
}


//==========================================================================\
// ricava il nome dei file selezionati, se ci sono + file selezionati       |
// mostra il dialogo per il salvataggio multiplo                            |
// copia il contenuto delle MLE negli EAS                                   |
//==========================================================================/

BOOL WriteNewAttr(HWND hwnd, PATTMAN pam) {
   VOID *buffer;
   ULONG ulData;
   int i;

   if ((buffer = malloc((size_t)0x00010000L)) == NULL) {
      PMPrint(hwnd, ERR_ALLOC_WRITE_ATTR);
      return FALSE;
   } // endif

   // nel caso ci sia la selezione estesa e ci siano pi— file selezionati
   if (pam->fsp.psSel[0] > 1) {
      HWND wrtHwnd;                    // handle dialogo salvataggio multiplo
      FILESTATUS3 fs3;                 // per dati file corrente
      // nome primo file selezionato dovrebbe essere == pam->fsp.pszFile
      DlgLboxQueryItemText(hwnd, LB_FILE, pam->fsp.psSel[1],
                           pam->fsp.pszFile, 256);
      // mostra dialogo salvataggio multiplo
      if ((ulData = WinDlgBox(HWND_DESKTOP, hwnd, SaveMultiDlgProc,
                         NULLHANDLE, MULT_SAVE_DLG, pam)) != 0) {
         // mostra dialogo progresso salvataggio con nome file corrente
         wrtHwnd = WinLoadDlg(HWND_DESKTOP, hwnd, ProgDlgProc,
                              NULLHANDLE, WRITE_DLG, NULL);
         i = 1; // ripete per tutti i file selezionati
         forever {
            WinSetDlgItemText(wrtHwnd, WRITE_FILE, pam->fsp.pszFile);
            // se si sceglie di aggiornare uno degli attributi ordinari
            if (ulData & UPDT_ORDATTR) { // legge attributi precedenti
               DosQueryPathInfo(pam->fsp.pszFile, FIL_STANDARD,
                                (PVOID)&fs3, sizeof(FILESTATUS3));
               UpdateOrdAttr(hwnd, &fs3, &pam->fsp, ulData);// li aggiorna
            } /* endif */
            // aggiorna gli attributi estesi
            if (ulData & UPDT_SUBJ)
               WriteSubject(hwnd, pam->fsp.pszFile, buffer);
            if (ulData & UPDT_KEY)
               WriteKeyPhrases(hwnd, pam->fsp.pszFile, buffer);
            if (ulData & UPDT_CMNT)
               WriteComments(hwnd, pam->fsp.pszFile, buffer);
            if (++i > pam->fsp.psSel[0]) break; // termina loop
            DlgLboxQueryItemText(hwnd, LB_FILE, pam->fsp.psSel[i],
                                 pam->fsp.pszFile, 256);
         } /* endwhile */
         WinDestroyWindow(wrtHwnd);
      } // end if
   } else {        // un solo file selezionato
      if (isOrdAttrChanged(hwnd, &pam->fsp))
         DosSetPathInfo(pam->fsp.pszFile, FIL_STANDARD, &pam->fsp.fsNew,
                        sizeof(FILESTATUS3), 0L);
      if (DlgMleQueryChanged(hwnd, MLE_KEY))
         WriteKeyPhrases(hwnd, pam->fsp.pszFile, buffer);
      if (DlgMleQueryChanged(hwnd, MLE_COMNT))
         WriteComments(hwnd, pam->fsp.pszFile, buffer);
      if (pam->fsp.subjChanged)
         WriteSubject(hwnd, pam->fsp.pszFile, buffer);
   } // end if
   pam->fsp.subjChanged = -1;      // resetta flag cambiamento subject,
   pam->fsp.fsNew.cbFile = FALSE;  // data/ora file e attributi ordinari
   pam->fsp.fs.attrFile = pam->fsp.fsNew.attrFile;
   free(buffer);
   return TRUE;
}


//==========================================================================\
// scrive gli EA .SUBJECT:                                                  |
//==========================================================================/

BOOL WriteSubject(HWND hwnd, PSZ pszFile, PVOID buffer) {
   ULONG ulData;

   if ((ulData = WinQueryDlgItemText(hwnd, EF_SUBJ, 256, (PSZ)buffer + 4))!=0) {
      *((PUSHORT)buffer) = EAT_ASCII;
      *(((PUSHORT)buffer) + 1) = (USHORT)ulData;
      ulData += 4;
   }
   memmove(((PBYTE)buffer) + 0x200, buffer, ulData);// a causa dell'attuale
   return PutEa(pszFile, ".SUBJECT", 8, buffer, &ulData);// implementaz di PutEa()
}


//==========================================================================\
// scrive gli EA .KEYPHRASES                                                |
//==========================================================================/

BOOL WriteKeyPhrases(HWND hwnd, PSZ pszFile, PVOID buffer) {
   ULONG ulData;
   ReadMle(hwnd, MLE_KEY, ((PCHAR)buffer) + 0x8000, &ulData);
   Text2Attr(((PCHAR)buffer) + 0x200, &ulData);
   return PutEa(pszFile, ".KEYPHRASES", 11, buffer, &ulData);
}


//==========================================================================\
// scrive gli EA .COMMENTS                                                  |
//==========================================================================/

BOOL WriteComments(HWND hwnd, PSZ pszFile, PVOID buffer) {
   ULONG ulData;
   ReadMle(hwnd, MLE_COMNT, ((PCHAR)buffer) + 0x8000, &ulData);
   Text2Attr(((PCHAR)buffer) + 0x200, &ulData);
   return PutEa(pszFile, ".COMMENTS", 9, buffer, &ulData);
}


//==========================================================================\
// copia il contenuto della MLE nel buffer                                  |
//==========================================================================/

VOID ReadMle(HWND hwnd, ULONG ctrlID, CHAR *buffer, ULONG *ulData) {
   ULONG offset = 0;
   ULONG length;

   if ((*ulData = DlgMleQueryTxtLength(hwnd, ctrlID)) > 0x7FFFL) {
      PMPrint(hwnd, ERR_EA_BUFFER);
      *ulData = 0x7FFFL; // tronca il testo a 32768 byte
   } /* endif */
   length = *ulData;             // il testo verra' copiato in fondo al buffer
   DlgMleInit(hwnd, ctrlID, (buffer), *ulData);
   DlgMleGetTxt(hwnd, ctrlID, &offset, ulData);
   // debug data
   *ulData = length;
}

//==========================================================================\
// mostra gli atributi nella MLE                                            |
//==========================================================================/

VOID ShowAttr(HWND hwnd, ULONG ctrlID, CHAR *buffer, ULONG *ulData) {
   IPT lOffset = 0;
   DlgMleDeleteAll(hwnd, ctrlID);
   DlgMleInit(hwnd, ctrlID, buffer, *ulData);
   DlgMleSetTxt(hwnd, ctrlID, &lOffset, ulData);
   DlgMleResetChanged(hwnd, ctrlID);
}
