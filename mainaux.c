//==========================================================================\
// MainAux.c : funzioni ausiliarie alla gestione dei msg della finestra     |
// principale del programma                                                 |
// MRESULT MinMaxFrame(HWND hwnd, PSWP pswp);                               |
// MRESULT ProcessMeasureItem(HWND hwnd);                                   |
// MRESULT AdjustWindowPos(HWND hwnd, PSWP pswp);                           |
// MRESULT DrawListBoxItem(HWND hwnd, POWNERITEM poi);                      |
// MRESULT ProcessContextMenu(HWND hwnd, ULONG idCtl);                      |
// MRESULT ProcessBubbleHelp(HWND hwnd, HWND hFrom);                        |
// MRESULT ProcessControl(HWND hwnd, MPARAM mp1);                           |
// MRESULT ProcessPresParmsChanged(HWND hwnd, LONG flag);                   |
// MRESULT ProcessCommand(HWND hwnd, MPARAM mp1, PAM_PRO ppref);            |
// MRESULT ProcessTermination(HWND hwnd, BOOL flag);                        |
// MRESULT ProcessChildAppEnd(HWND hwnd, MPARAM mp1, MPARAM mp2);           |
// MRESULT ProcessMouseMove (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2); |
// MRESULT ProcessMotionStart (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)|
// MRESULT ProcessMotionEnd (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2); |
// MRESULT ProcessTimer(HWND hwnd, LONG ulid)                               |
// MRESULT ProcessLBoxBtnUp(HWND hwnd, LONG lId, MPARAM mp2);               |
//==========================================================================/

#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#include <stdlib.h>
#include <listbox.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"


//==========================================================================\
// nasconde alcuni controlli per ottenere la corretta visualizzazione       |
// dell'icona quando minimizzato sulla scrivania e gestisce il              |
// ridimensionamento dei controlli interni in caso di massimizz/ripristino  |
// HWND hwnd = handle finestra principale                                   |
// PSWP pswp = puntatore struttura nuove dimensioni finestra                |
//==========================================================================/

MRESULT MinMaxFrame(HWND hwnd, PSWP pswp) {
   static ULONG status;
   static SWP swpMax;
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);

   // minimizzazione finestra nasconde i controlli in basso a sinistra
   if (pswp->fl & SWP_MINIMIZE) {
      Iconize(hwnd, FALSE, pam->fsp.hpfs); // nasconde controlli basso sinistra
   // ripristino dimensioni finestra da minimizzazione o massimizzazione
   } else if (pswp->fl & SWP_RESTORE) {
      // se prima era minimizzato controlla stato precedente minimizzazione
      if (WS_MINIMIZED & WinQueryWindowULong(hwnd, QWL_STYLE)) {
         if (status == SWP_MAXIMIZE)  // se prima della minimizz era maximizz
            ResizeControls(hwnd, swpMax.cx, pswp->cx, pswp->cy, pam);
         Iconize(hwnd, TRUE, pam->fsp.hpfs);
      } else {           // se prima era MASSIMIZZATO ridimensiona controlli
         ResizeControls(hwnd, swpMax.cx, pswp->cx, pswp->cy, pam);
      } /* endif */
      status = SWP_RESTORE;                   // memorizza lo status attuale

   // massimizzazione finestra da minimizzazione o stato normale
   } else {
      if (!swpMax.fl) swpMax = *pswp;// memorizza dati finestra massimizzata
      // se prima era minimizzato controlla stato precedente minimizzazione
      if (WS_MINIMIZED & WinQueryWindowULong(hwnd, QWL_STYLE)) {
         if (status == SWP_RESTORE) // se prima della minimizz era normale
            ResizeControls(hwnd, pam->pro.swp.cx, pswp->cx, pswp->cy, pam);
         Iconize(hwnd, TRUE, pam->fsp.hpfs);
      } else {      // se prima era finestra normale ridimensiona controlli
         ResizeControls(hwnd, pam->pro.swp.cx, pswp->cx, pswp->cy, pam);
      } // endif
      status = SWP_MAXIMIZE;
   } // end if
   return (MRESULT) FALSE;
}


//==========================================================================\
// se la struttura dei dati del programma Š stata propriamente inizializzata|
// restituisce l'altezza dell'item                                          |
//==========================================================================/

MRESULT ProcessMeasureItem(HWND hwnd) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   return MPFROMLONG(pam->pro.gen.cyItem);
}


//==========================================================================\
// gestisce il ridimensionamento della finestra e dei controlli, impedisce  |
// che il dialogo venga ridotto oltre una dimensione minima                 |
// HWND hwnd                                                                |
// PSWP pswp       = nuove dimensioni finestra                              |
// PPOINTL pptlMin = dimensioni minime finestra                             |
//==========================================================================/

MRESULT AdjustWindowPos(HWND hwnd, PSWP pswp) {
   SWP cswp;                           // SWP corrente della finestra
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   SHORT mincy;
   if (!pam)
      return WinDefDlgProc(hwnd, WM_ADJUSTWINDOWPOS, MPFROMP(pswp), 0L);
   if (pam->cyNoBrowse > 0) mincy = pam->cyNoBrowse;
   else mincy = pam->min.y;
   WinQueryWindowPos(hwnd, &cswp);     // ricava domensionei correnti
   if (pswp->fl & SWP_SIZE) {          // processa il msg solo se SWP_SIZE
      if (pswp->cx < pam->min.x) {     // se viene ridotto oltre cx min
         pswp->cx = pam->min.x;        // nuovo cx = min
         pswp->x = cswp.x;             // origine x = precedente x
      } /* endif */
      if (pswp->cy < mincy) {          // se viene ridotto oltre cy min
         pswp->cy = mincy;             // nuovo cy = min
         pswp->y = cswp.y;             // origine y = precedente y
      } /* endif */
      switch (pam->cyNoBrowse) {
         case -2:                      // avviato in browse mode
            pam->cyNoBrowse = 0;
            break;
         case -1:                      // switch da nobrwose a browse
            pam->cyNoBrowse = 0;       // resetta la flag
            return (MRESULT) FALSE;
         case 0:                       // gi… in modalit… browse
            if (pswp->cx == cswp.cx && pswp->cy == cswp.cy) //dimens invariate
               return (MRESULT) FALSE;
            pam->pro.swp.cy = pswp->cy;// aggiorna dimensione finestra nel
            pam->pro.swp.cx = pswp->cx;// file ini
            break;
         default:                      // no browse
            pswp->cy = pam->cyNoBrowse;
            if (pswp->cx == cswp.cx &&
                pswp->cy == cswp.cy)   //dimensioni invariate
               return (MRESULT) FALSE;
            pam->pro.swp.cx = pswp->cx;// aggiorna cx nel file ini
            break;
      } /* endswitch */
      ResizeControls(hwnd, cswp.cx, pswp->cx, pswp->cy, pam);
   } // endif
   return WinDefDlgProc(hwnd, WM_ADJUSTWINDOWPOS, MPFROMP(pswp), 0L);
}


//==========================================================================\
// gestisce l'inserimento degli item nella listbox dei folder               |
//==========================================================================/

MRESULT DrawListBoxItem(HWND hwnd, POWNERITEM poi) {
   RECTL rcl;
   HPOINTER hIco;
   char buf[256];
   int xshift;
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   LONG clrBack = pam->pro.gen.clrBack;        // background default
   LONG clrFore = pam->pro.gen.clrFore;        // foreground default

   // commuta in modalit… RGB
   GpiCreateLogColorTable(poi->hps, 0, LCOLF_RGB, 0, 0, NULL);
   // determina quale icona visualizzare
   if (poi->idItem > pam->fsp.currDir) {               // folder chiuso
      xshift = pam->fsp.currDir + 1;
      hIco = pam->hClose;
   } else {                                            // folder aperto
      xshift = poi->idItem;
      hIco = pam->hOpen;
   } // end if
   // se selezione item cambia colori = hilite background e foreground
   if (poi->fsState) {
      clrBack = pam->pro.gen.clrHiBack;
      clrFore = pam->pro.gen.clrHiFore;
   } /* endif */
   WinFillRect(poi->hps, &poi->rclItem, clrBack);
   poi->fsState = poi->fsStateOld = 0;
   WinDrawPointer(poi->hps, poi->rclItem.xLeft + 3 + xshift * 7,
                  poi->rclItem.yBottom + 1, hIco, DP_NORMAL);
   rcl.xLeft = poi->rclItem.xLeft + xshift * 7 + 30;
   rcl.xRight = poi->rclItem.xRight;
   rcl.yBottom = poi->rclItem.yBottom;
   rcl.yTop = poi->rclItem.yTop;
   DlgLboxQueryItemText(hwnd, LB_FOLDER, poi->idItem, buf, 256);
   WinDrawText(poi->hps, -1L, buf, &rcl, clrFore, clrBack,
               DT_VCENTER | DT_ERASERECT);
   return (MRESULT) TRUE;
}


//==========================================================================\
// elabora le azioni conseguenti alla pressione del tasto destro del mouse  |
// nelle finestre di editazione MLE e entryfield                            |
//==========================================================================/

MRESULT ProcessContextMenu(HWND hwnd, ULONG idCtl) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   pam->sMenuFrom = idCtl;
   if (idCtl == EF_SUBJ || idCtl == MLE_KEY || idCtl == MLE_COMNT) {
      InitEditMenu(hwnd, pam->hMEdit, pam);
      return ShowContextMenu(hwnd, pam->hMEdit);
   } else {
      return ShowContextMenu(hwnd, pam->hMMain);
   } /* endif */
}


//==========================================================================\
// mostra messagio help contestuale nella status bar                        |
// HWND hFrom indica la finestra che ha generato l'evento                   |
//==========================================================================/

MRESULT ProcessBubbleHelp(HWND hwnd, HWND hFrom) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   PSZ pszTxt;
   // se opzione help disattivata restituisce FALSE
   if (!pam->pro.gen.bubble) return (MRESULT)FALSE;
   // se timer inattivo o attivato da altra finestra lo riavvia
   if (pam->hCtlHelp != hFrom) {
      pam->hCtlHelp = hFrom;
      // mostra testo opportuno secondo origine evento
      switch(WinQueryWindowUShort(hFrom, QWS_ID)) {
         case BTN_OPEN:  pszTxt = BTN_OPEN_FLYHLP;  break;
         case BTN_CLOSE: pszTxt = BTN_CLOSE_FLYHLP; break;
         case BTN_UP:    pszTxt = BTN_UP_FLYHLP;    break;
         case BTN_DOWN:  pszTxt = BTN_DOWN_FLYHLP;  break;
         case BTN_SAVE:  pszTxt = BTN_SAVE_FLYHLP;  break;
         case BTN_IMP:   pszTxt = BTN_IMP_FLYHLP;   break;
         case BTN_REP:   pszTxt = BTN_REP_FLYHLP;   break;
         case BTN_FIND:  pszTxt = BTN_FIND_FLYHLP;  break;
         case BTN_LOG:   pszTxt = BTN_LOG_FLYHELP;  break;
         case STB_WRITTEN:
         case STB_CREATED:
         case STB_ACCESSED: pszTxt = SZ_CLICKTOEDIT; break;
         default: pszTxt = ""; break;
      } // end switch
      WinSetDlgItemText(hwnd, SBARMSG, pszTxt);
      WinStartTimer(WinQueryAnchorBlock(hwnd), hwnd, TID_CONTEXTHELP, 300);
   } // end if
   return (MRESULT) FALSE;
}


//==========================================================================\
// elabora le azioni conseguenti al rilevamento del msg WM_CONTOL           |
//==========================================================================/

MRESULT ProcessControl(HWND hwnd, MPARAM mp1) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);

   if (SHORT2FROMMP(mp1) == LN_ENTER) {
      switch (SHORT1FROMMP(mp1)) {
         case LB_DRIVE :            // selezione di un drive
            ProcessDriveSelection(hwnd, mp1, pam);
            break;
         case LB_FOLDER :           // selezione di una directory
            ProcessFolderSelection(hwnd, mp1, pam);
            break;
         case LB_FILE:              // selezione di un file
            ProcessFileSelection(hwnd, pam);
            break;
         default:
           break;
      } // endswitch    --- cambiamento entry field subject
   } else if (SHORT2FROMMP(mp1) == EN_CHANGE && SHORT1FROMMP(mp1) == EF_SUBJ) {
      ++pam->fsp.subjChanged;
      if (!pam->fsp.subjChanged)
         pam->fsp.subjUndo[0] = 0;
      else
         sstrcpy(pam->fsp.subjUndo, pam->fsp.subjCurr); 
      WinQueryDlgItemText(hwnd, EF_SUBJ, 256, pam->fsp.subjCurr);
   } /* endif */
   return (MRESULT)FALSE;
}


//==========================================================================\
// elaborazione conseguente cambiamento parametri presentazione             |
// chiede nome nuovo font e aggiorna dati font secondo il nuovo font        |
// parametri:                                                               |
// HWND hwnd     = handle finestra                                          |
// PPREFGEN pgen = puntatore struttura preferenze generali                  |
//==========================================================================/

MRESULT ProcessPresParmsChanged(HWND hwnd, LONG flag) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   CHAR szFont[FACESIZE];

   if (flag == PP_FONTNAMESIZE) { // cambiamento carattere
      WinQueryPresParam(hwnd, PP_FONTNAMESIZE, 0L, NULL, FACESIZE, &szFont, 0L);
      if (sstrcmp(szFont, pam->pro.gen.font)) {
         sstrcpy(pam->pro.gen.font, szFont);
         SetDialogFont(hwnd, &pam->pro.gen, FALSE);  // aggiorna dati font
      } /* endif */
   } /* endif */
   return (MRESULT) FALSE;
}

//==========================================================================\
// elabora le azioni conseguenti al rilevamento del msg WM_COMMAND          |
//==========================================================================/

MRESULT ProcessCommand(HWND hwnd, MPARAM mp1, PAM_PRO ppref) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   if (LOUSHORT(mp1) >= BTN_OPEN && LOUSHORT(mp1) <= BTN_FIND) {
      WinSetCapture(HWND_DESKTOP, NULLHANDLE);
      pam->sMenuFrom = LOUSHORT(mp1);
   } /* endif */
   switch (LOUSHORT(mp1)) {
      case STB_WRITTEN   :
      case STB_CREATED   :
      case STB_ACCESSED  :  return OpenEditDateTimeDlg(hwnd, pam, (ULONG)mp1);
      case BTN_OPEN      :  return ProcessButtonOpen(hwnd, pam);
      case BTN_CLOSE     :  return ProcessButtonClose(hwnd, pam);
      case BTN_SAVE      :  return ProcessButtonSave(hwnd, pam);
      case BTN_IMP       :  return ProcessButtonImport(hwnd, pam);
      case BTN_REP       :  return ProcessButtonReport(hwnd, pam);
      case BTN_FIND      :  return ProcessButtonFind();
      case BTN_UP        :  return ProcessButtonUp(hwnd, pam);
      case BTN_DOWN      :  return ProcessButtonDown(hwnd, pam);
      case MN_BROWSE     :  return ProcessMenuBrowse(hwnd, pam);
      case MN_SEL_ALL    :  return ProcessMenuSelAll(hwnd, pam);
      case MN_DESEL_ALL  :  return ProcessMenuDeselAll(hwnd, pam);
      case MN_MASK       :  return ProcessMenuMask(hwnd, pam);
      case MN_REFRESH    :  return ProcessMenuRefresh(hwnd, pam);
      case MN_SAVE       :  return ProcessButtonSave(hwnd, pam);
      case MN_SELECTED   :  return ProcessMenuSelected(hwnd);
      case MN_ALL        :  return ProcessMenuAll(hwnd);
      case MN_FTREE      :  return ProcessMenuFullTree(hwnd);
      case MN_FIND       :  return ProcessMenuFind(hwnd);
      case MN_EXIT       :  return ProcessTermination(hwnd, FALSE);
      case MN_PREF       :  return ProcessMenuPreferences(hwnd, pam, ppref);
      case MN_FONT       :  return ProcessMenuFont(hwnd, pam);
      case MN_READ       :  return ProcessMenuReadOnly(hwnd, pam);
      case MN_UNDO       :  return ProcessMenuUndo(hwnd, pam);
      case MN_CUT        :  return ProcessMenuCut(hwnd, pam);
      case MN_COPY       :  return ProcessMenuCopy(hwnd, pam);
      case MN_PASTE      :  return ProcessMenuPaste(hwnd, pam);
      case MN_CLEAR      :  return ProcessMenuClear(hwnd, pam);
      case MN_AUTO       :  return ProcessMenuImpAuto(hwnd, pam);
      case MN_4          :  return ProcessMenu4Dos(hwnd, pam);
      case MN_ID_DIZ     :  return ProcessMenuID_DIZ(hwnd, pam);
      case MN_ID_UDEF    :  return ProcessMenuImpUdef(hwnd, pam);
      case MN_OTHER      :  return ProcessMenuOther(hwnd, pam);
      case MN_HLP_IDX    :  return ProcessMenuHelpIDX();
      case MN_HLP_GEN    :  return ProcessMenuHelpGeneral();
      case MN_HLP_USE    :  return ProcessMenuHelpUse();
      case MN_HLP_KEY    :  return ProcessMenuHelpKey();
      case MN_HLP_PROD   :  return ProcessMenuHelpProduct(hwnd);
      default :
         break;
   } /* endswitch */
   return (MRESULT)FALSE;
}


//==========================================================================\
// elaborazione conseguenti chiusura programma (WM_CLOSE)                   |
// restituisce TRUE se conferma la chiusura                                 |
//==========================================================================/

MRESULT ProcessTermination(HWND hwnd, BOOL flag) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   if (!pam->fsp.psSel || !isChanged(hwnd, pam)) {
      // se necessario chiude blocco impostazioni
      if (pam->pro.hPref != NULLHANDLE)
         WinSendMsg(pam->pro.hPref, WM_CLOSE, 0L, 0L);
      if (pam->pro.gen.pswp) {
         pam->pro.gen.cxDrv = pam->pro.gen.pswp[23].cx;
         pam->pro.gen.cxFld = pam->pro.gen.pswp[25].cx;
         free(pam->pro.gen.pswp);
      } // end if
      WriteAMSettings(hwnd, pam->pszProfile, &pam->pro);
      DosDeleteDir(pam->pszTmpPath);
      if (pam->fsp.psSel) free(pam->fsp.psSel);
      WinPostMsg(hwnd, WM_QUIT, 0, 0);
   } else if (flag) {        // se necessario cancella SHUTDOWN
        WinCancelShutdown((HMQ)WinQueryWindowULong(hwnd, QWL_HMQ), FALSE);
   } // end if
   return (MRESULT)FALSE;
}


//==========================================================================\
// ProcessChildAppEnd: elaborazione conseguente terminazione applicazione   |
// avviata con WinStartApp.                                                 |
//==========================================================================/

MRESULT ProcessChildAppEnd(HWND hwnd, MPARAM mp1, MPARAM mp2) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   if ((HAPP)mp1 == pam->hSt[WSTART_IMP_FID])
      ReadFileIdDiz(hwnd, pam, mp2);
   else if ((HAPP)mp1 == pam->hSt[WSTART_UDEF])
      ReadUserDef(hwnd, pam, mp2);
   else if ((HAPP)mp1 == pam->hSt[WSTART_REPORT])
      ;
   else if ((HAPP)mp1 == pam->hSt[WSTART_FIND])
      ;
   else
      ;
   return (MRESULT) FALSE;
}


MRESULT ProcessMouseMove (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   SHORT x = SHORT1FROMMP(mp1);
   SHORT y = SHORT2FROMMP(mp1);
   static int oldx;

   dprintf(">>>>>>>> mousemove >>> x = %d, y = %d, browse = %d, flag = %d\n",
           x, y,pam->cyNoBrowse, pam->szCtl);
   // finestra browsing non visibile
   if (pam->cyNoBrowse)
      return WinDefDlgProc(hwnd, msg, mp1, mp2);
   if (y > pam->pro.gen.pswp[23].y &&  // y compreso nella posizione listbox
       y < (pam->pro.gen.pswp[23].y + pam->pro.gen.pswp[23].cy)) {
      if (x <= pam->pro.gen.pswp[25].x &&     // x tra lbox drive e folder
          x >= (pam->pro.gen.pswp[23].x + pam->pro.gen.pswp[23].cx)) {
         if (!pam->szCtl || pam->szCtl == 3) pam->szCtl = 1;
         WinSetPointer(HWND_DESKTOP,
                    WinQuerySysPointer(HWND_DESKTOP, SPTR_SIZEWE, FALSE));
         dprintf("drive><folder\n");
      } else if (x <= pam->pro.gen.pswp[27].x &&  // x tra lbox file e folder
                 x >= (pam->pro.gen.pswp[25].x + pam->pro.gen.pswp[25].cx)) {
         if (!pam->szCtl || pam->szCtl == 1) pam->szCtl = 3;
         WinSetPointer(HWND_DESKTOP,
                    WinQuerySysPointer(HWND_DESKTOP, SPTR_SIZEWE, FALSE));
         dprintf("folder><file\n");
      } else if (pam->szCtl % 2) {
         dprintf("y compatibile x no, szCtl dispari\n");
         pam->szCtl = 0;
         return WinDefDlgProc(hwnd, msg, mp1, mp2);
      } // end if
   } else if (pam->szCtl % 2) {
      dprintf("x, y non compatibili, szCtl dispari\n");
      pam->szCtl = 0;
      return WinDefDlgProc(hwnd, msg, mp1, mp2);
   } // end if
   if (!pam->szCtl) {              // non in fase di trascinamento
      oldx = 0;
      return WinDefDlgProc(hwnd, msg, mp1, mp2);
   } // end if            -----       ridimensionamento lbox drive/folder
   if (pam->szCtl == 2 && (oldx - x > 4 || oldx - x < -4)) {
      SWP aswp[3];
      int drvmin = 22 + 3 * pam->pro.gen.cxFont;  // min largh lbox drive
      int fldmin = 22 + 16 * pam->pro.gen.cxFont; // min largh lbox folder
      int totcx = pam->pro.gen.pswp[23].cx + pam->pro.gen.pswp[25].cx;
      int drvmax = totcx - fldmin;                // max largh lbox drive
      oldx = x;
      dprintf("resize drive><folder\n");
      // larghezza lbox drive
      pam->pro.gen.pswp[23].cx = x - pam->pro.gen.pswp[23].x - 1;
      if (pam->pro.gen.pswp[23].cx > drvmax) pam->pro.gen.pswp[23].cx = drvmax;
      if (pam->pro.gen.pswp[23].cx < drvmin) pam->pro.gen.pswp[23].cx = drvmin;
      aswp[0] = pam->pro.gen.pswp[23];
      // coordinata x e larghezza lbox folder
      pam->pro.gen.pswp[25].x = pam->pro.gen.pswp[26].x =
                                aswp[0].x + aswp[0].cx + 2;
      pam->pro.gen.pswp[25].cx = totcx - aswp[0].cx;
      aswp[1] = pam->pro.gen.pswp[25];
      aswp[2] = pam->pro.gen.pswp[26];
      WinSetMultWindowPos(WinQueryAnchorBlock(hwnd), aswp, 3);
      return (MRESULT)FALSE;
   } // end if           --------    ridimensionamento lbox folder/file
   if (pam->szCtl == 4 && (oldx - x > 4 || oldx - x < -4)) {
      SWP aswp[3];
      int filmin = 22 + 13 * pam->pro.gen.cxFont; // min largh lbox file
      int fldmin = 22 + 16 * pam->pro.gen.cxFont; // min largh lbox folder
      int totcx = pam->pro.gen.pswp[25].cx + pam->pro.gen.pswp[27].cx;
      int fldmax = totcx - filmin;                // max largh lbox folder
      oldx = x;
      dprintf("resize folder><file\n");
      // larghezza lbox folder
      pam->pro.gen.pswp[25].cx =  x - pam->pro.gen.pswp[25].x - 1;
      if (pam->pro.gen.pswp[25].cx > fldmax) pam->pro.gen.pswp[25].cx = fldmax;
      if (pam->pro.gen.pswp[25].cx < fldmin) pam->pro.gen.pswp[25].cx = fldmin;
      aswp[0] = pam->pro.gen.pswp[25];
      // coordinata x e larghezza lbox file
      pam->pro.gen.pswp[27].x = pam->pro.gen.pswp[28].x =
                                aswp[0].x + aswp[0].cx + 2;
      pam->pro.gen.pswp[27].cx = totcx - aswp[0].cx;
      aswp[1] = pam->pro.gen.pswp[27];
      aswp[2] = pam->pro.gen.pswp[28];
      WinSetMultWindowPos(WinQueryAnchorBlock(hwnd), aswp, 3);
      return (MRESULT)FALSE;
   } // end if
   return (MRESULT)FALSE;
}


MRESULT ProcessMotionStart (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
      dprintf("motion start\n");
   if (pam->szCtl) {
      pam->szCtl++;
      WinSetCapture(HWND_DESKTOP, hwnd);
      //return (MRESULT)FALSE;
   } // end if
   return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

MRESULT ProcessMotionEnd (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   dprintf("motion end\n");
   if (pam->szCtl) {
      pam->szCtl = 0;
      WinSetPointer(HWND_DESKTOP,
                    WinQuerySysPointer(HWND_DESKTOP, SPTR_ARROW, FALSE));
      WinSetCapture(HWND_DESKTOP, NULLHANDLE);
//      return (MRESULT)FALSE;
   } // end if
   return WinDefDlgProc(hwnd, msg, mp1, mp2);
}


//==========================================================================\
// controlla se il mouse Š ancora sul controllo che ha originato il msg     |
// se Š al di fuori ferma il timer, cancella il testo nella statusbar       |
// e setta a NULLHANDLE l'handle della finestra originatrice dell'HELP      |
//==========================================================================/

MRESULT ProcessTimer(HWND hwnd, ULONG ulid) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   POINTL ptl;
   if (ulid == TID_CONTEXTHELP) {
      WinQueryPointerPos(HWND_DESKTOP, &ptl);
      // si puo' anche memorizzare posizione in WM_ADJUSTWINDOWPOS
      WinMapWindowPoints(HWND_DESKTOP, hwnd, &ptl, 1);
      if (pam->hCtlHelp != WinWindowFromPoint(hwnd, &ptl, FALSE)) {
         pam->hCtlHelp = NULLHANDLE;
         WinStopTimer(WinQueryAnchorBlock(hwnd), hwnd, TID_CONTEXTHELP);
         WinSetDlgItemText(hwnd, SBARMSG, "");
      } // end if
   } // end if
   return (MRESULT)FALSE;
}


// simula evento doppioclick in una listbox

MRESULT ProcessLBoxBtnUp(HWND hwnd, LONG lId, MPARAM mp2) {
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
   if (pam->pro.sel.monoclick == LN_SELECT)
      WinSendMsg(hwnd, WM_CONTROL, MPFROM2SHORT(lId, LN_ENTER), mp2);
   return (MRESULT)FALSE;
}
