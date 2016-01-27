//==========================================================================\
// mask.c : procedure per i dialoghi secondari                              |
//==========================================================================/

#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#include <EFDlg.h>
#include <listbox.h>
#include <mywinutil.h>
#include <spinbtn.h>
#include <stdio.h>
#include <stdlib.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"


//==========================================================================\
// procedura dialogo selezione Mask                                         |
//==========================================================================/

MRESULT EXPENTRY MaskDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   static PMASKSEL pmask;
   static BOOL flag = FALSE;   // TRUE se Š stato aggiunto o tolto un elemento
   static int idx;             // posizione item selezionato o di inserzione

   switch (msg) {
      case WM_INITDLG: {
         CHAR buf[FACESIZE];
         PSZ pszCur;
         int len;
         pmask = (PMASKSEL)PVOIDFROMMP(mp2);      // recupera indirizzo dati
         // imposta il font della barra del titolo:
         PrfQueryProfileString(HINI_USERPROFILE, "PM_SystemFonts",
                               "WindowTitles", "9.WarpSans", buf, FACESIZE);
         WinSetPresParam(WinWindowFromID(hwnd, FID_TITLEBAR), PP_FONTNAMESIZE,
                         sstrlen(buf) + 1, (PVOID)(buf));
         WinSetWindowPos(hwnd, HWND_BOTTOM, pmask->pos.x, pmask->pos.y, 0, 0,
                         SWP_MOVE | SWP_SHOW);    // visualizza la finestra
         pszCur = pmask->pszExt;
         DlgEFSetTxtLimit(hwnd, COMBO_MASK, 63);
         // riempie la listbox
         while (len = sstrlen(pszCur)) {
            DlgLboxInsertItem(hwnd, COMBO_MASK, LIT_SORTASCENDING, pszCur);
            pszCur += len + 1;
         } /* endwhile */
         } // end case WM_INITDLG:
         break;
      case WM_CONTROL:
         switch (SHORT2FROMMP(mp1)) {
            case CBN_EFCHANGE: {          // cambiamento testo
               BOOL enable;
               // pulsante OK abilitato se c'e' testo nell' entrifield
               enable = WinQueryDlgItemTextLength(hwnd, COMBO_MASK);
               WinEnableControl(hwnd, MASK_OK, enable);
               // pulsante ADD abilitato se c'Š testo non gi… presente
               WinQueryDlgItemText(hwnd, COMBO_MASK, 64, pmask->achSel);
               idx = isInListBox(hwnd, pmask->achSel, COMBO_MASK); 
               WinEnableControl(hwnd, MASK_STORE, enable && (idx < 0));
               // pulsante REMOVE abilitato se testo EF == item lista
               WinEnableControl(hwnd, MASK_DEL, idx >= 0);
               } // end case CBN_EFCHANGE:
               break;
            case CBN_LBSELECT:            // selezione item
               idx = isInListBox(hwnd, pmask->achSel, COMBO_MASK);
               WinEnableControl(hwnd, MASK_DEL, idx >= 0);
               break;
            default:
              break;
         } /* endswitch */
         break;
      case WM_COMMAND:
         switch (LOUSHORT(mp1)) {
            case MASK_OK:
               WinQueryDlgItemText(hwnd, COMBO_MASK, 64, pmask->achSel);
               if (flag)    // eventualmente aggiorna lista filespec
                  ProcMaskDlgExit(hwnd, pmask);
               SaveMaskDlgPos(hwnd, pmask);
               WinDismissDlg(hwnd, TRUE);
               break;
            case MASK_STORE:
               flag = TRUE;
               DlgLboxInsertItem(hwnd, COMBO_MASK, LIT_SORTASCENDING,
                                 pmask->achSel);
               DlgLboxSelectItem(hwnd, COMBO_MASK, -idx - 1);
               WinEnableControl(hwnd, MASK_STORE, FALSE);
               break;
            case MASK_DEL:
               flag = TRUE;
               idx = DlgLboxQuerySelectedItem(hwnd, COMBO_MASK);
               DlgLboxDeleteItem(hwnd, COMBO_MASK, idx);
               WinSetDlgItemText(hwnd, COMBO_MASK, "");
               break;
            default: 
               if (flag)    // eventualmente aggiorna lista filespec
                  ProcMaskDlgExit(hwnd, pmask);
               SaveMaskDlgPos(hwnd, pmask);
               WinDismissDlg(hwnd, FALSE);
               break;
         } /* endswitch */
         break;
      case WM_CLOSE:
         if (flag)    // eventualmente aggiorna lista filespec
            ProcMaskDlgExit(hwnd, pmask);
         SaveMaskDlgPos(hwnd, pmask);
         WinDismissDlg(hwnd, FALSE);
         break;
      default: 
         return WinDefDlgProc(hwnd, msg, mp1, mp2);
   } // end switch
   return (MRESULT) FALSE;
}


//==========================================================================\
// ProcMaskDlgExit                     |
// parametri:                                                               |
// HWND hwnd 
// valore restituito:                                                       |
//            |
//==========================================================================/

VOID ProcMaskDlgExit(HWND hwnd, PMASKSEL pmask) {
   LONG ulItems;               // numero di items presenti nella listbox
   ULONG ulAlloc = 1;          // byte da allocare
   INT idx;                    // indice item
   PSZ pszTmp;                 // puntatore inizio nuova allocazione
   PSZ pszCur;                 // cursore nello spazio allocato

   ulItems = DlgLboxQueryItemCount(hwnd, COMBO_MASK);
   // calcola memoria da allocare x memorizzare contenuto listbox
   for (idx = 0; idx < ulItems; ++idx) {
      ulAlloc += DlgLboxQueryItemTextLength(hwnd, COMBO_MASK, idx) + 1; 
   } /* endfor */
   // se l'allocazione fallisce mostra msg di errore
   if ((pszTmp = (PSZ)malloc((size_t)ulAlloc)) == NULL ) {
      PMPrint(HWND_DESKTOP, ERR_ALLOC_MASK_DATA);
   } else { // copia in memoria contenuto listbox e libera preced buffer
      pmask->ulLen = ulAlloc;
      pszCur = pszTmp;
      for (idx = 0; idx < ulItems; ++idx) {
         ULONG ulTxt;
         ulTxt = DlgLboxQueryItemText(hwnd, COMBO_MASK, idx, pszCur, ulAlloc);
         ulAlloc -= ulTxt;
         pszCur += ulTxt + 1;
      } /* endfor */
      *pszCur = 0;
      free(pmask->pszExt);
      pmask->pszExt = pszTmp;
   } /* endif */
}


//==========================================================================\
// salva la posizione del dialogo                                           |
//==========================================================================|

VOID SaveMaskDlgPos(HWND hwnd, PMASKSEL pmask) {
   SWP swp;
   WinQueryWindowPos(hwnd, &swp);
   pmask->pos.x = swp.x;
   pmask->pos.y = swp.y;
}
