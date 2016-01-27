//==========================================================================\
// prefgen.c : funzioni dialoghi settaggio preferenze pag generale          |
//==========================================================================/

#define INCL_WINSTDFONT
#define INCL_WIN
#include <os2.h>
#include <spinbtn.h>
#include <efdlg.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "preferences.h"
#include "prefmessages.h"


//==========================================================================\
// procedura dialogo prima pagina : General                                 |
//==========================================================================/

MRESULT EXPENTRY GenDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   static PPREF_GEN pgen;

   switch (msg) {

      case WM_INITDLG:
         pgen = (PPREF_GEN)PVOIDFROMMP(mp2);
         InitGeneralPage(hwnd, pgen);
         break;
      case WM_CONTROL:
         if (SHORT1FROMMP(mp1) == CBOX_DEF_LEN &&
             SHORT2FROMMP(mp1) == BN_CLICKED)
            WinEnableControl(hwnd, SPIN_SUBJ_LEN,
                         !WinQueryButtonCheckstate(hwnd, CBOX_DEF_LEN));
         break;
      case WM_COMMAND:
         switch (LOUSHORT(mp1)) {
         case BTN_FONT: {
            char achFont[FACESIZE];  // buffer usato per i dati del nuovo font
            if (ShowFontDlg(hwnd, achFont))
               WinSetDlgItemText(hwnd, TXT_FONT, achFont);
            }
            break;
         case BTTN_UNDO:
            InitGeneralPage(hwnd, pgen);
            break;
         case BTTN_DEFAULT:
            SetGeneralDefault(hwnd, pgen);
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
// all'inizializzazione del dialogo o della pressione di UNDO (pagina 1)    |
// parametri:                                                               |
// HWND hwnd       = handle del dialogo                                     |
// PPREF_GEN pgen  = puntatore alla struttura delle impostazioni pag gen    |
//==========================================================================/

VOID InitGeneralPage(HWND hwnd, PPREF_GEN pgen) {
   DlgSpinSetLimits(hwnd, SPIN_SUBJ_LEN, 255, 0);
   WinCheckButton(hwnd, CBOX_NOLOGO, pgen->nologo);
   WinCheckButton(hwnd, CBOX_BUBBLE, pgen->bubble);
   if (pgen->subj < 0) {  // disabilita ef subj length
      WinCheckButton(hwnd, CBOX_DEF_LEN, TRUE);
      DlgSpinSetValue(hwnd, SPIN_SUBJ_LEN, -pgen->subj);
      WinEnableControl(hwnd, SPIN_SUBJ_LEN, FALSE);
   } else {
      WinCheckButton(hwnd, CBOX_DEF_LEN, FALSE);
      DlgSpinSetValue(hwnd, SPIN_SUBJ_LEN, pgen->subj);
      WinEnableControl(hwnd, SPIN_SUBJ_LEN, TRUE);
   } /* endif */
   WinCheckButton(hwnd, CBOX_READ_ONLY, pgen->ronly);
   WinCheckButton(hwnd, CBOX_SV_LASTPATH, pgen->lastPath[0] != 0);
   WinSetDlgItemText(hwnd, TXT_FONT, pgen->font);
}


//==========================================================================\
// resetta i controlli ai valori di default                                 |
// parametri:                                                               |
// HWND hwnd                                                                |
// valore restituito:                                                       |
// VOID                                                                     |
//==========================================================================/

VOID SetGeneralDefault(HWND hwnd, PPREF_GEN pgen) {
   WinCheckButton(hwnd, CBOX_NOLOGO, FALSE);
   WinCheckButton(hwnd, CBOX_BUBBLE, TRUE);
   WinCheckButton(hwnd, CBOX_DEF_LEN, TRUE);
   DlgSpinSetValue(hwnd, SPIN_SUBJ_LEN, 40);
   WinEnableControl(hwnd, SPIN_SUBJ_LEN, FALSE);
   WinCheckButton(hwnd, CBOX_READ_ONLY, FALSE);
   WinCheckButton(hwnd, CBOX_SV_LASTPATH, FALSE);
   WinSetDlgItemText(hwnd, TXT_FONT, "5.System VIO");
}
