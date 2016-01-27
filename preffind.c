//==========================================================================\
// preffind.c : funzioni dialoghi settaggio preferenze pagina find          |
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
// procedura dialogo ottava pagina : Find                                   |
//==========================================================================/

MRESULT EXPENTRY FindDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   static PPREF_FIND pfind;

   switch (msg) {
      case WM_INITDLG:
         pfind = (PPREF_FIND)PVOIDFROMMP(mp2);
         InitFindPage(hwnd, pfind);
         break;
      case WM_CONTROL:
         if (SHORT1FROMMP(mp1) == CBOX_FIND &&
             SHORT2FROMMP(mp1) == BN_CLICKED)
            EnableFind(hwnd, WinQueryButtonCheckstate(hwnd, CBOX_FIND));
         break;
      case WM_COMMAND:
         switch (LOUSHORT(mp1)) {
            case BTTN_UNDO:
               InitFindPage(hwnd, pfind);
               break;
            case BTTN_DEFAULT:
               SetFindDefault(hwnd);
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
// all'inizializzazione del dialogo o della pressione di UNDO               |
// parametri:                                                               |
// HWND hwnd         = handle del dialogo                                   |
// PPREF_REPORT prep = puntatore alla struttura delle impostazioni pag rep  |
//==========================================================================/

VOID InitFindPage(HWND hwnd, PPREF_FIND pfind) {
   DlgEFSetTxtLimit(hwnd, EF_IMP_PROG, 255);
   DlgEFSetTxtLimit(hwnd, EF_IMP_PARMS, 255);
   WinCheckButton(hwnd, CBOX_FIND, pfind->flag);
   EnableFind(hwnd, pfind->flag);
   WinSetDlgItemText(hwnd, EF_IMP_PROG, pfind->prog);
   WinSetDlgItemText(hwnd, EF_IMP_PARMS, pfind->parms);
}


//==========================================================================\
// abilita/disabilita le checkbox dipendenti dallo stato di "Find"          |
//==========================================================================/

VOID EnableFind(HWND hwnd, BOOL flag) {
   WinEnableControl(hwnd, TXT_IMP_PROG, flag);
   WinEnableControl(hwnd, EF_IMP_PROG, flag);
   WinEnableControl(hwnd, TXT_IMP_PARMS, flag);
   WinEnableControl(hwnd, EF_IMP_PARMS, flag);
}


//==========================================================================\
// reimposta i valori di default                                            |
//==========================================================================/

VOID SetFindDefault(HWND hwnd) {
   WinCheckButton(hwnd, CBOX_FIND, FALSE);
   EnableFind(hwnd, FALSE);
   WinSetDlgItemText(hwnd, EF_IMP_PROG, "");
   WinSetDlgItemText(hwnd, EF_IMP_PARMS, "");
}
