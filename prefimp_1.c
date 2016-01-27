//==========================================================================\
// prefimp_1.c : funzioni dialoghi settaggio preferenze pagina import 1     |
//==========================================================================/

#define INCL_WINSTDFONT
#define INCL_WIN
#include <os2.h>
#include <notebook.h>
#include <efdlg.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "preferences.h"
#include "prefmessages.h"

//==========================================================================\
// procedura dialogo seconda pagina : Import (1)                            |
//==========================================================================/

MRESULT EXPENTRY Imp1DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   static PPREF_IMPORT pimp;
   static ULONG ulPrev;        // radio button precedentemente selezionato

   switch (msg) {
      case WM_INITDLG:
         pimp = (PPREF_IMPORT)PVOIDFROMMP(mp2);
         InitImport1Page(hwnd, pimp, &ulPrev);
         break;
      case WM_CONTROL:
         // memorizza in ulPrev ultimo radio button selezionato manualmente
         if (SHORT1FROMMP(mp1) >= RADIO_IMP_AUTO &&
             SHORT1FROMMP(mp1) <= RADIO_IMP_OTHER &&
             SHORT2FROMMP(mp1) == BN_CLICKED) {
            ulPrev = (ULONG) SHORT1FROMMP(mp1);
         } else if // cambiamento in EF_DESCRIPTION
                   (SHORT1FROMMP(mp1) == EF_DESCRIPTION &&
                    SHORT2FROMMP(mp1) == EN_CHANGE) {
            BOOL state = WinQueryButtonCheckstate(hwnd, RADIO_IMP_4);
            BOOL len = WinQueryDlgItemTextLength(hwnd, EF_DESCRIPTION);
            if (len) { // se testo presente riseleziona se necessario
               WinEnableControl(hwnd, RADIO_IMP_4, TRUE);
               if (ulPrev == RADIO_IMP_4 && !state)
                  WinCheckButton(hwnd, RADIO_IMP_4, TRUE);
            } else {
               WinEnableControl(hwnd, RADIO_IMP_4, FALSE);
               if (state)
                  WinCheckButton(hwnd, RADIO_IMP_AUTO, TRUE);
            } // end if
         } else if // cambiamento nei campi programma user_def
                   (SHORT1FROMMP(mp1) >= EF_F_TOIMP &&
                    SHORT1FROMMP(mp1) <= EF_IMP_PARMS &&
                    SHORT2FROMMP(mp1) == EN_CHANGE) {
            BOOL state = WinQueryButtonCheckstate(hwnd, RADIO_USER_DEF);
            BOOL len = WinQueryDlgItemTextLength(hwnd, EF_F_TOIMP) &&
                       WinQueryDlgItemTextLength(hwnd, EF_IMP_PROG) &&
                       WinQueryDlgItemTextLength(hwnd, EF_IMP_PARMS);
            if (len) { // se testo presente riseleziona se necessario
               WinEnableControl(hwnd, RADIO_USER_DEF, TRUE);
               if (ulPrev == RADIO_USER_DEF && !state)
                  WinCheckButton(hwnd, RADIO_USER_DEF, TRUE);
            } else {
               WinEnableControl(hwnd, RADIO_USER_DEF, FALSE);
               if (state)
                  WinCheckButton(hwnd, RADIO_IMP_AUTO, TRUE);
            } // end if
         } // end if
         break;
      case WM_COMMAND:
         switch (LOUSHORT(mp1)) {
            case BTTN_UNDO:
               InitImport1Page(hwnd, pimp, &ulPrev);
               break;
            case BTTN_DEFAULT:
               ulPrev = RADIO_IMP_AUTO;
               SetImport1Default(hwnd);
               break;  
            default:
               break;
         } /* endswitch */
         break;
      default: 
         return WinDefDlgProc(hwnd, msg, mp1, mp2);
         break;
   } /* endswitch */
   return (MRESULT) FALSE;
}


//==========================================================================\
// setta i controlli secondo i valori delle impostazioni correnti in        |
// all'inizializzazione del dialogo o della pressione di UNDO (pagina 3)    |
// parametri:                                                               |
// HWND hwnd         = handle del dialogo                                   |
// PPREF_IMPORT pimp = puntatore alla struttura delle impostazioni pag imp1 |
//==========================================================================/

VOID InitImport1Page(HWND hwnd, PPREF_IMPORT pimp, PULONG pulPrev) {
   *pulPrev = pimp->def_imp;
   WinCheckButton(hwnd, CBOX_ENABLE_AIMP, pimp->autoimp);
   WinCheckButton(hwnd, CBOX_VIEW_ONLY, pimp->view);
   WinCheckButton(hwnd, pimp->imp_to, TRUE);
   WinCheckButton(hwnd, *pulPrev, TRUE);
   DlgEFSetTxtLimit(hwnd, EF_DESCRIPTION, 255);
   DlgEFSetTxtLimit(hwnd, EF_F_TOIMP, 255);
   DlgEFSetTxtLimit(hwnd, EF_IMP_PROG, 255);
   DlgEFSetTxtLimit(hwnd, EF_IMP_PARMS, 255);
   WinSetDlgItemText(hwnd, EF_DESCRIPTION, pimp->quattro);
   WinEnableControl(hwnd, RADIO_IMP_4, pimp->quattro[0]);
   WinSetDlgItemText(hwnd, EF_F_TOIMP, pimp->ftoimp);
   WinSetDlgItemText(hwnd, EF_IMP_PROG, pimp->xtrprog);
   WinSetDlgItemText(hwnd, EF_IMP_PARMS, pimp->xtrparms);
   WinEnableControl(hwnd, RADIO_USER_DEF, pimp->ftoimp[0] &&
                pimp->xtrprog[0] && pimp->xtrparms[0]);
}


//==========================================================================\
// abilita/disabilita controlli dipendenti dallo stato di "enable import"   |
//==========================================================================/

VOID SetImport1Default(HWND hwnd) {
   WinCheckButton(hwnd, CBOX_ENABLE_AIMP, FALSE);
   WinCheckButton(hwnd, CBOX_VIEW_ONLY, TRUE);
   WinCheckButton(hwnd, RADIO_TO_CMNT, TRUE);
   WinCheckButton(hwnd, RADIO_IMP_AUTO, TRUE);
   WinSetDlgItemText(hwnd, EF_DESCRIPTION, "DESCRIPT.ION");
   WinSetDlgItemText(hwnd, EF_F_TOIMP, "");
   WinSetDlgItemText(hwnd, EF_IMP_PROG, "");
   WinSetDlgItemText(hwnd, EF_IMP_PARMS, "");
   WinEnableControl(hwnd, RADIO_USER_DEF, FALSE);
}
