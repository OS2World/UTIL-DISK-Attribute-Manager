//==========================================================================\
// prerep_1.c : funzioni dialoghi settaggio preferenze pagina report 1      |
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
// procedura dialogo sesta pagina : Report 1                                |
//==========================================================================/

MRESULT EXPENTRY Rep1DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   static PPREF_REPORT prep;

   switch (msg) {
      case WM_INITDLG:
         prep = (PPREF_REPORT)PVOIDFROMMP(mp2);
         InitReport1Page(hwnd, prep);
         break;
      case WM_CONTROL:
         if (SHORT1FROMMP(mp1) == CBOX_AUTO_REP &&
             SHORT2FROMMP(mp1) == BN_CLICKED)
            EnableAutoReport(hwnd,
                             WinQueryButtonCheckstate(hwnd, CBOX_AUTO_REP));
         break;
      case WM_COMMAND:
         switch (LOUSHORT(mp1)) {
            case BTTN_UNDO:
               InitReport1Page(hwnd, prep);
               break;
            case BTTN_DEFAULT:
               SetReport1Default(hwnd);
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

VOID InitReport1Page(HWND hwnd, PPREF_REPORT prep) {
   WinCheckButton(hwnd, CBOX_AUTO_REP, prep->autorep);
   WinCheckButton(hwnd, CBOX_ONLY_DIR_REP, prep->repdir);
   WinCheckButton(hwnd, prep->view, TRUE);
   WinCheckButton(hwnd, prep->repmode, TRUE);
   EnableAutoReport(hwnd, prep->autorep);
}


//==========================================================================\
// abilita/disabilita le checkbox dipendenti dallo stato di "auto report"   |
//==========================================================================/

VOID EnableAutoReport(HWND hwnd, BOOL flag) {
   WinEnableControl(hwnd, CBOX_ONLY_DIR_REP, flag);
   WinEnableControl(hwnd, RADIO_SHOW, flag);
   WinEnableControl(hwnd, RADIO_HIDE, flag);
   WinEnableControl(hwnd, RADIO_SHOW_ONLYREP, flag);
}


//==========================================================================\
// reimposta i valori di default                                            |
//==========================================================================/

VOID SetReport1Default(HWND hwnd) {
   WinCheckButton(hwnd, CBOX_AUTO_REP, FALSE);
   WinCheckButton(hwnd, CBOX_ONLY_DIR_REP, FALSE);
   WinCheckButton(hwnd, RADIO_SHOW, TRUE);
   WinCheckButton(hwnd, RADIO_SEL_FILES, TRUE);
   EnableAutoReport(hwnd, FALSE);
}
