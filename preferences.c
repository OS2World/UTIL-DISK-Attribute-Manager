//==========================================================================\
// preferences.c : funzioni dialoghi settaggio preferenze                   |
//==========================================================================/

#define INCL_WINSTDFONT
#define INCL_WIN
#include <os2.h>
#include <notebook.h>
#include <spinbtn.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "preferences.h"
#include "prefmessages.h"

//==========================================================================\
// procedura dialogo blocco impostazioni                                    |
//==========================================================================/

MRESULT EXPENTRY PrefDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   static PAM_PRO ppref;
   static HWND hPages[7];
   ULONG pageID;

   switch (msg) {
      CHAR buf[FACESIZE];

      case WM_INITDLG:
         ppref = (PAM_PRO)PVOIDFROMMP(mp2);
         // imposta il font della barra del titolo:
         PrfQueryProfileString(HINI_USERPROFILE, "PM_SystemFonts",
                               "WindowTitles", "9.WarpSans", buf, FACESIZE);
         WinSetPresParam(WinWindowFromID(hwnd, FID_TITLEBAR), PP_FONTNAMESIZE,
                         sstrlen(buf) + 1, (PVOID)(buf));
         // inserisce la prima pagina : General
         pageID = DlgNtbkInsertPage(hwnd, PREF_NOTEBOOK, 0L,
                                    BKA_AUTOPAGESIZE | BKA_MAJOR |
                                    BKS_TABTEXTCENTER, BKA_FIRST);
         hPages[0] = WinLoadDlg(hwnd, hwnd, (PFNWP)GenDlgProc, 0L,
                                PREF_GENERAL, &ppref->gen);
         DlgNtbkSetPageWinHwnd(hwnd, PREF_NOTEBOOK, pageID, hPages[0]);
         DlgNtbkSetTab(hwnd, PREF_NOTEBOOK, pageID, _SZ_GENERAL);
         // inserisce la seconda pagina : Selection
         pageID = DlgNtbkInsertPage(hwnd, PREF_NOTEBOOK, pageID,
                                    BKA_AUTOPAGESIZE | BKA_MAJOR |
                                    BKS_TABTEXTCENTER, BKA_NEXT);
         hPages[1] = WinLoadDlg(hwnd, hwnd, (PFNWP)SelDlgProc, 0L, PREF_SEL,
                                &ppref->sel);
         DlgNtbkSetPageWinHwnd(hwnd, PREF_NOTEBOOK, pageID, hPages[1]);
         DlgNtbkSetTab(hwnd, PREF_NOTEBOOK, pageID, _SZ_SELECTION);
         // inserisce la terza pagina : Import (1)
         pageID = DlgNtbkInsertPage(hwnd, PREF_NOTEBOOK, pageID,
                                    BKA_AUTOPAGESIZE | BKA_STATUSTEXTON |
                                    BKA_MAJOR | BKS_TABTEXTCENTER, BKA_NEXT);
         hPages[2] = WinLoadDlg(hwnd, hwnd, (PFNWP)Imp1DlgProc, 0L,
                                PREF_IMPORT_1, &ppref->imp);
         DlgNtbkSetPageWinHwnd(hwnd, PREF_NOTEBOOK, pageID, hPages[2]);
         DlgNtbkSetTab(hwnd, PREF_NOTEBOOK, pageID, _SZ_IMPORT);
         DlgNtbkSetStatusLine(hwnd, PREF_NOTEBOOK, pageID, PG1OF2);
         // inserisce la quarta pagina : Import (2)
         pageID = DlgNtbkInsertPage(hwnd, PREF_NOTEBOOK, pageID,
                                    BKA_AUTOPAGESIZE | BKA_STATUSTEXTON,
                                    BKA_NEXT);
         hPages[3] = WinLoadDlg(hwnd, hwnd, (PFNWP)Imp2DlgProc, 0L,
                                PREF_IMPORT_2, &ppref->imp);
         DlgNtbkSetPageWinHwnd(hwnd, PREF_NOTEBOOK, pageID, hPages[3]);
         DlgNtbkSetStatusLine(hwnd, PREF_NOTEBOOK, pageID, PG2OF2);
         // inserisce la quinta pagina : Report (1)
         pageID = DlgNtbkInsertPage(hwnd, PREF_NOTEBOOK, pageID,
                                    BKA_AUTOPAGESIZE | BKA_STATUSTEXTON |
                                    BKA_MAJOR | BKS_TABTEXTCENTER, BKA_NEXT);
         hPages[4] = WinLoadDlg(hwnd, hwnd, (PFNWP)Rep1DlgProc, 0L,
                                PREF_REPORT_1, &ppref->rep);
         DlgNtbkSetPageWinHwnd(hwnd, PREF_NOTEBOOK, pageID, hPages[4]);
         DlgNtbkSetTab(hwnd, PREF_NOTEBOOK, pageID, _SZ_REPORT);
         DlgNtbkSetStatusLine(hwnd, PREF_NOTEBOOK, pageID, PG1OF2);
         // inserisce la sesta pagina : Report (2)
         pageID = DlgNtbkInsertPage(hwnd, PREF_NOTEBOOK, pageID,
                                    BKA_AUTOPAGESIZE | BKA_STATUSTEXTON,
                                    BKA_NEXT);
         hPages[5] = WinLoadDlg(hwnd, hwnd, (PFNWP)Rep2DlgProc, 0L,
                                PREF_REPORT_2, &ppref->rep);
         DlgNtbkSetPageWinHwnd(hwnd, PREF_NOTEBOOK, pageID, hPages[5]);
         DlgNtbkSetStatusLine(hwnd, PREF_NOTEBOOK, pageID, PG2OF2);
         // inserisce la settima pagina : Find
         pageID = DlgNtbkInsertPage(hwnd, PREF_NOTEBOOK, pageID,
                                    BKA_AUTOPAGESIZE | BKA_MAJOR |
                                    BKS_TABTEXTCENTER, BKA_NEXT);
         hPages[6] = WinLoadDlg(hwnd, hwnd, (PFNWP)FindDlgProc, 0L, PREF_FIND,
                                &ppref->find);
         DlgNtbkSetPageWinHwnd(hwnd, PREF_NOTEBOOK, pageID, hPages[6]);
         DlgNtbkSetTab(hwnd, PREF_NOTEBOOK, pageID, _SZ_FIND);

         DlgNtbkSetDimension(hwnd, PREF_NOTEBOOK,        // dimensiona le tab
                             ppref->gen.cxFont * 9 + 12,// lungh "selection"
                             ppref->gen.cyFont * 2,// altezza font + 4 pixel
                             BKA_MAJORTAB);
         // se la versione < warp 4 imposta Helv 8 come font di default:
         if (ppref->ulVer < 40) {
            int i;
            for (i = 0; i < sizeof(hPages)/sizeof(HWND); i++)
               WinSetPresParam(hPages[i], PP_FONTNAMESIZE, 7, (PVOID)"8.Helv");
         } /* endif */
         WinSetWindowPos(hwnd, HWND_BOTTOM, ppref->pos.x, ppref->pos.y, 0, 0,
                         SWP_MOVE | SWP_SHOW);
         break;
      case WM_CLOSE: 
         ReadNewSettings(hwnd, hPages, ppref);
         WinSendMsg(WinQueryWindow(hwnd, QW_OWNER), WM_UPD_SETTINGS, 0L, 0L); 
         WinDismissDlg(hwnd, FALSE);
         break;
      default: 
         return WinDefDlgProc(hwnd, msg, mp1, mp2);
         break;
   } /* endswitch */
   return (MRESULT) FALSE;
}


//==========================================================================\
// Legge nella struttura AM_PRO le nuove impostazioni                       |
// parametri:                                                               |
// PHWND pHpages = puntatore ad un array di handle pagine blocco settaggi   |
// PAM_PRO ppref = puntatore alla struttura di registrazione dei settaggi   |
//==========================================================================/

VOID ReadNewSettings(HWND hwnd, PHWND pHpages, PAM_PRO ppref) {
   SWP swp;

   // posizione dialogo
   WinQueryWindowPos(hwnd, &swp);
   ppref->pos.x = swp.x;
   ppref->pos.y = swp.y;

   // lettura prima pagina: (generale)
   ppref->gen.nologo = WinQueryButtonCheckstate(pHpages[0], CBOX_NOLOGO);
   ppref->gen.bubble = WinQueryButtonCheckstate(pHpages[0], CBOX_BUBBLE);
   DlgSpinQueryLong(pHpages[0], SPIN_SUBJ_LEN, &ppref->gen.subj);
   if (WinQueryButtonCheckstate(pHpages[0], CBOX_DEF_LEN))
      ppref->gen.subj *= -1;
   ppref->gen.ronly = WinQueryButtonCheckstate(pHpages[0], CBOX_READ_ONLY);
   ppref->gen.lastPath[0] = WinQueryButtonCheckstate(pHpages[0],
                                                     CBOX_SV_LASTPATH);
   WinQueryDlgItemText(pHpages[0], TXT_FONT, 256, ppref->gen.font);

   // lettura seconda pagina: (selezione)
   ppref->sel.extsel = WinQueryButtonCheckstate(pHpages[1], CBOX_EXT_SEL);
   ppref->sel.dir = WinQueryButtonCheckstate(pHpages[1], CBOX_SEL_ALL_INDIR);
   ppref->sel.monoclick =
      WinQueryButtonCheckstate(pHpages[1], CBOX_MOUSE_SINGLE)?
      LN_SELECT: LN_ENTER;
   ppref->sel.browse = WinQueryButtonCheckstate(pHpages[1], CBOX_FILE_WIN);
   ppref->sel.browsedir = WinQueryButtonCheckstate(pHpages[1], CBOX_ONLY_DIR);

   // lettura terza pagina: (import - 1)
   ppref->imp.autoimp = WinQueryButtonCheckstate(pHpages[2], CBOX_ENABLE_AIMP);
   ppref->imp.view = WinQueryButtonCheckstate(pHpages[2], CBOX_VIEW_ONLY);
   if (WinQueryButtonCheckstate(pHpages[2], RADIO_TO_SUBJ))
      ppref->imp.imp_to = RADIO_TO_SUBJ;
   else if (WinQueryButtonCheckstate(pHpages[2], RADIO_TO_CMNT))
      ppref->imp.imp_to = RADIO_TO_CMNT;
   else
      ppref->imp.imp_to = RADIO_TO_AUTO;
   if (WinQueryButtonCheckstate(pHpages[2], RADIO_IMP_AUTO))
      ppref->imp.def_imp = RADIO_IMP_AUTO;
   else if (WinQueryButtonCheckstate(pHpages[2], RADIO_IMP_4))
      ppref->imp.def_imp = RADIO_IMP_4;
   else if (WinQueryButtonCheckstate(pHpages[2], RADIO_FILE_ID_DIZ))
      ppref->imp.def_imp = RADIO_FILE_ID_DIZ;
   else if (WinQueryButtonCheckstate(pHpages[2], RADIO_USER_DEF))
      ppref->imp.def_imp = RADIO_USER_DEF;
   else
      ppref->imp.def_imp = RADIO_IMP_OTHER;
   WinQueryDlgItemText(pHpages[2], EF_DESCRIPTION, 256, ppref->imp.quattro);
   WinQueryDlgItemText(pHpages[2], EF_F_TOIMP, 256, ppref->imp.ftoimp);
   WinQueryDlgItemText(pHpages[2], EF_IMP_PROG, 256, ppref->imp.xtrprog);
   WinQueryDlgItemText(pHpages[2], EF_IMP_PARMS, 256, ppref->imp.xtrparms);

   // lettura quarta pagina: (import - 2)
   WinSendMsg(pHpages[3], WM_CLOSE_PREFERENCES, MPFROMLONG(0L), MPFROMLONG(0L));

   // lettura quinta pagina: (report - 1)
   ppref->rep.autorep = WinQueryButtonCheckstate(pHpages[4], CBOX_AUTO_REP);
   ppref->rep.repdir = WinQueryButtonCheckstate(pHpages[4], CBOX_ONLY_DIR_REP);
   if (WinQueryButtonCheckstate(pHpages[4], RADIO_SHOW))
      ppref->rep.view = RADIO_SHOW;
   else if (WinQueryButtonCheckstate(pHpages[4], RADIO_HIDE))
      ppref->rep.view = RADIO_HIDE;
   else
      ppref->rep.view = RADIO_SHOW_ONLYREP;
   if (WinQueryButtonCheckstate(pHpages[4], RADIO_SEL_FILES))
      ppref->rep.repmode = RADIO_SEL_FILES;
   else if (WinQueryButtonCheckstate(pHpages[4], RADIO_ALL_FILES))
      ppref->rep.repmode = RADIO_ALL_FILES;
   else
      ppref->rep.repmode = RADIO_FULL_TREE;

   // lettura sesta pagina: (report - 2)
   ppref->rep.formflag = WinQueryButtonCheckstate(pHpages[5], CBOX_FORMAT);
   WinQueryDlgItemText(pHpages[5], EF_IMP_PROG, 256, ppref->rep.formprog);
   WinQueryDlgItemText(pHpages[5], EF_IMP_PARMS, 256, ppref->rep.formparms);
   ppref->rep.autosave = WinQueryButtonCheckstate(pHpages[5], CBOX_AUTOSAVE);
   WinQueryDlgItemText(pHpages[5], EF_SAVEAS, 256, ppref->rep.savefile);

   // lettura otteva pagina: (find)
   ppref->find.flag = WinQueryButtonCheckstate(pHpages[6], CBOX_FIND);
   WinQueryDlgItemText(pHpages[6], EF_IMP_PROG, 256, ppref->find.prog);
   WinQueryDlgItemText(pHpages[6], EF_IMP_PARMS, 256, ppref->find.parms);
}


//===========================[UpdateSettings()]=============================\
// aggiorna impostazioni programma seguito chiusura blocco impostazioni     |
// parametri:                                                               |
// HWND hwnd     = handle finestra                                          |
// PATTMAN pam   = puntatore struttura globale                              |
// PAM_PRO ppnew = puntatore struttura nuove impostazioni                   |
//==========================================================================/

MRESULT UpdateSettings(HWND hwnd, PAM_PRO ppnew) {

   PATTMAN pam = (PATTMAN)WinQueryWindowPtr(hwnd, QWL_USER);

   if (pam->pro.gen.subj != ppnew->gen.subj)            // lunghezza subject
      SetSubjectLimit(hwnd, ppnew->gen.subj);
   if (pam->pro.gen.ronly != ppnew->gen.ronly)          // readonly/edit
      SwitchEditMode(hwnd, ppnew->gen.ronly, pam);
   if (sstrcmp(pam->pro.gen.font, ppnew->gen.font))     // imposta nuovo font
      SetDialogFont(hwnd, &ppnew->gen, TRUE);
   if (pam->pro.sel.extsel != ppnew->sel.extsel)        // sel estesa/singola
      SwitchSelectionMode(hwnd, ppnew->sel.extsel);
   if (pam->pro.sel.browse != ppnew->sel.browse)        // browse/nobrowse
      EnableBrowsing(hwnd, pam, (ppnew->sel.browse && (!ppnew->sel.browsedir ||
                     (ppnew->sel.browsedir && pam->fsp.pszFile[0] == '\\'))));
   if (pam->pro.imp.def_imp != ppnew->imp.def_imp)      // default import
      SetMenuDefaults(pam->hMEdit, SUBMN_IMPORT, pam->pro.imp.def_imp, ppnew->imp.def_imp);
   EnableImportMenuItems(hwnd, pam, ppnew);
   if (pam->pro.rep.repmode != ppnew->rep.repmode) {    // default report
      SetMenuDefaults(pam->hMEdit, SUBMN_REPORT, pam->pro.rep.repmode, ppnew->rep.repmode);
      SetMenuDefaults(pam->hMMain, SUBMN_REPORT, pam->pro.rep.repmode , ppnew->rep.repmode);
   } // end if
   // aggiungere elaborazione report
   pam->pro = *ppnew;  // aggiorna precedenti impostazioni
   WinEnableMenuItem(pam->hMMain, MN_PREF, TRUE);
   WinEnableMenuItem(pam->hMEdit, MN_PREF, TRUE);
   WinDestroyWindow(pam->pro.hPref);
   pam->pro.hPref = NULLHANDLE;
   return (MRESULT) FALSE;
}
