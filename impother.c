// impother.c: mostra file dialogo open per la selezione di un file esterno
//             da importare

#define INCL_WIN
#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "messages.h"


BOOL ShowOther(HWND hwnd, PATTMAN pam) {
   FILEDLG fdlg;

   memset(&fdlg, 0, sizeof(FILEDLG));
   fdlg.cbSize = sizeof(FILEDLG);
   fdlg.fl = FDS_OPEN_DIALOG | FDS_CENTER;
   if (WinFileDlg(HWND_DESKTOP, hwnd, &fdlg) && fdlg.lReturn == DID_OK) {
      HFILE hf;
      ULONG ulRc;
      ULONG cbRead;
      FILESTATUS3 fst;
      PSZ buffer;
      // apre file estratto
      if (DosOpen(fdlg.szFullFile, &hf, &ulRc, 0, FILE_NORMAL, FILE_OPEN,
                  OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE, NULL)) {
         PMPrint(hwnd, ERR_OPEN_OTHER);
         return FALSE;
      } // end if                 - ricava dimensione file estratto
      DosQueryFileInfo(hf, FIL_STANDARD, &fst, sizeof(FILESTATUS3));
      // se la dimensione Š > di 32KB la tronca
      cbRead = (fst.cbFile > 0x7fff)? 0x7fff: fst.cbFile;
      // allocazione x lettura file estratto
      if ((buffer = malloc((size_t)cbRead)) == NULL) {
         PMPrint(hwnd, ERR_ALLOC_OTHER);
         return FALSE;
      } // endif
      DosRead(hf, buffer, cbRead, &ulRc);
      DosClose(hf);
         DisplayImportedData(hwnd, pam, buffer, ulRc);
      free(buffer);
   } /* endif */
   return FALSE;
}
