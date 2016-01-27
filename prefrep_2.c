//==========================================================================\
// prefrep_2.c : funzioni dialoghi settaggio preferenze pagina report 2     |
//==========================================================================/

#define INCL_WIN
#include <os2.h>
#include <stdlib.h>
#include <efdlg.h>
#include <listbox.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "preferences.h"
#include "prefmessages.h"


//==========================================================================\
// procedura dialogo settima pagina : Report 2                              |
//==========================================================================/

MRESULT EXPENTRY Rep2DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   static PPREF_REPORT prep;

   switch (msg) {
      case WM_INITDLG:
         prep = (PPREF_REPORT)PVOIDFROMMP(mp2);
         InitReport2Page(hwnd, prep);
         break;
      case WM_CONTROL:
         if (SHORT1FROMMP(mp1) == CBOX_FORMAT &&
             SHORT2FROMMP(mp1) == BN_CLICKED)
            EnableReportFormat(hwnd,
                               WinQueryButtonCheckstate(hwnd, CBOX_FORMAT));
         else if (SHORT1FROMMP(mp1) == CBOX_AUTOSAVE &&
             SHORT2FROMMP(mp1) == BN_CLICKED)
            EnableReportAutosave(hwnd,
                                 WinQueryButtonCheckstate(hwnd, CBOX_AUTOSAVE));
         break;
      case WM_COMMAND:
         switch (LOUSHORT(mp1)) {
            case BTTN_UNDO:
               InitReport2Page(hwnd, prep);
               break;
            case BTTN_DEFAULT:
               SetReport2Default(hwnd);
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
// all'inizializzazione del dialogo o della pressione di UNDO (pagina 5)    |
// parametri:                                                               |
// HWND hwnd         = handle del dialogo                                   |
// PPREF_REPORT prep = puntatore alla struttura delle impostazioni pag rep  |
//==========================================================================/

VOID InitReport2Page(HWND hwnd, PPREF_REPORT prep) {
   DlgEFSetTxtLimit(hwnd, EF_IMP_PROG, 255);
   DlgEFSetTxtLimit(hwnd, EF_IMP_PARMS, 255);
   DlgEFSetTxtLimit(hwnd, EF_SAVEAS, 255);
   WinCheckButton(hwnd, CBOX_FORMAT, prep->formflag);
   WinCheckButton(hwnd, CBOX_AUTOSAVE, prep->autosave);
   EnableReportFormat(hwnd, prep->formflag);
   EnableReportAutosave(hwnd, prep->autosave);
   WinSetDlgItemText(hwnd, EF_IMP_PROG, prep->formprog);
   WinSetDlgItemText(hwnd, EF_IMP_PARMS, prep->formparms);
   WinSetDlgItemText(hwnd, EF_SAVEAS, prep->savefile);
}


//==========================================================================\
// abilita/disabilita le checkbox dipendenti dallo stato di "auto report"   |
//==========================================================================/

VOID EnableReportFormat(HWND hwnd, BOOL flag) {
   WinEnableControl(hwnd, TXT_IMP_PROG, flag);
   WinEnableControl(hwnd, EF_IMP_PROG, flag);
   WinEnableControl(hwnd, TXT_IMP_PARMS, flag);
   WinEnableControl(hwnd, EF_IMP_PARMS, flag);
}


//==========================================================================\
// abilita/disabilita le checkbox dipendenti dallo stato di "auto report"   |
//==========================================================================/

VOID EnableReportAutosave(HWND hwnd, BOOL flag) {
   WinEnableControl(hwnd, TXT_SAVEAS, flag);
   WinEnableControl(hwnd, EF_SAVEAS, flag);
}


//==========================================================================\
// reimposta i valori di default                                            |
//==========================================================================/

VOID SetReport2Default(HWND hwnd) {
   WinCheckButton(hwnd, CBOX_FORMAT, FALSE);
   WinCheckButton(hwnd, CBOX_AUTOSAVE, FALSE);
   EnableReportFormat(hwnd, FALSE);
   EnableReportAutosave(hwnd, FALSE);
   WinSetDlgItemText(hwnd, EF_IMP_PROG, "");
   WinSetDlgItemText(hwnd, EF_IMP_PARMS, "");
   WinSetDlgItemText(hwnd, EF_SAVEAS, "");
}
