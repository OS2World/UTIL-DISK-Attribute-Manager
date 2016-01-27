//==========================================================================\
// window.c : funzioni per il ridimensionamento dei controlli e per         |
// l'aggiornamento dei parametri di presentazione                           |
// VOID ResizeControls(HWND hwnd, SHORT cxOld, SHORT cxNew, SHORT cyNew,    |
//                     PATTMAN pam);                                        |
// VOID SetSubjectLimit(HWND hwnd, LONG length);                            |
// VOID EnableBrowsing(HWND hwnd, PATTMAN pam, BOOL flag);                  |
// VOID SwitchBrowserVisibility(HWND hwnd, BOOL flag);                      |
// VOID SetDialogFont(HWND hwnd, PPREF_GEN pGen, BOOL flag);                |
// MRESULT ShowContextMenu(HWND hwnd, HWND hMenu);                          |
// VOID SwitchSelectionMode(HWND hwnd, BOOL flag);                          |
// VOID SwitchEditMode(HWND hwnd, BOOL flag, PATTMAN pam);                  |
// VOID SwitchCheckBoxStyle(HWND hwnd, BOOL flag);                          |
// VOID Iconize(HWND hwnd, BOOL flag, BOOL hpfs);                           |
// VOID SetMenuCondCascadeStyle(HWND hMenu, SHORT sSubMenuID);              |
// VOID SetMenuDefaults(HWND hMenu, SHORT sSubMenu,                         |
//                      SHORT sUnchkID, SHORT sCheckID);                    |
// VOID InitEditMenu(HWND hwnd, HWND hMenu, PATTMAN pam);                   |
// VOID EnableImportMenuItems(HWND hwnd, PATTMAN pam, PAM_PRO ppref);       |
//==========================================================================/

#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#include <efdlg.h>
#include <mledlg.h>
#include <listbox.h>
#include <spinbtn.h>
#include <string.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"


//==========================================================================\
// ridimensiona tutti i controlli contenuti nella finestra                  |
// parametri: HWND hwnd     handle della frame window                       |
//            cxOld, cyOld  vecchie dimensioni della frame                  |
//            cxNew, cyNew  nuove dimensioni della frame                    |
//            init TRUE se viene richiamato durante l'inizializzazione      |
// In fase di inizializzazione memorizza dimensioni minime dialogo e default|
// dei controlli.                                                           |
// Se Š in browse mode ignora le finestre non visualizzate riguardo         |
// i cambiamenti relativi all'altezza                                       |
//==========================================================================/

VOID ResizeControls(HWND hwnd, SHORT cxOld, SHORT cxNew, SHORT cyNew,
                    PATTMAN pam) {
   static ULONG fw;      // cx font
   static ULONG fh;      // cy font
   static ULONG cytb;    // cy titlebar
   PSWP pswp = pam->pro.gen.pswp;

   if (!cytb) cytb = WinQuerySysValue(HWND_DESKTOP, SV_CYTITLEBAR) + 6;
   if (!fw) {                                     // inizializzazione
      pswp[0].hwnd = WinWindowFromID(hwnd, STB_ACCESSED);
      pswp[1].hwnd = WinWindowFromID(hwnd, STB_CREATED);
      pswp[2].hwnd = WinWindowFromID(hwnd, STB_WRITTEN);
      pswp[3].hwnd = WinWindowFromID(hwnd, TXT_EASIZE);
      pswp[4].hwnd = WinWindowFromID(hwnd, TXT_FSIZE);
      pswp[5].hwnd = WinWindowFromID(hwnd, CBOX_A);
      pswp[6].hwnd = WinWindowFromID(hwnd, CBOX_H);
      pswp[7].hwnd = WinWindowFromID(hwnd, CBOX_R);
      pswp[8].hwnd = WinWindowFromID(hwnd, CBOX_S);
      pswp[9].hwnd = WinWindowFromID(hwnd, BTN_OPEN);
      pswp[10].hwnd = WinWindowFromID(hwnd, BTN_CLOSE);
      pswp[11].hwnd = WinWindowFromID(hwnd, BTN_SAVE);
      pswp[12].hwnd = WinWindowFromID(hwnd, BTN_IMP);
      pswp[13].hwnd = WinWindowFromID(hwnd, BTN_REP);
      pswp[14].hwnd = WinWindowFromID(hwnd, BTN_FIND);
      pswp[15].hwnd = WinWindowFromID(hwnd, BTN_DOWN);
      pswp[16].hwnd = WinWindowFromID(hwnd, BTN_UP);
      pswp[17].hwnd = WinWindowFromID(hwnd, MLE_KEY);
      pswp[18].hwnd = WinWindowFromID(hwnd, TXT_KEY);
      pswp[19].hwnd = WinWindowFromID(hwnd, MLE_COMNT);
      pswp[20].hwnd = WinWindowFromID(hwnd, TXT_COMNT);
      pswp[21].hwnd = WinWindowFromID(hwnd, TXT_SUBJ);
      pswp[22].hwnd = WinWindowFromID(hwnd, EF_SUBJ);
      pswp[23].hwnd = WinWindowFromID(hwnd, LB_DRIVE);
      pswp[24].hwnd = WinWindowFromID(hwnd, TXT_DRIVE);
      pswp[25].hwnd = WinWindowFromID(hwnd, LB_FOLDER);
      pswp[26].hwnd = WinWindowFromID(hwnd, TXT_FOLDER);
      pswp[27].hwnd = WinWindowFromID(hwnd, LB_FILE);
      pswp[28].hwnd = WinWindowFromID(hwnd, TXT_FILE);
      pswp[29].hwnd = WinWindowFromID(hwnd, GRP_ORDATTR);
      pswp[30].hwnd = WinWindowFromID(hwnd, SBARMSG);
      pswp[31].hwnd = WinWindowFromID(hwnd, BTN_LOG);

      // GRP_ORDATTR x, y
      pswp[29].x = 5; pswp[29].y = 36;
      // STB_ACCESSED STB_CREATED - STB_WRITTEN - TXT_EASIZE - TXT_FSIZE
      pswp[0].x = pswp[1].x = pswp[2].x = 9;
      pswp[3].x = pswp[4].x = 12;
      pswp[0].y = 38;
      // flag tutti SWP_SIZE | SWP_MOVE tranne bottoni e statusbar
      pswp[0].fl = pswp[1].fl = pswp[2].fl = pswp[3].fl = pswp[4].fl =
      pswp[5].fl = pswp[6].fl = pswp[7].fl = pswp[8].fl = pswp[17].fl =
      pswp[18].fl = pswp[19].fl = pswp[20].fl = pswp[21].fl = pswp[22].fl =
      pswp[23].fl = pswp[24].fl = pswp[25].fl = pswp[26].fl = pswp[27].fl =
      pswp[28].fl = pswp[29].fl = pswp[30].fl = SWP_SIZE | SWP_MOVE;
      pswp[9].fl = pswp[10].fl = pswp[11].fl = pswp[12].fl = pswp[13].fl =
      pswp[14].fl = pswp[15].fl = pswp[16].fl = pswp[31].fl = SWP_MOVE;
      // bottone log, listbox log e helpTXT:
      pswp[31].x = pswp[31].y = 5;
      pswp[30].x = 36; pswp[30].y = 5; pswp[30].cy = 28;
      pswp[31].cy = 26;
      // CBOX_A
      pswp[5].x = 9;
      // coordinate y bottoni:BTN_OPEN - BTN_CLOSE (cx e cy vengono lasciati a 0 perch‚ autosize)
      pswp[9].y = pswp[10].y = pswp[11].y = pswp[12].y = pswp[13].y =
      pswp[14].y = pswp[15].y = 36;
      pswp[16].y = 50;
      // y MLE EAs
      pswp[17].y = 67; pswp[19].y = 5;
      // LBOX e STATIC DRIVE
      pswp[23].x = pswp[24].x = 5;
      // larghezza listbox drive e folder:
      cxOld = cxNew;
      pswp[23].cx = pam->pro.gen.cxDrv;
      pswp[25].cx = pam->pro.gen.cxFld;
      if (!pswp[25].cx) pswp[25].cx = 22 + 30 * pam->pro.gen.cxFont;
   } // end if ---                 >>>    cambiamento font:
   if (fw != pam->pro.gen.cxFont || fh != pam->pro.gen.cyFont) {
      fw = pam->pro.gen.cxFont; fh = pam->pro.gen.cyFont;
      // larghezza STB_ACCESSED- STB_CREATED - ecc
      pswp[0].cx = pswp[1].cx = pswp[2].cx = 32 * fw;
      pswp[3].cx = pswp[4].cx = 31 * fw;
      // larghezza GRP_ORDATTR
      pswp[29].cx = pswp[0].cx + 8;
      // altezza STB_ACCESSED, altri testi statici e entryfield
      pswp[0].cy = pswp[1].cy = pswp[2].cy = pswp[3].cy = pswp[4].cy =
      pswp[18].cy = pswp[20].cy = pswp[21].cy =  pswp[24].cy = pswp[26].cy =
      pswp[28].cy = 4 + fh;
      pswp[22].cy =  fh + 1;
      // coordinata y STB_CREATED - TXT_FSIZE
      pswp[1].y = 1 + pswp[0].y + pswp[0].cy;
      pswp[2].y = 1 + pswp[1].y + pswp[1].cy;
      pswp[3].y = 1 + pswp[2].y + pswp[2].cy;
      pswp[4].y = 1 + pswp[3].y + pswp[3].cy;
      // coordinata x checkbox attributi
      pswp[6].x = 9 + 8 * fw; pswp[7].x = 9 + 16 * fw; pswp[8].x = 9 + 24 * fw;
      // coordinata y checkbox attributi
      pswp[5].y = pswp[6].y = pswp[7].y = pswp[8].y =
      1 + pswp[4].y + pswp[4].cy;
      // larghezza checkbox attributi
      pswp[5].cx = pswp[6].cx = pswp[7].cx = pswp[8].cx = 7 * fw;
      // altezza checkbox attributi
      pswp[5].cy = pswp[6].cy = pswp[7].cy = pswp[8].cy = fh + 5 > 21 ?
                   fh + 5: 21;
      // altezza GRP_ORDATTR
      pswp[29].cy = pswp[5].y + pswp[5].cy + fh - pswp[0].y + 5;
      // coordinate x bottoni e KeyPhrases e TXT_SUBJ
      pswp[9].x = pswp[10].x = pswp[17].x = pswp[18].x = pswp[21].x =
      8 + pswp[29].cx;
      pswp[11].x = pswp[10].x + 29; pswp[12].x = pswp[11].x + 29;
      pswp[13].x = pswp[12].x + 29; pswp[14].x = pswp[13].x + 29;
      pswp[15].x = pswp[16].x = pswp[14].x + 29;
      // coordinate y listbox
      pswp[23].y = pswp[25].y = pswp[27].y = pswp[29].y + pswp[29].cy + 5;
      // cx TXT_SUBJ, y TXT_SUBJ e EF_SUBJ
      pswp[21].y = pswp[23].y - 5 - pswp[21].cy;
      pswp[22].y = pswp[21].y + 2;
      pswp[21].cx = 8 * fw;
      // y TXT_KEY - TXT_COMNT
      pswp[18].y = pswp[20].y = pswp[21].y - 3 - pswp[21].cy;
      // cx - cy MLE_KEY cx TXT_KEY - TXT_COMNT
      pswp[17].cx = 163; pswp[17].cy = pswp[18].y - 3 - pswp[17].y;
      pswp[18].cx = pswp[20].cx = 13 * fw;
      pswp[19].cy = pswp[20].y - 3 - pswp[19].y;
      // x TXT_COMNT - MLE_COMNT - EF_SUBJ
      pswp[19].x = pswp[20].x = pswp[17].x + pswp[17].cx + 2;
      pswp[22].x = pswp[21].x + pswp[21].cx + 3;
      // larghezza Drive, Folder, File
      pswp[24].cx = 6 * fw + 4; pswp[26].cx = 7 * fw + 4;
      pswp[28].cx = 5 * fw + 4;
      pswp[30].cx = pswp[19].x - 38;
      pswp[30].cx - 2;
   } /* endif */
   if (!pam->cyNoBrowse) { // solo se Š visibile finestra browsing
      pswp[24].y = pswp[26].y = pswp[28].y = cyNew - cytb - pswp[24].cy;
      pswp[23].cy = pswp[25].cy = pswp[27].cy = pswp[24].y - pswp[23].y - 1;
   } // endif
   // cx lbox drive
   dprintf("larg drive: %d - larg folder: %d\n",pswp[23].cx, pswp[25].cx);
   if ((pswp[23].cx =  // larghezza lb drive controlla non sia < min
       (INT)((float)pswp[23].cx * (float)cxNew / (float)cxOld + 0.49999)) <
       (22 + 3 * fw)) pswp[23].cx = 22 + 3 * fw;
   pswp[25].x = pswp[26].x = pswp[23].x + pswp[23].cx + 2;  // x lbox folder
   if ((pswp[25].cx =  // larghezza lb folder controlla non sia < min
       (INT)((float)pswp[25].cx * (float)cxNew / (float)cxOld + 0.49999)) <
       (22 + 16 * fw)) pswp[25].cx = 22 + 16 * fw;
   dprintf("larg drive: %d - larg folder: %d\n",pswp[23].cx, pswp[25].cx);
   pswp[27].x = pswp[28].x = pswp[25].x + pswp[25].cx + 2;    // x lbox file
   pswp[27].cx = cxNew - pswp[27].x - 5;   // cx lbox file
   pswp[22].cx = cxNew - pswp[22].x - 8;   // cx EF_SUBJ
   pswp[19].cx = cxNew - pswp[19].x - 5;   // cx MLE_CMNT
   WinSetMultWindowPos(WinQueryAnchorBlock(hwnd), pswp, 32);
}


//==========================================================================\
// imposta la larghezza massima del campo subject                           |
// parametri:                                                               |
// HWND hwnd   = handle dialogo                                             |
// LONG length = lunghezza da impostare                                     |
//==========================================================================/

VOID SetSubjectLimit(HWND hwnd, LONG length) {
   if (length > 0) {
      DlgEFSetTxtLimit(hwnd, EF_SUBJ, length);
   } else {
      DlgEFSetTxtLimit(hwnd, EF_SUBJ, 40);
   } /* endif */
}


//==========================================================================\
// abilita/disabilita la finestra al browsing                               |
// parametri:                                                               |
// HWND hwnd   = handle dialogo principale                                  |
// PATTMAN pam =                                                            |
// BOOL flag   = se TRUE viene abilitato browse, FALSE disabilitato         |
//==========================================================================/

VOID  EnableBrowsing(HWND hwnd, PATTMAN pam, BOOL flag) {
   static MENUITEM mitem;
   HWND hMinMax = WinWindowFromID(hwnd, FID_MINMAX);

   // con la prima esecuzione ricava dati struttura pulsante max
   if (pam->cyNoBrowse == -2)
      WinSendMsg(hMinMax, MM_QUERYITEM, MPFROM2SHORT(SC_MAXIMIZE, 0),
                 MPFROMP(&mitem));   // memorizza struttura pulsante max
   // abilita/disabilita checkmark dal menu Browse
   WinCheckMenuItem(pam->hMMain, MN_BROWSE, flag); 
   WinCheckMenuItem(pam->hMEdit, MN_BROWSE, flag);
   // scambia i pulsanti apertura/chiusura browsing
   DlgShowCtl(hwnd, BTN_OPEN, !flag);
   DlgShowCtl(hwnd, BTN_CLOSE, flag);
   // nasconde/visualizza finestre browsing
   SwitchBrowserVisibility(hwnd, flag);
   if (flag && pam->cyNoBrowse == -2) { // avviato in browse mode
      WinSetWindowPos(hwnd, 0, 0, 0, pam->pro.swp.cx, pam->pro.swp.cy, SWP_SIZE);
   } else if (flag) {                   // browse mode!!!
      if (pam->cyNoBrowse > 0)
         WinSendMsg(hMinMax, MM_INSERTITEM, MPFROMP(&mitem), NULL);
      if (pam->pro.gen.pswp[24].y == 0) // prima occorrenza browse mode
         pam->cyNoBrowse = -2;
      else
         pam->cyNoBrowse = -1;
      WinSetWindowPos(hwnd, 0, 0, 0, pam->pro.swp.cx, pam->pro.swp.cy, SWP_SIZE);
   } else {                          // se non Š in browse mode
      // se la finestra Š massimizzata ripristina la dimensione normale
      if (WS_MAXIMIZED & WinQueryWindowULong(hwnd, QWL_STYLE)) {
         pam->cyNoBrowse = 0;        // resetta per ridimensionamento controlli
         WinSetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_RESTORE);
      } // end if --- calcola altezza finestra in modo nobrowse
      pam->cyNoBrowse = WinQuerySysValue(HWND_DESKTOP, SV_CYTITLEBAR) + 77 +
                        6 * pam->pro.gen.cyFont +
                        (pam->pro.gen.cyFont + 7 > 21?
                        pam->pro.gen.cyFont + 7 : 21);
      WinSetWindowPos(hwnd, HWND_BOTTOM, 0, 0, pam->pro.swp.cx,
                      pam->cyNoBrowse, SWP_SIZE);
      WinSendMsg(hMinMax, MM_REMOVEITEM, // rimuove pulsante massimizzazione
                 MPFROM2SHORT(SC_MAXIMIZE, FALSE), NULL);
   } /* endif */
   WinSendMsg(hwnd, WM_UPDATEFRAME, (flag? MPFROMLONG(FCF_MINMAX):
              MPFROMLONG(FCF_MINBUTTON)), NULL);
}


//==========================================================================\
// rende visibili/invisibili le finestre di browsing                        |
//==========================================================================/

VOID SwitchBrowserVisibility(HWND hwnd, BOOL flag) {

   DlgShowCtl(hwnd, TXT_DRIVE, flag);
   DlgShowCtl(hwnd, LB_DRIVE, flag);
   DlgShowCtl(hwnd, TXT_FOLDER, flag);
   DlgShowCtl(hwnd, LB_FOLDER, flag);
   DlgShowCtl(hwnd, TXT_FILE, flag);
   DlgShowCtl(hwnd, LB_FILE, flag);
}


//==========================================================================\
// setta un nuovo font memorizzandone la massima larghezza e altezza        |
// parametri:                                                               |
// HWND hwnd      = handle finestra                                         |
// PPREF_GEN pGen = indirizzo preferenze generali                           |
// BOOL flag      = TRUE imposta nuovo font, FALSE legge solo parametri font|
// Š FALSE quando il nuovo font Š stato impostato tramite drag & drop       |
//==========================================================================/

VOID SetDialogFont(HWND hwnd, PPREF_GEN pGen, BOOL flag) {
   HPS hps;
   FONTMETRICS fm;
   int newx, newy;        // nuove dimensioni dialogo
   int maxX, maxY;        // dimensioni schermo
   SWP swp;
   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);

   if (flag) WinSetPresParam(hwnd, PP_FONTNAMESIZE, // setta il font del dlg
                   sstrlen(pGen->font) + 1, (PVOID)(pGen->font));
   hps = WinGetPS(hwnd);
   GpiQueryFontMetrics(hps, sizeof(FONTMETRICS), &fm);
   // se non prima occorrenza aggiorna dim finestra secondo dim nuovo font:
   if (pGen->cxFont) {
      WinQueryWindowPos(hwnd, &swp);
      newx = 180 + (INT)((float)(swp.cx - 180.0) * (float)fm.lAveCharWidth /
              (float)pGen->cxFont + 0.49999);
      newy = 120 + (INT)((float)(swp.cy - 120.0) * (float)fm.lMaxBaselineExt /
              (float)pGen->cyFont + 0.49999);
      maxX = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
      maxY = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);
      if (newx > maxX) newx = maxX;
      if (newy > maxY) newy = maxY;
   } else {
      newx = swp.cx; newy = swp.cy; // per evitare ridimensionamento finestra
   } /* endif */
   if (pam->cyNoBrowse > 0) { // se necessario aggiorna pam->cyNoBrowse
      pam->cyNoBrowse = WinQuerySysValue(HWND_DESKTOP, SV_CYTITLEBAR) + 77 +
                        6 * fm.lMaxBaselineExt + (fm.lMaxBaselineExt + 7 > 21?
                        fm.lMaxBaselineExt + 7 : 21);
      pam->pro.gen.pswp[24].y = 0; // forza successivo ricalcolo dim lbox
      // aggiorna anche cy modalit… browse
      pam->pro.swp.cy = 120 + (INT)((float)(pam->pro.swp.cy - 120.0) *
                   (float)fm.lMaxBaselineExt / (float)pGen->cyFont + 0.49999);
      if (pam->pro.swp.cy > maxY) pam->pro.swp.cy = maxY;
   } // end if
   pGen->cxFont = fm.lAveCharWidth;// MaxCharInc;
   pGen->cyFont = fm.lMaxBaselineExt;
   // max tra altezza font e icona (quest'ultima Š alta 15 pixel)
   pGen->cyItem = pGen->cyFont > 15? pGen->cyFont: 15;
   pGen->clrBack = WinQuerySysColor(HWND_DESKTOP, SYSCLR_ENTRYFIELD, 0L);
   pGen->clrFore = WinQuerySysColor(HWND_DESKTOP, SYSCLR_WINDOWTEXT, 0L);
   pGen->clrHiBack = WinQuerySysColor(HWND_DESKTOP, SYSCLR_HILITEBACKGROUND, 0L);
   pGen->clrHiFore = WinQuerySysColor(HWND_DESKTOP, SYSCLR_HILITEFOREGROUND, 0L);
   WinReleasePS(hps);
   // ricalcola dimensioni minime dialogo
   if ((pam->min.x = pam->pro.gen.cxFont * 60 + 183) >
       WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN))
      pam->min.x = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
   if ((pam->min.y = pam->pro.gen.cyFont * 18 + 72) >
       WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN))
      pam->min.y = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);
   if (newx != swp.cx || newy != swp.cy)
      WinSetWindowPos(hwnd, 0, 0, 0, newx, newy, SWP_SIZE);
   DlgLboxSetItemHeight(hwnd, LB_FOLDER, pGen->cyItem);
}


//==========================================================================\
// mostra menu contestuale                                                  |
//==========================================================================/

MRESULT ShowContextMenu(HWND hwnd, HWND hMenu) {
   POINTL ptl;
   WinQueryMsgPos(WinQueryAnchorBlock(hwnd), &ptl);
   WinPopupMenu(HWND_DESKTOP, hwnd, hMenu, ptl.x, ptl.y, 0,
                PU_HCONSTRAIN | PU_VCONSTRAIN | PU_KEYBOARD |
                PU_MOUSEBUTTON1 | PU_MOUSEBUTTON2 | PU_MOUSEBUTTON3);
   return (MRESULT) FALSE;
}

//==========================================================================\
// cambia la modalit… di selezione nella listbox file                       |
// parametri:                                                               |
// BOOL flag = TRUE -> selezione estesa, FALSE ->selezione singola          |
//==========================================================================/

VOID SwitchSelectionMode(HWND hwnd, BOOL flag) {
   if (flag) {
      DlgSetCtlBits(hwnd, LB_FILE, QWL_STYLE, LS_EXTENDEDSEL, LS_EXTENDEDSEL);
   } else {
      PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);
      int idx = DlgLboxQuerySelectedItem(hwnd, LB_FILE);
      ProcessMenuDeselAll(hwnd, pam);
      if (idx != LIT_NONE)
         DlgLboxSelectItem(hwnd, LB_FILE, idx);
   } /* endif */
}


//==========================================================================\
// cambia la modalit… delle finestre di editazione da readonly a editazione |
// e viceversa, disabilita/abilita voce EDIT del menu contestuale           |
// parametri:                                                               |
// HWND hwnd = handle dialogo                                               |
// BOOL flag = TRUE setta readonly, FALSE editazione attiva                 |
// PATTMAN pam = indirizzo struutra dati applicazione                       |
//==========================================================================/

VOID SwitchEditMode(HWND hwnd, BOOL flag, PATTMAN pam) {
   pam->pro.gen.ronly = flag;
   DlgEFSetReadOnly(hwnd, EF_SUBJ, flag);
   DlgMleSetReadOnly(hwnd, MLE_COMNT, flag);
   DlgMleSetReadOnly(hwnd, MLE_KEY, flag);
   SwitchCheckBoxStyle(hwnd, flag);
   WinCheckMenuItem(pam->hMMain, MN_READ, flag); 
   WinCheckMenuItem(pam->hMEdit, MN_READ, flag);
   WinEnableMenuItem(pam->hMMain, MN_SAVE, !flag);
   WinEnableMenuItem(pam->hMEdit, MN_SAVE, !flag);
   WinEnableControl(hwnd, BTN_SAVE, !flag);
}


//==========================================================================\
// cambia lo stato dei pulsanti degli attributi da autocheckbox a checkbox  |
// secondo se si Š in modalit… editazione o readonly                        |
// parametri:                                                               |
// BOOL flag = TRUE -> cambia lo stile delle checkbox da AUTOCHECKBOX a     |
//                     CHECKBOX                                             |
//             FALSE -> il contrario                                        |
//==========================================================================/

VOID SwitchCheckBoxStyle(HWND hwnd, BOOL flag) {
   USHORT id;
   ULONG OldStyle, NewStyle;
   // cambia lo stile delle checkbox attributi
   if (flag) {
      OldStyle = BS_AUTOCHECKBOX;
      NewStyle = BS_CHECKBOX;
   } else {
      OldStyle = BS_CHECKBOX;
      NewStyle = BS_AUTOCHECKBOX;
   } /* endif */
   for (id = CBOX_A; id <= CBOX_R; ++id) {
      DlgSetCtlBits(hwnd, id, QWL_STYLE, 0L, OldStyle);
      DlgSetCtlBits(hwnd, id, QWL_STYLE,
                       NewStyle, NewStyle);
   } /* endfor */
   // cambia lo stile delle finestre di editazione
}


//==========================================================================\
// nasconde alcuni controlli per ottenere la corretta visualizzazione       |
// dell'icona quando minimizzato sulla scrivania                            |
//==========================================================================/

VOID Iconize(HWND hwnd, BOOL flag, BOOL hpfs) {
   DlgShowCtl(hwnd, STB_WRITTEN, flag);
   if (hpfs) {
      DlgShowCtl(hwnd, STB_CREATED, flag);
      DlgShowCtl(hwnd, STB_ACCESSED, flag);
   } /* endif */
}


//==========================================================================\
// imposta lo stile del submenu a MS_CONDITIONALCASCADE                     |
// Parametri:                                                               |
// HWND hMenu       = handle menu parent                                    |
// SHORT sSubMenuID = ID submenu                                            |
//==========================================================================/

VOID SetMenuCondCascadeStyle(HWND hMenu, SHORT sSubMenuID) {
   MENUITEM mItem;
   WinSendMsg(hMenu, MM_QUERYITEM, MPFROM2SHORT(sSubMenuID, TRUE),
              MPFROMP(&mItem));
   WinSetWindowBits(mItem.hwndSubMenu, QWL_STYLE, MS_CONDITIONALCASCADE,
                    MS_CONDITIONALCASCADE);
}


//==========================================================================\
// Imposta le voci di default dei submenu con stile MS_CONDITIONALCASCADE   |
// Parametri:                                                               |
// HWND hMenu     = handle Menu                                             |
// SHORT sUnchkID = ID item cui togliere il checkmark                       |
// SHORT sCheckID = ID item cui aggiungere il checkmark                     |
//==========================================================================/

VOID SetMenuDefaults(HWND hMenu, SHORT sSubMenu,
                     SHORT sUnchkID, SHORT sCheckID) {
   MENUITEM mItem;
   WinSendMsg(hMenu, MM_QUERYITEM, MPFROM2SHORT(sSubMenu, TRUE),
              MPFROMP(&mItem));
   WinCheckMenuItem(hMenu, sUnchkID, FALSE);
   WinSendMsg(mItem.hwndSubMenu, MM_SETDEFAULTITEMID,
              MPFROMLONG((LONG)sCheckID), MPFROMLONG(0L));
   WinCheckMenuItem(hMenu, sCheckID, TRUE);
}


//==========================================================================\
// Inizializza il menu di editazione secondo dati clipboard e presenza      |
// testo selezionato. Se il menu Š orignato da MLE_KEY disabilita "Import"  |
// parametri:                                                               |
// HWND hwnd    = handle finestra principale                                |
// HWND hMenu   = handle menu                                               |
// SHORT ctrlID = ID controllo                                              |
//==========================================================================/

VOID InitEditMenu(HWND hwnd, HWND hMenu, PATTMAN pam) {
   ULONG ulSelTxt;
   // menu UNDO CUT-COPY-CLEAR
   if (pam->sMenuFrom == EF_SUBJ) {
      ulSelTxt = DlgEFQuerySelection(hwnd, EF_SUBJ); //testo selezionato
      WinEnableMenuItem(hMenu, MN_UNDO, pam->fsp.subjChanged); // UNDO
   } else {
      ulSelTxt = DlgMleQuerySelection(hwnd, pam->sMenuFrom);
      WinEnableMenuItem(hMenu, MN_UNDO,
                        DlgMleQueryChanged(hwnd, pam->sMenuFrom));
   } // endif
   ulSelTxt = (HIUSHORT(ulSelTxt) - LOUSHORT(ulSelTxt))? TRUE: FALSE;
   WinEnableMenuItem(hMenu, MN_CUT, ulSelTxt);
   WinEnableMenuItem(hMenu, MN_COPY, ulSelTxt);
   WinEnableMenuItem(hMenu, MN_CLEAR, ulSelTxt);
   // menu item PASTE
   WinEnableMenuItem(hMenu, MN_PASTE,
                     WinQueryClipbrdFmtInfo(WinQueryAnchorBlock(hwnd),
                     CF_TEXT, NULL));
   // menu import
   WinEnableMenuItem(hMenu, SUBMN_IMPORT, pam->sMenuFrom != MLE_KEY);
}


//==========================================================================\
// Abilita-disabilita le varie voci del menu di importazione                |
// Parametri: HWND hwnd, PATTMAN pam, PAM_PRO ppref                         |
//==========================================================================/

VOID EnableImportMenuItems(HWND hwnd, PATTMAN pam, PAM_PRO ppref) {
   WinEnableMenuItem(pam->hMEdit, MN_4, ppref->imp.quattro[0]);
   WinEnableMenuItem(pam->hMEdit, MN_ID_DIZ, ppref->imp.unarc.ulItems);
   WinEnableMenuItem(pam->hMEdit, MN_ID_UDEF, ppref->imp.ftoimp[0]);
}
