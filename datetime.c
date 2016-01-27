//==========================================================================\
// datetime.c : editazione data/ora file                                    |
//   MRESULT OpenEditDateTimeDlg(HWND hwnd, PATTMAN pam, ULONG id);         |
//   MRESULT EXPENTRY DateTimeDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
//   MRESULT InitDateTimeDlg(HWND hwnd, PEDITDATETIME pedt);                |
//   VOID SetDateTimeSpins(HWND hwnd, PEDITDATETIME pedt);                  |
//   VOID SetDateTimeLimits(HWND hwnd, PEDITDATETIME pedt);                 |
//   VOID GetDateTimePref(PFILESPECS pfs);                                  |
//==========================================================================/

#define INCL_DOSNLS
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"
#include <spinbtn.h>


//==========================================================================\
// OpenEditDateTimeDlg : visualizza dialogo editazione data/ora  file       |
//==========================================================================/

MRESULT OpenEditDateTimeDlg(HWND hwnd, PATTMAN pam, ULONG id) {
   static BOOL isDlg;
   EDITDATETIME edt;
   SWP swp;

   if (isDlg) return (MRESULT)FALSE;
   isDlg = TRUE;
   switch (id) {
      case STB_WRITTEN:
         edt.pft = &pam->fsp.fsNew.ftimeLastWrite;
         edt.pfd = &pam->fsp.fsNew.fdateLastWrite;
         edt.pszTitle = SZ_LASTCHANGE;
         break;
      case STB_CREATED:
         edt.pft = &pam->fsp.fsNew.ftimeCreation;
         edt.pfd = &pam->fsp.fsNew.fdateCreation;
         edt.pszTitle = SZ_LASTCREATE;
         break;
      default: // TXT_ACCESSED
         edt.pft = &pam->fsp.fsNew.ftimeLastAccess;
         edt.pfd = &pam->fsp.fsNew.fdateLastAccess;
         edt.pszTitle = SZ_LASTACCESS;
         break;
   } // end switch ---     calcola posizione dialogo
   WinQueryWindowPos(hwnd, &swp);
   edt.pts.x = pam->pro.gen.pswp[29].x + pam->pro.gen.pswp[29].cx + 3 + swp.x;
   edt.pts.y = pam->pro.gen.pswp[29].y + swp.y;
   edt.style = pam->fsp.dtFrm;
   edt.ulVer = pam->pro.ulVer;
   edt.usSize = sizeof(EDITDATETIME);
   if (WinDlgBox(HWND_DESKTOP, hwnd, (PFNWP)DateTimeDlgProc, NULLHANDLE,
                 EDITDATETIME_DLG, (PVOID)&edt)) { // se si Š premuto OK
      pam->fsp.fsNew.cbFile = 1;                   // setta flag attr cambiati
      ShowDateTime(hwnd, &pam->fsp);
   } // end if
   isDlg = FALSE;
   return (MRESULT)FALSE;
}


//==========================================================================\
// procedura dialogo editazione data/ora file                               |
//==========================================================================/

MRESULT EXPENTRY DateTimeDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   switch (msg) {

      case WM_INITDLG :
         return InitDateTimeDlg(hwnd, (PEDITDATETIME)mp2);
      case WM_CONTROL:                     // cambiamento valori data ora
         if (SHORT2FROMMP(mp1) == SPBN_CHANGE &&
             (SHORT1FROMMP(mp1) == SPIN_HOUR ||
             SHORT1FROMMP(mp1) == SPIN_MIN ||
             SHORT1FROMMP(mp1) == SPIN_SEC ||
             SHORT1FROMMP(mp1) == SPIN_DAY ||  
             SHORT1FROMMP(mp1) == SPIN_MONTH ||
             SHORT1FROMMP(mp1) == SPIN_YEAR)) {
            WinEnableControl(hwnd, BTN3_OK, TRUE); // abilita pulsante OK
            if (SHORT1FROMMP(mp1) == SPIN_MONTH || // ricalcola limiti
                SHORT1FROMMP(mp1) == SPIN_YEAR) {  // spinbutton day
               ULONG ulMonth, ulYear;
               DlgSpinQueryLong(hwnd, SPIN_MONTH, &ulMonth);
               DlgSpinQueryLong(hwnd, SPIN_YEAR, &ulYear);
               DlgSpinSetLimits(hwnd, SPIN_DAY, GetMaxDay(ulMonth,ulYear), 1L);
            } /* endif */
         } /* endif */
         break;
      case WM_COMMAND:
         if (LOUSHORT(mp1) == BTN3_OK) {           // legge nuovi attributi
            ULONG ulTmp;
            PEDITDATETIME pedt = (PEDITDATETIME) WinQueryWindowPtr(hwnd, QWL_USER);
            DlgSpinQueryLong(hwnd, SPIN_HOUR, &ulTmp);
            pedt->pft->hours = (USHORT)ulTmp;
            DlgSpinQueryLong(hwnd, SPIN_MIN, &ulTmp);
            pedt->pft->minutes = (USHORT)ulTmp;
            DlgSpinQueryLong(hwnd, SPIN_SEC, &ulTmp);
            pedt->pft->twosecs = (USHORT)(ulTmp / 2);
            DlgSpinQueryLong(hwnd, SPIN_DAY, &ulTmp);
            pedt->pfd->day = (USHORT)ulTmp;
            DlgSpinQueryLong(hwnd, SPIN_MONTH, &ulTmp);
            pedt->pfd->month = (USHORT)ulTmp;
            DlgSpinQueryLong(hwnd, SPIN_YEAR, &ulTmp);
            pedt->pfd->year = ulTmp < 80? (USHORT)(ulTmp + 20):
                                          (USHORT)(ulTmp - 80);
         } /* endif */
         mp1 = MPFROMLONG(LOUSHORT(mp1) == BTN3_OK);
         break;
      case WM_CLOSE:
         mp1 = NULL;
         break;
      default: 
         break;
   } // end switch
   return WinDefDlgProc(hwnd, msg, mp1, mp2);
}


//==========================================================================\
// procedura inizializzazione dialogo editazione data/ora file              |
//==========================================================================/

MRESULT InitDateTimeDlg(HWND hwnd, PEDITDATETIME pedt) {
   SWP aSwp[4];
   HAB hab = WinQueryAnchorBlock(hwnd);
   HWND hMain = WinQueryWindow(hwnd, QW_OWNER);
   CHAR buf[FACESIZE];
   
   WinSetWindowPtr(hwnd, QWL_USER, (PVOID)pedt);
   // riposiziona controlli secondo formato impostato nelle preferenze
   if (pedt->ulVer < 40)
      WinSetPresParam(hwnd, PP_FONTNAMESIZE, 7, (PVOID)"8.Helv");
   PrfQueryProfileString(HINI_USERPROFILE, "PM_SystemFonts",
                         "WindowTitles", "", buf, FACESIZE);
   WinSetPresParam(WinWindowFromID(hwnd, FID_TITLEBAR), PP_FONTNAMESIZE,
                   sstrlen(buf) + 1, (PVOID)(buf));
   switch (pedt->style) {
      case MM_DD_YY : // mese-giorno anno: scambia posizione mese con giorno
         DlgQueryCtlPos(hwnd, TXT_DAY, &aSwp[0]);
         DlgQueryCtlPos(hwnd, SPIN_DAY, &aSwp[1]);
         DlgQueryCtlPos(hwnd, TXT_MONTH, &aSwp[2]);
         DlgQueryCtlPos(hwnd, SPIN_MONTH, &aSwp[3]);
         WinSetWindowPos(aSwp[0].hwnd, 0, aSwp[2].x, aSwp[2].y, 0, 0, SWP_MOVE); 
         WinSetWindowPos(aSwp[1].hwnd, 0, aSwp[3].x, aSwp[3].y, 0, 0, SWP_MOVE);
         WinSetWindowPos(aSwp[2].hwnd, 0, aSwp[0].x, aSwp[0].y, 0, 0, SWP_MOVE);
         WinSetWindowPos(aSwp[3].hwnd, 0, aSwp[1].x, aSwp[1].y, 0, 0, SWP_MOVE);
         break;
      case YY_MM_DD : // anno-mese-giorno: scambia posizione anno con giorno
         DlgQueryCtlPos(hwnd, TXT_DAY, &aSwp[0]);
         DlgQueryCtlPos(hwnd, SPIN_DAY, &aSwp[1]);
         DlgQueryCtlPos(hwnd, TXT_YEAR, &aSwp[2]);
         DlgQueryCtlPos(hwnd, SPIN_YEAR, &aSwp[3]);
         WinSetWindowPos(aSwp[0].hwnd, 0, aSwp[2].x, aSwp[2].y, 0, 0, SWP_MOVE); 
         WinSetWindowPos(aSwp[1].hwnd, 0, aSwp[3].x, aSwp[3].y, 0, 0, SWP_MOVE);
         WinSetWindowPos(aSwp[2].hwnd, 0, aSwp[0].x, aSwp[0].y, 0, 0, SWP_MOVE);
         WinSetWindowPos(aSwp[3].hwnd, 0, aSwp[1].x, aSwp[1].y, 0, 0, SWP_MOVE);
         break;
      default:                  // giorno-mese-anno
         break;
   } /* endswitch */
   // imposta limiti spinbuttons
   SetDateTimeLimits(hwnd, pedt);
   // scrive dati correnti
   SetDateTimeSpins(hwnd, pedt);
   WinSetWindowText(hwnd, pedt->pszTitle);
   WinEnableControl(hwnd, BTN3_OK, FALSE);
   WinSetWindowPos(hwnd, 0, pedt->pts.x, pedt->pts.y,0, 0, SWP_MOVE | SWP_SHOW);
   return (MRESULT) FALSE;
}


//==========================================================================\
// setta gli spinbuttons secondo data e ora                                 |
//==========================================================================/

VOID SetDateTimeSpins(HWND hwnd, PEDITDATETIME pedt) {
   DlgSpinSetValue(hwnd, SPIN_HOUR, (LONG)pedt->pft->hours);
   DlgSpinSetValue(hwnd, SPIN_MIN, (LONG)pedt->pft->minutes);
   DlgSpinSetValue(hwnd, SPIN_SEC, (LONG)(2 * pedt->pft->twosecs));
   DlgSpinSetValue(hwnd, SPIN_DAY, (LONG)pedt->pfd->day);
   DlgSpinSetValue(hwnd, SPIN_MONTH, (LONG)pedt->pfd->month);
   DlgSpinSetValue(hwnd, SPIN_YEAR, (LONG)(pedt->pfd->year > 19?
                                           pedt->pfd->year - 20:
                                           pedt->pfd->year + 80));
}


//==========================================================================\
// setta i limiti degli spinbutton                                          |
// HWND hwnd = handle della finestra                                        |
// BOOL flag = TRUE modalit… readonly                                       |
// PFILESPECS pfsp = puntatore struttura dati file                          |
//==========================================================================/

VOID SetDateTimeLimits(HWND hwnd, PEDITDATETIME pedt) {
   DlgSpinSetLimits(hwnd, SPIN_HOUR, 23, 0);
   DlgSpinSetLimits(hwnd, SPIN_MIN, 59, 0);
   DlgSpinSetLimits(hwnd, SPIN_SEC, 59, 0);
   // salta il settaggio di SPIN_DAY in quanto dipendente dal SPIN_MONTH
   DlgSpinSetLimits(hwnd, SPIN_MONTH, 12, 1);
   DlgSpinSetLimits(hwnd, SPIN_YEAR, 99, 0);
   DlgSpinSetLimits(hwnd, SPIN_DAY, GetMaxDay(pedt->pfd->month,
                                              pedt->pfd->year), 1L);
   DlgSpinSetTextLimit(hwnd, SPIN_HOUR, 2);
   DlgSpinSetTextLimit(hwnd, SPIN_MIN, 2);
   DlgSpinSetTextLimit(hwnd, SPIN_SEC, 2);
   DlgSpinSetTextLimit(hwnd, SPIN_DAY, 2);
   DlgSpinSetTextLimit(hwnd, SPIN_MONTH, 2);
   DlgSpinSetTextLimit(hwnd, SPIN_YEAR, 2);
}


//==========================================================================\
// controlla impostazioni separatore migliaia, data e ora                   |
// PFILESPECS pfsp = puntatore struttura dati file                          |
//==========================================================================/

VOID GetDateTimePref(PFILESPECS pfs) {
   COUNTRYCODE cc = {0};
   COUNTRYINFO ci = {0};
   ULONG ulC = 0;

   if (DosQueryCtryInfo(sizeof(COUNTRYINFO), &cc, &ci, &ulC)) {
      pfs->chD = '/';
      pfs->chT = ':';
      pfs->dtFrm = 0;
      pfs->milSep = ',';
   } else {
      pfs->chD = ci.szDateSeparator[0];
      pfs->chT = ci.szTimeSeparator[0];
      pfs->dtFrm = ci.fsDateFmt;
      pfs->milSep = ci.szThousandsSeparator[0];
   } /* endif */
}
