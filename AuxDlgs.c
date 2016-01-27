//==========================================================================\
// auxdlgs.c : procedure per i dialoghi secondari                           |
// MRESULT EXPENTRY SaveMultiDlgProc(HWND hwnd, ULONG msg,                  |
//                                   MPARAM mp1, MPARAM mp2);               |
// MRESULT EXPENTRY ProgDlgProc(HWND hwnd, ULONG msg,                       |
//                              MPARAM mp1, MPARAM mp2);                    |
// MRESULT EXPENTRY LogoDlgProc(HWND hwnd, ULONG msg,                       |
//                              MPARAM mp1, MPARAM mp2);                    |
//==========================================================================/

#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#include <EFDlg.h>
#include <listbox.h>
#include <mywinutil.h>
#include <spinbtn.h>
#include <stdio.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"


//==========================================================================\
// procedura del dialogo per il salvataggio multiplo (+ file selezionati)   |
//==========================================================================/

MRESULT EXPENTRY SaveMultiDlgProc(HWND hwnd,ULONG msg, MPARAM mp1, MPARAM mp2) {
   ULONG flags = 0;
   static PATTMAN pam;

   switch (msg) {
      // setta il testo delle varie check box secondo i nuovi attributi
      case WM_INITDLG : {
         HWND HOwner;
         char datetime[24];
         char buf[FACESIZE];
         FFDATE ffd;
         pam = (PATTMAN)PVOIDFROMMP(mp2);      // recupera indirizzo struttura
         // imposta il font della barra del titolo:
         PrfQueryProfileString(HINI_USERPROFILE, "PM_SystemFonts",
                               "WindowTitles", "9.WarpSans", buf, FACESIZE);
         WinSetPresParam(WinWindowFromID(hwnd, FID_TITLEBAR), PP_FONTNAMESIZE,
                         sstrlen(buf) + 1, (PVOID)(buf));
         HOwner = WinQueryOwnerHandle(hwnd);   // handle del dialogo princip
         ReadNewOrdAttrs(HOwner, &pam->fsp);//legge nuovi attributi ordin
         // aggiorna il testo delle varie checkbox del dialogo
         WinSetDlgItemText(hwnd, CKBOX_A,
                           pam->fsp.fsNew.attrFile & FILE_ARCHIVED?
                           "[+] Archive": "[-] Archive");
         WinSetDlgItemText(hwnd, CKBOX_H,
                           pam->fsp.fsNew.attrFile & FILE_HIDDEN?
                           "[+] Hidden": "[-] Hidden");
         WinSetDlgItemText(hwnd, CKBOX_R,
                           pam->fsp.fsNew.attrFile & FILE_READONLY?
                           "[+] Read only": "[-] Read only");
         WinSetDlgItemText(hwnd, CKBOX_S,
                           pam->fsp.fsNew.attrFile & FILE_SYSTEM?
                           "[+] System": "[-] System");
         // data ora ultima scrittura secondo formato data
         FormatDate(&pam->fsp.fsNew.fdateLastWrite, &ffd, pam->fsp.dtFrm);
         sprintf(datetime, "date: %02u%c%02u%c%02u",
                 ffd.a, pam->fsp.chD, ffd.b, pam->fsp.chD, ffd.c);
         WinSetDlgItemText(hwnd, CKBOX_CHDATE, datetime);
         sprintf(datetime, "time: %02u%c%02u%c%02u",
                 pam->fsp.fsNew.ftimeLastWrite.hours, pam->fsp.chT,
                 pam->fsp.fsNew.ftimeLastWrite.minutes, pam->fsp.chT,
                 pam->fsp.fsNew.ftimeLastWrite.twosecs * 2);
         WinSetDlgItemText(hwnd, CKBOX_CHTIME, datetime);
         // se il FS non suporta creation e last access termina qui
         if (!pam->fsp.hpfs) break; // eventualmente esce
         // mostra controlli creation-last access
         DlgShowCtl(hwnd, GRP_LASTCREATE, TRUE);
         DlgShowCtl(hwnd, CKBOX_CRTIME, TRUE);
         DlgShowCtl(hwnd, CKBOX_CRDATE, TRUE);
         DlgShowCtl(hwnd, GRP_LASTACCESS, TRUE);
         DlgShowCtl(hwnd, CKBOX_ACTIME, TRUE);
         DlgShowCtl(hwnd, CKBOX_ACDATE, TRUE);
         // data ora creazione secondo formato data
         FormatDate(&pam->fsp.fsNew.fdateCreation, &ffd, pam->fsp.dtFrm);
         sprintf(datetime, "date: %02u%c%02u%c%02u",
                 ffd.a, pam->fsp.chD, ffd.b, pam->fsp.chD, ffd.c);
         WinSetDlgItemText(hwnd, CKBOX_CRDATE, datetime);
         sprintf(datetime, "time: %02u%c%02u%c%02u",
                 pam->fsp.fsNew.ftimeCreation.hours, pam->fsp.chT,
                 pam->fsp.fsNew.ftimeCreation.minutes, pam->fsp.chT,
                 pam->fsp.fsNew.ftimeCreation.twosecs * 2);
         WinSetDlgItemText(hwnd, CKBOX_CRTIME, datetime);
         // data ora lastchanged: secondo formato data
         FormatDate(&pam->fsp.fsNew.fdateLastAccess, &ffd, pam->fsp.dtFrm);
         sprintf(datetime, "date: %02u%c%02u%c%02u",
                 ffd.a, pam->fsp.chD, ffd.b, pam->fsp.chD, ffd.c);
         WinSetDlgItemText(hwnd, CKBOX_ACDATE, datetime);
         sprintf(datetime, "time: %02u%c%02u%c%02u",
                 pam->fsp.fsNew.ftimeLastAccess.hours, pam->fsp.chT,
                 pam->fsp.fsNew.ftimeLastAccess.minutes, pam->fsp.chT,
                 pam->fsp.fsNew.ftimeLastAccess.twosecs * 2);
         WinSetDlgItemText(hwnd, CKBOX_ACTIME, datetime);
         } break;
      case WM_COMMAND : // se si preme OK controlla lo stato delle checkbox
         if (LOUSHORT(mp1) == BTN_4_OK) {
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_A)? UPDT_A: 0;
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_H)? UPDT_H: 0;
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_R)? UPDT_R: 0;
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_S)? UPDT_S: 0;
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_SUBJ)? UPDT_SUBJ: 0;
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_KEY)? UPDT_KEY: 0;
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_CMNT)? UPDT_CMNT: 0;
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_CHTIME)? UPDT_CHTIME: 0;
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_CHDATE)? UPDT_CHDATE: 0;
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_CRTIME)? UPDT_CRTIME: 0;
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_CRDATE)? UPDT_CRDATE: 0;
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_ACTIME)? UPDT_ACTIME: 0;
            flags |= WinQueryButtonCheckstate(hwnd, CKBOX_ACDATE)? UPDT_ACDATE: 0;
            WinDismissDlg(hwnd, flags);
         } else {
            WinDismissDlg(hwnd, 0);
         } /* endif */
         break;
      case WM_CLOSE :
         WinDismissDlg(hwnd, 0);
         break;
      default: 
         return WinDefDlgProc(hwnd, msg, mp1, mp2);
   } /* endswitch */
   return (MRESULT) FALSE;
}


//==========================================================================\
// dialogo visibile quando si salva gli attributi di molti file             |
//==========================================================================/

MRESULT EXPENTRY ProgDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   return WinDefDlgProc(hwnd, msg, mp1, mp2);
}


//==========================================================================\
// procedura dialogo logo                                                   |
//==========================================================================/
 
MRESULT EXPENTRY LogoDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   switch (msg) {
      SWP aSwp[3];
      
      case WM_INITDLG : {
         HAB hab = WinQueryAnchorBlock(hwnd);
         LONG xScreen;
         LONG yScreen;
         aSwp[0].hwnd = WinWindowFromID(hwnd, BMP_CTRL);
         aSwp[0].x = 10;
         aSwp[0].y = 90;
         aSwp[0].cx = 300;
         aSwp[0].cy = 90;
         aSwp[0].fl = SWP_MOVE | SWP_SIZE;
         aSwp[1].hwnd = WinWindowFromID(hwnd, TXT_VERSION);
         aSwp[1].x = 10;
         aSwp[1].y = 55;
         aSwp[1].cx = 300;
         aSwp[1].cy = 35;
         aSwp[1].fl = SWP_MOVE | SWP_SIZE;
         aSwp[2].hwnd = WinWindowFromID(hwnd, LOGO_BTN);
         aSwp[2].x = 110;
         aSwp[2].y = 10;
         aSwp[2].cx = 100;
         aSwp[2].cy = 30;
         aSwp[2].fl = SWP_MOVE | SWP_SIZE;
         WinSetMultWindowPos(hab, aSwp, 3);
         xScreen = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN) / 2 - 160;
         yScreen = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN) / 2 - 100;
         WinSetWindowPos(hwnd, HWND_TOP, xScreen, yScreen, 320, 200,
                         SWP_SHOW | SWP_MOVE | SWP_SIZE);
         } break;
      case WM_CLOSE:
      case WM_COMMAND:
         WinDismissDlg(hwnd, 0);
         break;
      default: 
         break;
   } // end switch
   return WinDefDlgProc(hwnd, msg, mp1, mp2);
}
