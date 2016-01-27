//==========================================================================\
// commands.c : elabora le azioni conseguenti al click su un pulsante o     |
// alla selezione di un menuitem                                            |
// MRESULT ProcessButtonOpen(HWND hwnd, PATTMAN pam);                       |
// MRESULT ProcessButtonClose(HWND hwnd, PATTMAN pam);                      |
// MRESULT ProcessButtonSave(HWND hwnd, PATTMAN pam);                       |
// MRESULT ProcessButtonImport(HWND hwnd, PATTMAN pam);                     |
// MRESULT ProcessButtonReport(HWND hwnd, PATTMAN pam);                     |
// MRESULT ProcessButtonFind(void);                                         |
// MRESULT ProcessButtonUp(HWND hwnd, PATTMAN pam);                         |
// MRESULT ProcessButtonDown(HWND hwnd, PATTMAN pam);                       |
// MRESULT ProcessMenuBrowse(HWND hwnd, PATTMAN pam);                       |
// MRESULT ProcessMenuSelAll(HWND hwnd, PATTMAN pam);                       |
// MRESULT ProcessMenuDeselAll(HWND hwnd, PATTMAN pam);                     |
// MRESULT ProcessMenuMask(HWND hwnd, PATTMAN pam);                         |
// MRESULT ProcessMenuRefresh(HWND hwnd, PATTMAN pam);                      |
// MRESULT ProcessMenuSelected(HWND hwnd);                                  |
// MRESULT ProcessMenuAll(HWND hwnd);                                       |
// MRESULT ProcessMenuFullTree(HWND hwnd);                                  |
// MRESULT ProcessMenuFind(HWND hwnd);                                      |
// MRESULT ProcessMenuPreferences(HWND hwnd, PATTMAN pam, PAM_PRO ppref);   |
// MRESULT ProcessMenuFont(HWND hwnd, PATTMAN pam);                         |
// MRESULT ProcessMenuReadOnly(HWND hwnd, PATTMAN pam);                     |
// MRESULT ProcessMenuUndo(HWND hwnd, PATTMAN pam);                         |
// MRESULT ProcessMenuCut(HWND hwnd, PATTMAN pam);                          |
// MRESULT ProcessMenuCopy(HWND hwnd, PATTMAN pam);                         |
// MRESULT ProcessMenuPaste(HWND hwnd, PATTMAN pam);                        |
// MRESULT ProcessMenuClear(HWND hwnd, PATTMAN pam);                        |
// MRESULT ProcessMenuImpAuto(HWND hwnd, PATTMAN pam);                      |
// MRESULT ProcessMenu4Dos(HWND hwnd, PATTMAN pam);                         |
// MRESULT ProcessMenuID_DIZ(HWND hwnd, PATTMAN pam);                       |
// MRESULT ProcessMenuImpUdef(HWND hwnd, PATTMAN pam);                      |
// MRESULT ProcessMenuOther(HWND hwnd, PATTMAN pam);                        |
// MRESULT ProcessMenuHelpIDX(void);                                        |
// MRESULT ProcessMenuHelpGeneral(void);                                    |
// MRESULT ProcessMenuHelpUse(void);                                        |
// MRESULT ProcessMenuHelpKey(void);                                        |
// MRESULT ProcessMenuHelpProduct(HWND hwnd);                               |
//==========================================================================/

#define INCL_WIN
#include <os2.h>
#include <mledlg.h>
#include <listbox.h>
#include <efdlg.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"
#include "preferences.h"


//==========================================================================\
// elaborazione conseguente selezione browse mode                           |
//==========================================================================/

MRESULT ProcessButtonOpen(HWND hwnd, PATTMAN pam) {
   EnableBrowsing(hwnd, pam, TRUE);
   return (MRESULT) FALSE;
}


//==========================================================================\
// elaborazione conseguente selezione no browse mode                        |
//==========================================================================/

MRESULT ProcessButtonClose(HWND hwnd, PATTMAN pam) {
   EnableBrowsing(hwnd, pam, FALSE);
   return (MRESULT) FALSE;
}


//==========================================================================\
// elaborazione conseguente al salvataggio degli attributi                  |
//==========================================================================/

MRESULT ProcessButtonSave(HWND hwnd, PATTMAN pam) {
   WriteNewAttr(hwnd, pam);
   DlgMleResetChanged(hwnd, MLE_KEY); 
   DlgMleResetChanged(hwnd, MLE_COMNT);
   DlgEFQueryChanged(hwnd, EF_SUBJ);
   return (MRESULT) FALSE;
}


//==========================================================================\
// importa una descrizione del file. La sorgente di importazione Š          |
// determinata da quanto stabilito nel blocco di impostazioni come sorgente |
// di default, lo stesso vale per la destinazione. Se nel campo di          |
// destinazione Š gi… presente un commento questo viene sostituito dal      |
// testo importato. La sostituzione diventa permanente se si salva.         |
//==========================================================================/

MRESULT ProcessButtonImport(HWND hwnd, PATTMAN pam) {
   pam->sMenuFrom = BTN_IMP;
   ImportFileData(hwnd, pam);
   return (MRESULT) FALSE;
}

#include <stdio.h>
//==========================================================================\
//
//==========================================================================/

MRESULT ProcessButtonReport(HWND hwnd, PATTMAN pam) {
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessButtonFind(void) {
   return (MRESULT) FALSE;
}


MRESULT ProcessButtonUp(HWND hwnd, PATTMAN pam) {
   SHORT idx = pam->fsp.psSel[1];
   DeselectAllFiles(hwnd, pam);
   DlgLboxSelectItem(hwnd, LB_FILE, idx - 1);
   WinSendMsg(hwnd, WM_CONTROL, MPFROM2SHORT(LB_FILE, LN_ENTER),   
              MPFROMHWND(WinWindowFromID(hwnd, LB_FILE)));
   return (MRESULT) FALSE;
}
  

MRESULT ProcessButtonDown(HWND hwnd, PATTMAN pam) {
   SHORT idx = pam->fsp.psSel[1];
   DeselectAllFiles(hwnd, pam);
   DlgLboxSelectItem(hwnd, LB_FILE, idx + 1);
   WinSendMsg(hwnd, WM_CONTROL, MPFROM2SHORT(LB_FILE, LN_ENTER),   
              MPFROMHWND(WinWindowFromID(hwnd, LB_FILE)));
   return (MRESULT) FALSE;
}



//==========================================================================\
// elaborazione conseguente dalla selezione della voce browse del menu      |
//==========================================================================/

MRESULT ProcessMenuBrowse(HWND hwnd, PATTMAN pam) {
   EnableBrowsing(hwnd, pam, !WinIsMenuItemChecked(pam->hMMain, MN_BROWSE));
   return (MRESULT) FALSE;
}


//==========================================================================\
// selezione menu: Select All                                               |
//==========================================================================/

MRESULT ProcessMenuSelAll(HWND hwnd, PATTMAN pam) {
   SHORT count = DlgLboxQueryItemCount(hwnd, LB_FILE);
   while (--count > -1) {
      MyDlgLboxSelectItem(hwnd, LB_FILE, count);
   } // end while
   sstrcpy(pam->fsp.pszFile, "*.*");
   ProcessFileSelection(hwnd, pam);
   return (MRESULT) FALSE;
}


//==========================================================================\
// selezione menu: Deselect all                                             |
//==========================================================================/

MRESULT ProcessMenuDeselAll(HWND hwnd, PATTMAN pam) {
   DeselectAllFiles(hwnd, pam);
   pam->fsp.psSel[1] = -1;
//   ProcessFileSelection(hwnd, pam);
   DlgLboxSelectItem(hwnd, LB_FILE, 0);
   return (MRESULT) FALSE;
}


//==========================================================================\
// selezione menu: Mask...                                                  |
//==========================================================================/

MRESULT ProcessMenuMask(HWND hwnd, PATTMAN pam) {
   USHORT count;
   if (WinDlgBox(HWND_DESKTOP, hwnd, MaskDlgProc, 0L, MASKSEL_DLG,
                 &pam->pro.msk)) {
      CHAR achFile[256];
      DeselectAllFiles(hwnd, pam);                 // deseleziona tutto
      count = DlgLboxQueryItemCount(hwnd, LB_FILE);
      while (--count) {            // seleziona file rispondenti alla mask
         DlgLboxQueryItemText(hwnd, LB_FILE, count, achFile, 256);
         if (WildCmp(pam->pro.msk.achSel, achFile)) {
            MyDlgLboxSelectItem(hwnd, LB_FILE, count);
         } // end if
      } // end while
      sstrcpy(pam->fsp.pszFile, pam->pro.msk.achSel);
      ProcessFileSelection(hwnd, pam);
   } // end if
   return (MRESULT) FALSE;
}


//==========================================================================\
// selezione menu: Refresh                                                  |
//==========================================================================/

MRESULT ProcessMenuRefresh(HWND hwnd, PATTMAN pam) {
   if (SetDisk(hwnd, *pam->fsp.pszPath, &pam->fsp.hpfs)) { // drive non disp
      PMPrint(hwnd, CANNOT_REFRESH);
   } else {                            // drive disponibile -> aggiornamento
      QueryCurrentPath(pam->fsp.pszPath, pam->fsp.pszFile);
      FillDirList(hwnd, pam);
   } /* endif */
   return (MRESULT) FALSE;
}


//==========================================================================\
// selezione menu: Save -> elaborato da ProcessButtonSave()                 |
//==========================================================================/


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuSelected(HWND hwnd) {
   PMPrint(hwnd, "Menu-Report: Selected files detected");
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuAll(HWND hwnd) {
   PMPrint(hwnd, "Menu-Report: All files detected");
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuFullTree(HWND hwnd) {
   PMPrint(hwnd, "Menu-Report: Full tree detected");
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuFind(HWND hwnd) {
   return (MRESULT) FALSE;
}


//==========================================================================\
// selezione menu : Options->General preferences                            |
//==========================================================================/

MRESULT ProcessMenuPreferences(HWND hwnd, PATTMAN pam, PAM_PRO ppref) {
   HWND hPref;
   *ppref = pam->pro;        // inizializza ppref con opzioni correnti
   if ((pam->pro.hPref = WinLoadDlg(HWND_DESKTOP, hwnd, (PFNWP)PrefDlgProc,
                                    0L, DLG_PREFERENCES, ppref))
       != NULLHANDLE) {
      WinEnableMenuItem(pam->hMMain, MN_PREF, FALSE);
      WinEnableMenuItem(pam->hMEdit, MN_PREF, FALSE);
   } // end if
   return (MRESULT) FALSE;
}


//==========================================================================\
// elabora selezione Font dal submenu Options                               |
//==========================================================================/

MRESULT ProcessMenuFont(HWND hwnd, PATTMAN pam) {
   if (ShowFontDlg(hwnd, pam->pro.gen.font))
      SetDialogFont(hwnd, &pam->pro.gen, TRUE);
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuReadOnly(HWND hwnd, PATTMAN pam) {
   SwitchEditMode(hwnd, !WinIsMenuItemChecked(pam->hMMain, MN_READ), pam);
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuUndo(HWND hwnd, PATTMAN pam) {
   if (pam->sMenuFrom == EF_SUBJ)
      WinSetDlgItemText(hwnd, EF_SUBJ, pam->fsp.subjUndo);
   else
      DlgMleUndo(hwnd, pam->sMenuFrom);
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuCut(HWND hwnd, PATTMAN pam) {
   if (pam->sMenuFrom == EF_SUBJ)
      DlgEFCut(hwnd, pam->sMenuFrom);
   else
      DlgMleCut(hwnd, pam->sMenuFrom);
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuCopy(HWND hwnd, PATTMAN pam) {
   if (pam->sMenuFrom == EF_SUBJ)
      DlgEFCopy(hwnd, pam->sMenuFrom);
   else
      DlgMleCopy(hwnd, pam->sMenuFrom);
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuPaste(HWND hwnd, PATTMAN pam) {
   if (pam->sMenuFrom == EF_SUBJ)
      DlgEFPaste(hwnd, pam->sMenuFrom);
   else
      DlgMlePaste(hwnd, pam->sMenuFrom);
    return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuClear(HWND hwnd, PATTMAN pam) {
   if (pam->sMenuFrom == EF_SUBJ)
      DlgEFClear(hwnd, pam->sMenuFrom);
   else
      DlgMleClear(hwnd, pam->sMenuFrom);
    return (MRESULT) FALSE;
}


//==========================================================================\
// vale solo per il file corrrente
//==========================================================================/

MRESULT ProcessMenuImpAuto(HWND hwnd, PATTMAN pam) { 
   if (Show4Dos(hwnd, pam)) return (MRESULT) FALSE;
   if (ShowFileIdDiz(hwnd, pam)) return (MRESULT) FALSE;
   if (ShowUserDef(hwnd, pam)) return (MRESULT) FALSE;
   (ShowOther(hwnd, pam));
   return (MRESULT) FALSE;
}


//==========================================================================\
// loopa x tutti i file selezionati
//==========================================================================/

MRESULT ProcessMenu4Dos(HWND hwnd, PATTMAN pam) {
   return Import4Dos(hwnd, pam);
}


//==========================================================================\
// loopa x tutti i file selezionati
//==========================================================================/

MRESULT ProcessMenuID_DIZ(HWND hwnd, PATTMAN pam) {
   return ImportFileIdDiz(hwnd, pam);
}


//==========================================================================\
// loopa x tutti i file selezionati
//==========================================================================/

MRESULT ProcessMenuImpUdef(HWND hwnd, PATTMAN pam) {
   return ImportUserDef(hwnd, pam);
}


//==========================================================================\
// solo primo file selezionato
//==========================================================================/

MRESULT ProcessMenuOther(HWND hwnd, PATTMAN pam) {
   ShowOther(hwnd, pam);
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuHelpIDX(void) {
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuHelpGeneral(void) {
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuHelpUse(void) {
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuHelpKey(void) {
   return (MRESULT) FALSE;
}


//==========================================================================\
//
//==========================================================================/

MRESULT ProcessMenuHelpProduct(HWND hwnd) {
   WinDlgBox(HWND_DESKTOP, hwnd, (PFNWP)LogoDlgProc, 0L, LOGO_DLG, NULL);
   return (MRESULT) FALSE;
}
