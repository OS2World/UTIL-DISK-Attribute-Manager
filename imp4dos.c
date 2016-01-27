// imp4dos.c: funzioni per la gestione dei descript.ion del 4 DOS-OS/2

#define INCL_WIN
#include <os2.h>
#include <stdlib.h>
#include <listbox.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"


//==========================================================================\
// Show4Dos: importa commenti dal file descript.ion del 4DOS-OS/2           |
// parametri:                                                               |
// HWND hwnd                                                                |
// PATTMAN pam                                                              |
// valore restituito:                                                       |
// BOOL: TRUE dati importati, FALSE = nessun dato                           |
//==========================================================================/

BOOL Show4Dos(HWND hwnd, PATTMAN pam) {
   PSZ buffer;
   PSZ pszCur;
   ULONG ulSize;
   BOOL rc;

   if (!ReadDescriptionList(pam, &buffer)) return FALSE;
   pszCur = buffer;
   if (!(ulSize = Find4DosFileDescription(pam, &pszCur))) {
      free(buffer);
      return FALSE;
   } // end if
   rc = DisplayImportedData(hwnd, pam, pszCur, ulSize);
   free(buffer);
   return rc;
}


//==========================================================================\
// ReadDescriptionList: apre il file DESCRIPT.ION leggendone il contenuto   |
// in PSZ buffer                                                            |
// parametri:                                                               |
// PATTMAN pam, PSZ buffer                                                  |
// valore restituito:                                                       |
// BOOL TRUE = successo, FALSE = errore                                     |
//==========================================================================/

BOOL ReadDescriptionList(PATTMAN pam, PPSZ pbuffer) {
   HFILE hf;
   ULONG ulRc;
   APIRET rc;
   FILESTATUS3 fst;

   // apre file descrizione 4DOS - OS/2
   if (rc = DosOpen(pam->pro.imp.quattro, &hf, &ulRc, 0,
                    FILE_NORMAL, FILE_OPEN,
                    OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE, NULL)) {
      PMPrint(HWND_DESKTOP, ERR_ACCESS_4DOSFILE);
      return FALSE;
   } // end if                           -- rileva dimensioni file
   DosQueryFileInfo(hf, FIL_STANDARD, &fst, sizeof(FILESTATUS3));
   // alloca memoria + spazio x zero finale x leggerne il contenuto
   if ((*pbuffer = malloc((size_t)fst.cbFile + 1)) == NULL) {
      PMPrint(HWND_DESKTOP, ERR_ALLOC_READ_DESCRIPTION);
      DosClose(hf);
      return FALSE;
   } // endif -- legge contenuto file
   DosRead(hf, *pbuffer, fst.cbFile, &ulRc);
   *(*pbuffer + fst.cbFile) = 0xff;   // termina il buffer di lettura con 0xff
   DosClose(hf);
   return TRUE;
}


//==========================================================================\
// Find4DosFileDescription: trova la descrizione corrispondente a           |
// pam->fsp.pszFile nel file DESCRIPT.ION                                   |
// parametri:                                                               |
// PATTMAN pam, PPSZ ppszCur                                                |
// valore restituito:                                                       |
// lunghezza della descrizione rilevata (0 se manca la descrizione)         |
//==========================================================================/

ULONG Find4DosFileDescription(PATTMAN pam, PPSZ ppszCur) {
   PSZ pszEnd;
   ULONG ulSize = sstrlen(pam->fsp.pszFile);
   // trova descrizione corrispondente al file corrente
   while (sstrnicmp(pam->fsp.pszFile, *ppszCur, ulSize)) {
      while (*((*ppszCur)++) != '\n')
         if (*(*ppszCur - 1) == 0xff) return FALSE;
   } /* endwhile */
   *ppszCur += ulSize; // punta alla fine del nome del file
   while (**ppszCur == ' ' || **ppszCur == '\t') ++(*ppszCur);  // canc spazi
   pszEnd = *ppszCur;  // marca con 0xff la fine della descrizione
   while (*pszEnd != '\xa' && *pszEnd != 0xff) pszEnd++; // trova fine descriz
   --pszEnd;           // cancella spazi finali
   while (*pszEnd == '\xd' || *pszEnd == ' ' || *pszEnd == '\t') --pszEnd;
   *++pszEnd = 0;
   return ulSize = pszEnd - *ppszCur;                     // dimensione dati
}


//==========================================================================\
//                      |
// parametri:                                                               |
// 
// valore restituito:                                                       |
//            |
//==========================================================================/

MRESULT Import4Dos(HWND hwnd, PATTMAN pam) {
   // se readonly o viewonly visualizza solo decrizione file corrente
   if (pam->pro.gen.ronly || pam->pro.imp.view)
      Show4Dos(hwnd, pam);
   else {     // sovrascrive eventuali descrizioni gi… presenti
      PSZ buffer;
      PSZ pszCur;
      HWND HWrite;
      SHORT idx = DlgLboxQuerySelectedItem(hwnd, LB_FILE);
      ULONG ulSize;
      DlgLboxQueryItemText(hwnd, LB_FILE, idx, pam->fsp.pszFile, 256);
      HWrite = WinLoadDlg(HWND_DESKTOP, hwnd, ProgDlgProc,
                           NULLHANDLE, WRITE_DLG, NULL);
      // se non riesce a leggere descript.ion in memoria
      if (!ReadDescriptionList(pam, &buffer)) return (MRESULT) FALSE;
      pszCur = buffer;
      forever {      // ripete per tutti i file selezionati
         if (!(ulSize = Find4DosFileDescription(pam, &pszCur))) {
            pszCur = buffer;
         } else {
            if (DisplayImportedData(hwnd, pam, pszCur, ulSize))
               WinSetDlgItemText(HWrite, WRITE_FILE, pam->fsp.pszFile);
         } // end if
         if ((idx = DlgLboxQueryNextSelItem(hwnd, LB_FILE, idx)) == LIT_NONE)
            break; //esce dal loop quando termina file selezionati
         DlgLboxQueryItemText(hwnd, LB_FILE, idx, pam->fsp.pszFile, 256);
      } /* endwhile */
      free(buffer);
      WinDestroyWindow(HWrite);
      // WinDismissDlg(HWrite, FALSE);
   } // end if
   return (MRESULT) FALSE;
}
