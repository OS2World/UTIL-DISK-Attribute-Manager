//==========================================================================\
// attman.c file principale                                                 |
// int main(int argc, char** argv);                                         |
// MRESULT EXPENTRY MyDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);|
// MRESULT EXPENTRY NewTitleWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
// MRESULT EXPENTRY ACCMMLEWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
// MRESULT EXPENTRY NewEFWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
// MRESULT EXPENTRY ACCMSTextWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
// MRESULT EXPENTRY ACCMLBoxWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
// MRESULT EXPENTRY ACCHBtnWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
// MRESULT EXPENTRY ACCHSBarWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
// MRESULT EXPENTRY FileBoxWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
//==========================================================================/

#define INCL_WIN
#include <os2.h>
#include "attman.h"
#include "messages.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"

// variabili globali in cui vengono memorizzate le procedure di default
// dei controlli superclassati
PFNWP pfnwpSbar, pfnwpBtn, pfnwpLBox, pfnwpSText, pfnwpMle;


int main(int argc, char** argv) {
   HAB    hab;
   HMQ    hmq;
   QMSG   qmsg;
   HWND   hwndDlg;
   ATTMAN am;

   am.cbSize = sizeof(ATTMAN);          // dimensione della struttura ATTMAN
   // inizializza dimensioni substrutture
   am.pro.usSize = sizeof(AM_PRO);
   am.pro.gen.usSize = sizeof(PREF_GEN);
   am.pro.sel.usSize = sizeof(PREF_SEL);
   am.pro.imp.usSize = sizeof(PREF_IMPORT);
   am.pro.rep.usSize = sizeof(PREF_REPORT);
   am.pro.find.usSize = sizeof(PREF_FIND);
   am.pro.msk.usSize = sizeof(MASKSEL);
   am.fsp.psSel = NULL;
   am.pro.gen.pswp = NULL;
   am.pro.gen.cxFont = 0; // flag inizializzazione usata in SetDialogFont
   am.cyNoBrowse = -2;    // usato in EnableBrowsing x mem dati pulsante max
   am.szCtl = 0;          // usato x ridimensionare listbox
   hab = WinInitialize(0);
   hmq = WinCreateMsgQueue(hab, 0);
   if (ParseArgs(argc, argv, &am)) return Terminate(hab, hmq, 2);
   if (ParseProfile(hab, am.pszProfile, &am.pro)) return Terminate(hab, hmq, 2);

   if (!am.pro.gen.nologo)
      WinDlgBox(HWND_DESKTOP, HWND_DESKTOP, (PFNWP)LogoDlgProc, 0L,
                LOGO_DLG, NULL);
   if (!RegisterCustomControls(hab)) {
      PMPrint(HWND_DESKTOP, SZ_CCREGISTRATIONFAILURE);
      return Terminate(hab, hmq, 4);
   } /* endif */

   hwndDlg = WinLoadDlg(HWND_DESKTOP, HWND_DESKTOP, (PFNWP)MyDlgProc,
                        0L, DLG_MAIN, &am);
   if (hwndDlg) {                              // LOOP messaggi modificato
      forever {
         if(WinGetMsg(hab, &qmsg, NULLHANDLE, 0, 0)) {    // loop standard
            WinDispatchMsg(hab, &qmsg);
         } else {                   // WM_QUIT
            if(qmsg.hwnd == NULLHANDLE)                       // SHUTDOWN
               WinPostMsg(hwndDlg, WM_CLOSE, MPFROMLONG(TRUE), NULL);
            else if(qmsg.hwnd == HWNDFROMMP(qmsg.mp2))        // TASKLIST
               WinPostMsg(qmsg.hwnd, WM_CLOSE, 0L, 0L);
            else                            // chiusura regolare: termina
               break;
         } // end if
      } // end forever
   } // end if
   WinDestroyWindow(hwndDlg);
   return Terminate(hab, hmq, 0);
}


//==========================================================================\
// procedura della finestra principale del programma                        |
//==========================================================================/

MRESULT EXPENTRY MyDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   static AM_PRO pref;

   switch (msg) {
      case WM_INITDLG:
         return InitDlg(hwnd, (PATTMAN)mp2);
      case WM_MINMAXFRAME:         // iconizza quando minimizzato sul desktop
         return MinMaxFrame(hwnd, (PSWP)mp1);
      case WM_MEASUREITEM:              // restituisce massima altezza font
         return ProcessMeasureItem(hwnd);
      case WM_DRAWITEM:                 // disegna item listbox folder
         return DrawListBoxItem(hwnd, (POWNERITEM)mp2);
      case WM_ADJUSTWINDOWPOS:          // controlla il ridimensionamento
         return AdjustWindowPos(hwnd, (PSWP)mp1);
      case WM_PRESPARAMCHANGED:
         return ProcessPresParmsChanged(hwnd, (LONG)mp1);
      case WM_APPTERMINATENOTIFY:
         return ProcessChildAppEnd(hwnd, mp1, mp2);
      case TTL_DROP:
         return ProcessDrop(hwnd, (PDRAGINFO)mp1);
      case WM_CONTEXTMENU:
         return ProcessContextMenu(hwnd, DLG_MAIN);
         break;   
      case WM_POPUPMENU:
         return ProcessContextMenu(hwnd, (ULONG)mp1);
      case WM_BUBBLEHELP:
         return ProcessBubbleHelp(hwnd, (HWND)mp1);
      case WM_TIMER:
         return ProcessTimer(hwnd, (ULONG)mp1);
      case WM_MOUSEMOVE:
         return ProcessMouseMove(hwnd, msg, mp1, mp2);
      case WM_BUTTON1MOTIONSTART:
         return ProcessMotionStart(hwnd, msg, mp1, mp2);
      case WM_BUTTON1UP:
      case WM_BUTTON1MOTIONEND:
         return ProcessMotionEnd(hwnd, msg, mp1, mp2);
      case WM_CONTROL:
         return ProcessControl(hwnd, mp1);
      case WM_LBOXBTN1UP:
         return ProcessLBoxBtnUp(hwnd, (LONG)mp1, mp2);
      case WM_COMMAND:           // elabora gli eventi generati dai pulsanti
         return ProcessCommand(hwnd, mp1, &pref);
      case WM_UPD_SETTINGS:             // update struttura pro
         return UpdateSettings(hwnd, &pref);
      case WM_PROC_READY:
         return ProcessReady(hwnd, mp1, mp2);
      case WM_CLOSE :
         return ProcessTermination(hwnd, (BOOL)mp1);
      default :
         return WinDefDlgProc(hwnd, msg, mp1, mp2);
   } // end switch
   return (MRESULT) FALSE;
}


//==========================================================================\
// procedura personalizzata per il titolo della finestra                    |
//==========================================================================/

MRESULT EXPENTRY NewTitleWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   PFNWP pfnwpOld = (PFNWP)WinQueryWindowPtr(hwnd, QWL_USER);
   switch (msg) {
      case DM_DRAGOVER:
         return ProcessDragOver(WinQueryWindow(hwnd, QW_OWNER), (PDRAGINFO)mp1);
         break;
      case DM_DROP:
         WinSendMsg(WinQueryWindow(hwnd, QW_OWNER), TTL_DROP, mp1, 0L);
         break;
      default: 
        break;
   } /* endswitch */
   return (MRESULT) (*pfnwpOld)(hwnd, msg, mp1, mp2);
}

//==========================================================================\
// procedura personalizzata delle finestre MLE per abilitare                |
// l'intercettazione di WM_CONTEXTMENU                                      |
//==========================================================================/

MRESULT EXPENTRY ACCMMLEWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   if (msg == WM_CONTEXTMENU) {
      WinPostMsg(WinQueryWindow(hwnd, QW_PARENT), WM_POPUPMENU,
                 MPFROMLONG((LONG)WinQueryWindowUShort(hwnd, QWS_ID)),
                 MPFROMHWND(hwnd));
   } // end if
   return (MRESULT) (*pfnwpMle)(hwnd, msg, mp1, mp2);
}


//==========================================================================\
// procedura personalizzata delle finestre entryfield per abilitare         |
// l'intercettazione di WM_CONTEXTMENU                                      |
//==========================================================================/

MRESULT EXPENTRY NewEFWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   PFNWP pfnwpOld = (PFNWP)WinQueryWindowPtr(hwnd, QWL_USER);
   if (msg == WM_CONTEXTMENU) {
      WinPostMsg(WinQueryWindow(hwnd, QW_PARENT), WM_POPUPMENU,
                 MPFROMLONG((LONG)WinQueryWindowUShort(hwnd, QWS_ID)),
                 MPFROMHWND(hwnd));
   } // end if
   return (MRESULT) (*pfnwpOld)(hwnd, msg, mp1, mp2);
}


//==========================================================================\
// procedura personalizzata delle finestre static text per abilitare        |
// l'intercettazione di WM_CONTEXTMENU                                      |
//==========================================================================/

MRESULT EXPENTRY ACCMSTextWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   if (msg == WM_CONTEXTMENU) {
      WinPostMsg(WinQueryWindow(hwnd, QW_PARENT), WM_POPUPMENU,
                 MPFROMLONG((LONG)WinQueryWindowUShort(hwnd, QWS_ID)),
                 MPFROMHWND(hwnd));
   } // end if
   return (MRESULT) (*pfnwpSText)(hwnd, msg, mp1, mp2);
}


//==========================================================================\
// procedura personalizzata delle finestre listbox per abilitare            |
// l'intercettazione di WM_CONTEXTMENU                                      |
//==========================================================================/

MRESULT EXPENTRY ACCMLBoxWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   switch (msg) {
      case WM_CONTEXTMENU:
         WinPostMsg(WinQueryWindow(hwnd, QW_PARENT), WM_POPUPMENU,
                    MPFROMLONG((LONG)WinQueryWindowUShort(hwnd, QWS_ID)),
                    MPFROMHWND(hwnd));
         break;
      case WM_CHAR:// se viene rilasciato tasto freccia su/gi— o pag su/gi—
         if (CHARMSG(&msg)->fs & KC_KEYUP &&              // rilascio tasto
             CHARMSG(&msg)->fs & KC_VIRTUALKEY &&         // virtual key
             (CHARMSG(&msg)->vkey == VK_UP) ||            // freccia su
             (CHARMSG(&msg)->vkey == VK_DOWN) ||          // freccia gi—
             (CHARMSG(&msg)->vkey == VK_PAGEUP) ||        // pag su
             (CHARMSG(&msg)->vkey == VK_PAGEDOWN)) {      // pag gi—
            MRESULT mr = (*pfnwpLBox)(hwnd, msg, mp1, mp2);
            WinPostMsg(WinQueryWindow(hwnd, QW_PARENT), WM_LBOXBTN1UP,
                       MPFROMLONG((LONG)WinQueryWindowUShort(hwnd, QWS_ID)),
                       MPFROMHWND(hwnd));
            return mr;
         } // end if
         break;
      case WM_BUTTON1UP: {
         MRESULT mr = (*pfnwpLBox)(hwnd, msg, mp1, mp2);
         WinPostMsg(WinQueryWindow(hwnd, QW_PARENT), WM_LBOXBTN1UP,
                    MPFROMLONG((LONG)WinQueryWindowUShort(hwnd, QWS_ID)),
                    MPFROMHWND(hwnd));
         return mr;
      } // end case WM_BUTTON1UP
      default:
         break;
   } // end switch
   return (MRESULT)(*pfnwpLBox)(hwnd, msg, mp1, mp2);
}


//==========================================================================\
// procedura button superclassato x l'help contestuale                      |
//==========================================================================/

MRESULT EXPENTRY ACCHBtnWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   HWND hParent;
   if (msg == WM_MOUSEMOVE && ((hParent = WinQueryWindow(hwnd, QW_PARENT))
                                    == WinQueryActiveWindow(HWND_DESKTOP)))
      WinPostMsg(hParent, WM_BUBBLEHELP, MPFROMHWND(hwnd), MPVOID);
   return (MRESULT) (*pfnwpBtn)(hwnd, msg, mp1, mp2);
}


//==========================================================================\
// procedura status bar superclassate x l'help contestuale                  |
//==========================================================================/

MRESULT EXPENTRY ACCHSBarWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   HWND hParent;
   if (msg == WM_MOUSEMOVE && ((hParent = WinQueryWindow(hwnd, QW_PARENT))
                                    == WinQueryActiveWindow(HWND_DESKTOP)))
      WinPostMsg(hParent, WM_BUBBLEHELP, MPFROMHWND(hwnd), MPVOID);
   return (MRESULT) (*pfnwpSbar)(hwnd, msg, mp1, mp2);
}


//==========================================================================\
// procedura personalizzata della finestra listbox file per                 |
// l'intercettazione di WM_CONTEXTMENU e per mimare la modalit… di selezione|
// estesa dei container                                                     |
//==========================================================================/

MRESULT EXPENTRY FileBoxWinProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   POINTL ptl[1];
   PLBOXFILE plbfile = (PLBOXFILE)WinQueryWindowPtr(hwnd, QWL_USER);
   SWP swp;
   SHORT idx, i, count = 0;
   BOOL flag = FALSE;
   switch (msg) {
      case WM_CONTEXTMENU:
         WinPostMsg(WinQueryWindow(hwnd, QW_PARENT), WM_POPUPMENU,
                    MPFROMLONG((LONG)WinQueryWindowUShort(hwnd, QWS_ID)),
                    MPFROMHWND(hwnd));
         break;
      case WM_BUTTON1DOWN:  // selezione item
         // se non Š selezione multipla esegue procedura normale
         if (!plbfile->pam->pro.sel.extsel) break;
         // se Š stato premuto Ctrl o Shift esegue procedura normale
         if ((SHORT2FROMMP(mp2) & KC_CTRL) || (SHORT2FROMMP(mp2) & KC_SHIFT))
            break;
         // calcola indice item selezionato
         WinQueryWindowPos(hwnd, &swp);
         idx = (SHORT)(*(plbfile->pfnwp))(hwnd, LM_QUERYTOPINDEX,
                                          MPFROMLONG(0L), MPFROMLONG(0L)) +
                ((swp.cy - SHORT2FROMMP(mp1)) / plbfile->pam->pro.gen.cyFont);
         // se l'indice non Š valido (click in una zona vuota della listbox),
         // l'item non Š gi… selezionato o Š l'unico selezionato ritorna
         for (i = (SHORT)(*(plbfile->pfnwp))(hwnd, LM_QUERYSELECTION,
                                     MPFROMSHORT(LIT_FIRST), MPFROMLONG(0L));
              i > LIT_NONE && (i <= idx || count < 2);
              i = (SHORT)(*(plbfile->pfnwp))(hwnd, LM_QUERYSELECTION,
                                             MPFROMSHORT(i), MPFROMLONG(0L))) {
            count++;
            if (i == idx) flag = TRUE;
         } /* endfor */
         if (!flag || count < 2) break;
         // deseleziona tutti i file
         for (i = (SHORT)(*(plbfile->pfnwp))(hwnd, LM_QUERYSELECTION,
                                     MPFROMSHORT(LIT_FIRST), MPFROMLONG(0L));
              i != LIT_NONE;
              i = (SHORT)(*(plbfile->pfnwp))(hwnd, LM_QUERYSELECTION,
                                             MPFROMSHORT(i), MPFROMLONG(0L))) {
            plbfile->pam->LMsel = TRUE;
            (*(plbfile->pfnwp))(hwnd, LM_SELECTITEM, MPFROMSHORT(i),
                                MPFROMLONG(FALSE));
            plbfile->pam->LMsel = FALSE;
         } // end for      ---    seleziona file corrente
         break;
      case WM_CHAR:// se viene rilasciato tasto freccia su/gi— o pag su/gi—
         if (CHARMSG(&msg)->fs & KC_KEYUP &&              // rilascio tasto
             CHARMSG(&msg)->fs & KC_VIRTUALKEY &&         // virtual key
             (CHARMSG(&msg)->vkey == VK_UP) ||            // freccia su
             (CHARMSG(&msg)->vkey == VK_DOWN) ||          // freccia gi—
             (CHARMSG(&msg)->vkey == VK_PAGEUP) ||        // pag su
             (CHARMSG(&msg)->vkey == VK_PAGEDOWN)) {      // pag gi—
            MRESULT mr = (*pfnwpLBox)(hwnd, msg, mp1, mp2);
            WinPostMsg(WinQueryWindow(hwnd, QW_PARENT), WM_LBOXBTN1UP,
                       MPFROMLONG((LONG)WinQueryWindowUShort(hwnd, QWS_ID)),
                       MPFROMHWND(hwnd));
            return mr;
         } // end if
         break;
      case WM_BUTTON1UP: {
         MRESULT mr = (*pfnwpLBox)(hwnd, msg, mp1, mp2);
         WinPostMsg(WinQueryWindow(hwnd, QW_PARENT), WM_LBOXBTN1UP,
                    MPFROMLONG((LONG)WinQueryWindowUShort(hwnd, QWS_ID)),
                    MPFROMHWND(hwnd));
         return mr;
      } // end case WM_BUTTON1UP
      default: 
         break;
   } /* endswitch */
   return (MRESULT) (*(plbfile->pfnwp))(hwnd, msg, mp1, mp2);
}
