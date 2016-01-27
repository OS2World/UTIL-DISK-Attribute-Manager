//==========================================================================\
// prefsel.c : funzioni dialoghi settaggio preferenze pagina selezione      |
//==========================================================================/

#define INCL_WINSTDFONT
#define INCL_WIN
#include <os2.h>
#include <notebook.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "preferences.h"
#include "prefmessages.h"


//==========================================================================\
// procedura dialogo seconda pagina : Selection                             |
//==========================================================================/

MRESULT EXPENTRY SelDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   static PPREF_SEL psel;

   switch (msg) {
      case WM_INITDLG:
         psel = (PPREF_SEL)PVOIDFROMMP(mp2);
         InitSelectionPage(hwnd, psel);
         break;
      case WM_CONTROL:
         if (SHORT1FROMMP(mp1) == CBOX_EXT_SEL &&
             SHORT2FROMMP(mp1) == BN_CLICKED) {
            WinEnableControl(hwnd, CBOX_SEL_ALL_INDIR,
                         WinQueryButtonCheckstate(hwnd, CBOX_EXT_SEL));
         } else if (SHORT1FROMMP(mp1) == CBOX_FILE_WIN &&
                    SHORT2FROMMP(mp1) == BN_CLICKED) {
            WinEnableControl(hwnd, CBOX_ONLY_DIR,
                         WinQueryButtonCheckstate(hwnd, CBOX_FILE_WIN));
         } /* endif */
         break;
      case WM_COMMAND:
         switch (LOUSHORT(mp1)) {
            case BTTN_UNDO:
               InitSelectionPage(hwnd, psel);
               break;
            case BTTN_DEFAULT:
               SetSelectionDefault(hwnd);
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
// all'inizializzazione del dialogo o della pressione di UNDO (pagina 2)    |
// parametri:                                                               |
// HWND hwnd       = handle del dialogo                                     |
// PPREF_SEL psel  = puntatore alla struttura delle impostazioni pag sel    |
//==========================================================================/

VOID InitSelectionPage(HWND hwnd, PPREF_SEL psel) {
   WinCheckButton(hwnd, CBOX_EXT_SEL, psel->extsel);
   WinCheckButton(hwnd, CBOX_SEL_ALL_INDIR, psel->dir);
   WinEnableControl(hwnd, CBOX_SEL_ALL_INDIR, psel->extsel);
   WinCheckButton(hwnd, CBOX_MOUSE_SINGLE, psel->monoclick == LN_SELECT);
   WinCheckButton(hwnd, CBOX_FILE_WIN, psel->browse);
   WinCheckButton(hwnd, CBOX_ONLY_DIR, psel->browsedir);
   WinEnableControl(hwnd, CBOX_ONLY_DIR, psel->browse);
}


//==========================================================================\
// resetta i controlli ai valori di default                                 |
// parametri:                                                               |
// HWND hwnd                                                                |
// valore restituito:                                                       |
// VOID                                                                     |
//==========================================================================/

VOID SetSelectionDefault(HWND hwnd) {
   WinCheckButton(hwnd, CBOX_EXT_SEL, TRUE);
   WinCheckButton(hwnd, CBOX_SEL_ALL_INDIR, FALSE);
   WinEnableControl(hwnd, CBOX_SEL_ALL_INDIR, TRUE);
   WinCheckButton(hwnd, CBOX_MOUSE_SINGLE, FALSE);
   WinCheckButton(hwnd, CBOX_FILE_WIN, FALSE);
   WinCheckButton(hwnd, CBOX_ONLY_DIR, FALSE);
   WinEnableControl(hwnd, CBOX_ONLY_DIR, FALSE);
}
