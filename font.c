//==========================================================================\
// font.c : funzioni dialogo font                                           |
//==========================================================================/

#define INCL_WIN
#include <os2.h>
#include <stdio.h>
#include <string.h>
#include <spinbtn.h>
#include <efdlg.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "preferences.h"
#include "prefmessages.h"


//==========================================================================\
// mostra finestra dialogo font                                             |
// parametri:                                                               |
// PSZ pszFont = nome font completo                                         |
// risultato:                                                               |
// BOLL rc = TRUE (si Š premuto OK) FAALSE (si Š premuto CANCEL)            |
//==========================================================================/

BOOL ShowFontDlg(HWND hwnd, PSZ pszFont) {
   FONTDLG fntDlg;
   char szFname[FACESIZE];

   memset(&fntDlg, 0, sizeof(FONTDLG));
   fntDlg.cbSize = sizeof(FONTDLG);
   fntDlg.hpsScreen = WinGetPS(hwnd);
   fntDlg.pszTitle = "Attribute Manager Font";
   fntDlg.pszPreview = "Attribute Manager";
   fntDlg.pfnDlgProc = NewFontDlgProc;
   fntDlg.pszFamilyname = szFname;
   fntDlg.usFamilyBufLen = FACESIZE;
   fntDlg.fl = FNTS_CENTER | FNTS_FIXEDWIDTHONLY | FNTS_RESETBUTTON |
               FNTS_NOSYNTHESIZEDFONTS;
   fntDlg.clrFore = CLR_BLACK ;
   fntDlg.clrBack = CLR_WHITE ;
   BreakFontAttrs(pszFont, szFname, &fntDlg.flStyle, &fntDlg.fxPointSize);
   WinFontDlg(HWND_DESKTOP, HWND_DESKTOP, &fntDlg);
   if (fntDlg.lReturn == DID_OK)
      JoinFontAttrs(pszFont, fntDlg.fAttrs.szFacename,
                    fntDlg.fAttrs.fsSelection, fntDlg.fxPointSize);
   return fntDlg.lReturn == DID_OK;
}


//==========================================================================\
// separa nelle varie stringhe componenti il font corrente                  |
// parametri:                                                               |
// 
// valore restituito:                                                       |
//            |
//==========================================================================/

VOID BreakFontAttrs(PSZ pszFont, PSZ pszName, PULONG pulStyle, PFIXED pfix) {
   UINT i = 0;

   // ricava dimensione font
   while (*pszFont != '.') i += i * 10 + *pszFont++ - '0';
   *pfix = MAKEFIXED(i, 0);
   // ricava facename e stili
   while (*pszFont) {
      while (*pszFont == ' ' || *pszFont == '.') ++pszFont;
      if (!sstrncmp(pszFont, "Italic", 6)) {
         *pulStyle |= FATTR_SEL_ITALIC;
         pszFont += 6;
      } else if (!sstrncmp(pszFont, "Bold", 4)) {
         *pulStyle |= FATTR_SEL_BOLD;
         pszFont += 4;
      } else if (!sstrncmp(pszFont, "Underscore", 10)) {
         *pulStyle |= FATTR_SEL_UNDERSCORE;
         pszFont += 10;
      } else if (!sstrncmp(pszFont, "Outline", 7)) {
         *pulStyle |= FATTR_SEL_OUTLINE;
         pszFont += 7;
      } else if (!sstrncmp(pszFont, "Strikeout", 9)) {
         *pulStyle |= FATTR_SEL_STRIKEOUT;
         pszFont += 9;
      } else {
         while ((*pszName++ = *pszFont++) != ' ' && *pszFont) ;
      } /* endif */
   } /* endwhile */
   *pszName = 0;
}


//==========================================================================\
//                      |
// parametri:                                                               |
// 
// valore restituito:                                                       |
//            |
//==========================================================================/

VOID JoinFontAttrs(PSZ pszFont, PSZ pszName, ULONG ulStyle, FIXED fix) {
   char fontsize[4];
   sstrcpy(pszFont, i2str(FIXEDINT(fix), fontsize));
   sstrcat(pszFont, ".");
   sstrcat(pszFont, pszName);
   if (ulStyle & FATTR_SEL_BOLD) sstrcat(pszFont, " Bold");
   if (ulStyle & FATTR_SEL_ITALIC) sstrcat(pszFont, " Italic");
   if (ulStyle & FATTR_SEL_OUTLINE) sstrcat(pszFont, " Outline");
   if (ulStyle & FATTR_SEL_UNDERSCORE) sstrcat(pszFont, " Underscore");
   if (ulStyle & FATTR_SEL_STRIKEOUT) sstrcat(pszFont, " Strikeout");
}


//==========================================================================\
//                      |
// parametri:                                                               |
// 
// valore restituito:                                                       |
//            |
//==========================================================================/

MRESULT EXPENTRY NewFontDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   switch (msg) {
      case WM_INITDLG:
         DlgShowCtl(hwnd, DID_DISPLAY_FILTER, FALSE);
         DlgShowCtl(hwnd, DID_PRINTER_FILTER, FALSE);
         DlgShowCtl(hwnd, DID_OUTLINE, FALSE);
         DlgShowCtl(hwnd, DID_UNDERSCORE, FALSE);
         DlgShowCtl(hwnd, DID_STRIKEOUT, FALSE);
         DlgShowCtl(hwnd, DID_EMPHASIS_GROUPBOX, FALSE);
         break;
      default:
        break;
   } /* endswitch */
   return WinDefFontDlgProc(hwnd, msg, mp1, mp2);
}
