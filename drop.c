//==========================================================================\
// drop.c : funzioni gestione drop oggetti sulla barra del titolo           |
//==========================================================================/

#define INCL_WIN
#define INCL_WINSTDDRAG
#include <os2.h>
#include "attman.h"                  
#include "definitions.h"             
#include "funzioni.h"                
#include "interface.h"


//==========================================================================\
// elabora il messaggio DM_DRAGOVER                                         |
// HWND hwnd        = handle finestra principale                            |
// PDRAGINFO pdinfo = indirizzo struttura DRAGINFO                          |
//==========================================================================/

MRESULT ProcessDragOver(HWND hwnd, PDRAGINFO pdinfo) {
   PDRAGITEM pditem;
   ULONG cItem;
   BOOL flag = FALSE;
   DrgAccessDraginfo(pdinfo);
   if (pdinfo->usOperation != DO_DEFAULT) {    // se non Š drag default
      DrgFreeDraginfo(pdinfo);                 // ritorna
      return MRFROM2SHORT(DOR_NEVERDROP, 0);
   } /* endif */
   cItem = DrgQueryDragitemCount(pdinfo);      // numero oggetti draggati
   do {
      pditem = DrgQueryDragitemPtr(pdinfo, --cItem);
      if ((pditem->fsControl & DC_REF) ||     // se l'oggetto Š una shadow
          !DrgVerifyRMF(pditem, "DRM_OS2FILE", NULL))      // o Š astratto
         continue;
      flag = TRUE;
      break;
   } while (cItem); /* enddo */

   DrgFreeDraginfo(pdinfo);
   return flag? MRFROM2SHORT(DOR_DROP, DO_MOVE):
                MRFROM2SHORT(DOR_NEVERDROP, 0);
}


//==========================================================================\
// elaborazione conseguente al rilascio di un oggetto sulla titlebar        |
// HWND hwnd        = handle finestra principale                            |
// PDRAGINFO pdinfo = indirizzo struttura DRAGINFO                          |
// PATTMAN pam      = indirizzo struttura dati applicazione                 |
//==========================================================================/

MRESULT ProcessDrop(HWND hwnd, PDRAGINFO pdinfo) {
   SHORT idx;
   PDRAGITEM pditem;
   BOOL isFirst = TRUE;
   ULONG cItem;
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);

   if (!isChanged(hwnd, pam)) {
      DrgAccessDraginfo(pdinfo);
      cItem = DrgQueryDragitemCount(pdinfo);
      do {
         pditem = DrgQueryDragitemPtr(pdinfo, --cItem);
         DrgQueryStrName(pditem->hstrSourceName, 256, pam->fsp.pszFile);
   
         if (pditem->fsControl & DC_REF ||     // se l'oggetto Š una shadow
             !DrgVerifyRMF(pditem, "DRM_OS2FILE", NULL))    // o Š astratto
            continue;                          // esamina l'oggetto successivo
         if (isFirst) {      // se Š il primo item processato aggiorna path
            // rileva path  item rilasciato sulla barra del titolo
            DrgQueryStrName(pditem->hstrContainerName, 256, pam->fsp.pszPath);
            sstrcat(pam->fsp.pszPath, pam->fsp.pszFile);
            if (SetDisk(hwnd, pam->fsp.pszPath[0], &pam->fsp.hpfs)) { //oggetto drive rimosso
               QueryCurrentPath(pam->fsp.pszPath, pam->fsp.pszFile);
               DrgFreeDraginfo(pdinfo);
               return (MRESULT) FALSE;            
            } // end if
            pam->fsp.sPrvDrv = pam->fsp.pszPath[0] > 'Z'?
                               pam->fsp.pszPath[0] - 'a':
                               pam->fsp.pszPath[0] - 'A';
            MyDlgLboxSelectItem(hwnd, LB_DRIVE, pam->fsp.sPrvDrv);
            SetPath(&pam->fsp);
            pam->fsp.psSel[0] = -1;
            FillDirList(hwnd, pam);
            if (pditem->fsControl & DC_CONTAINER) { // se Š una cartella esce
               DrgFreeDraginfo(pdinfo);
               return (MRESULT) FALSE;
            } // end if
            isFirst = FALSE;
         } else if ((idx = isInListBox(hwnd, pam->fsp.pszFile, LB_FILE)) >= 0) {
            MyDlgLboxSelectItem(hwnd, LB_FILE, idx);
         } /* endif */
      } while (cItem); /* enddo */
      DrgFreeDraginfo(pdinfo);
      ProcessFileSelection(hwnd, pam);
   } /* endif */
   return (MRESULT) FALSE;
}
