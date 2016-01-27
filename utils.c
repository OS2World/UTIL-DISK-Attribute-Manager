//==========================================================================\
// utils.c : funzioni di utilit…                                            |
// BOOL WildCmp(char* mask, char* cmp);                                     |
// BOOL isWildCh(PSZ pszFile);                                              |
// LONG GetMaxDay(USHORT month, USHORT year);                               |
// PSZ i2str(int i, PSZ psz);                                               |
// SHORT isInListBox(HWND hwnd, PSZ pszFile, ULONG ID);                     |
// PSZ GetParms(HWND hwnd, PSZ pszOut, PATTMAN pam, PSZ pszImp, PSZ pszParms);
// BOOL Subclass(HWND hwnd, USHORT usID, PFNWP newProc);                    |
// BOOL SubclassFileList(HWND hwnd ,PATTMAN pam, PFNWP newProc);            |
// BOOL isExpired(HMQ hmq, HAB hab);                                        |
// int Terminate(HAB hab, HMQ hmq, int rc);                                 |
// PSZ i2fstr(int i, PSZ psz, CHAR ch);                                     |
// BOOL RegisterCustomControls(HAB hab);                                    |
// VOID FormatDate(PFDATE pfd, PFFDATE pffd, ULONG ulFrm);                  |
//==========================================================================/

#define INCL_WIN
#include <os2.h>
#include <stdio.h>
#include <listbox.h>
#include <3dctls.h>
#include "attman.h"
#include "interface.h"
#include "funzioni.h"
#include "definitions.h"
#include "messages.h"

//==========================================================================\
// ritorna TRUE se cmp risponde al criterio specificato in mask             |
// char* mask = maschera contenente wildchar                                |
// char* cmp  = stringa da comparare con "mask"                             |
//==========================================================================/

BOOL WildCmp(char* mask, char* cmp) {
   while (*cmp) {
      switch (*mask++) {
         case '*':
            if (!*mask) return TRUE;
            while (*cmp && !WildCmp(mask, cmp)) ++cmp;
            break;
         case '?':
            ++cmp;
            break;
         default: 
            if ((*(mask - 1) == *cmp) ||                   // identit…
                (*(mask - 1) == (*cmp + 'A' - 'a') &&
                 *cmp > '`' && *cmp < '{') ||   // mask maiusc cmp minuscolo
                (*(mask - 1) == (*cmp + 'a' - 'A') &&
                 *cmp > '@' && *cmp < '[')) {   // mask minusc cmp maiuscolo
               ++cmp;
               break;
            } else {
               return FALSE;
            } // endif
      } /* endswitch */
   } /* endwhile */
   return *mask? FALSE: TRUE;
}


//==========================================================================\
// restituisce TRUE se nella stringa ci sono wild char (*?)                 |
// PSZ pszFile = stringa da esaminare per la presenza di wildchars          |
//==========================================================================/

BOOL isWildCh(PSZ pszFile) {
   do {
      if (*pszFile == '*' || *pszFile == '?') return TRUE;
   } while (*pszFile++);
   return FALSE;
}


//==========================================================================\
// restituisce l'ultimo giorno del mese dipendente dal mese e dall'anno     |
// USHORT month = numero (1-12) corrispondente al mese                      |
// USHORT year  = numero di ani dopo il 1980                                |
//==========================================================================/

LONG GetMaxDay(USHORT month, USHORT year) {
   year += 1980;
   switch (month) {
      case 4:
      case 6:
      case 9:
      case 11:
         return 30;
      case 2:
         return ((!(year % 4) && (year % 100)) || !(year % 400))? 29: 28;
      default: 
        break;
   } /* endswitch */
   return 31;
}


//==========================================================================\
// converte un intero positivo in stringa                                   |
// parametri:                                                               |
// int i      = intero da convertire                                        |
// PSZ psz    = buffer stringa risultato della conversione                  |
// risultato:                                                               |
// PSZ pszRes = puntatore alla stringa ottenuta                             |
//==========================================================================/

PSZ i2str(int i, PSZ psz) {
   char swap = 0;
   PSZ s = psz;
   PSZ start = psz;

   if (i < 0) { swap = '-'; i *= -1; }
   do { *s++ = i % 10 + '0'; } while (i /= 10);                    // convert
   if (swap) *s++ = swap;
   *s-- = 0;
   while (start < s) { swap = *start; *start++ = *s; *s-- = swap; } //reverse
   return psz;
}


//==========================================================================\
// Controlla la presenza di una stringa in una listbox il cui contenuto Š   |
// ordinato alfabeticamente. Se la stringa non Š presente restituisce       |
// come numero negativo la posizione successiva a quella in cui deve essere |
// inserito il nuovo item                                                   |
// piIns la posizione di inserzione della nuova stringa                     |
// Parametri:                                                               |
// HWND hwnd   = handle finestra principale                                 |
// PSZ pszFile = nome file da controllare                                   |
// ULONG ID    = identita controllo listbox                                 |
// Risultato:                                                               |
// SHORT idx   = <0 se l'item non Š presente nella listbox, altrimenti      |
//               l'indice corrispondente                                    |
//==========================================================================/

SHORT isInListBox(HWND hwnd, PSZ pszFile, ULONG ID) {
   int comp, low, mid, hi;
   char achFile[256];

   low = 0;
   hi = DlgLboxQueryItemCount(hwnd, ID) - 1;
   while (low <= hi) {
      mid = (low + hi) / 2;
      DlgLboxQueryItemText(hwnd, ID, mid, achFile, 256);
      if ((comp = sstricmp(pszFile, achFile)) < 0)
         hi = mid - 1;
      else if (comp > 0)
         low = mid + 1;
      else
         return mid;
   } /* endwhile */
   return -(hi + 2);
}


//==========================================================================\
// GetParms: formatta i parametri del programma sostituendo gli opportuni   |
// valori ai caratteri che seguono il simbolo %. Simboli validi sono:       |
// %d o %D nome directory temporanea                                        |
// %f o %F nome file corrente compreso il percorso                          |
// %i o %I nome file che verr… in seguito importato nei commenti o subject  |
// %p o %P nome path corrente                                               |
// %%      carattere %                                                      |
// parametri:                                                               |
// PSZ pszOut = puntatore al buffer in cui verranno scritti i parametri     |
// PATTMAN pam                                                              |
// PSZ pszImp = nome del file da importare                                  |
// PSZ pszParms = stringa parametri da convertire                           |
// valore restituito:                                                       |
// PSZ = puntatore al buffer con i parametri                                |
//==========================================================================/

PSZ GetParms(HWND hwnd, PSZ pszOut, PATTMAN pam, PSZ pszImp, PSZ pszParms) {
   PSZ pszStart = pszOut;
   PSZ pszErr = pszParms;
   while (*pszParms) {
      if (*pszParms == '%') { // carattere sostituzione
         switch (*(++pszParms)) {
            case 'd':
            case 'D':
               pszOut = sstrcpy(pszOut, pam->pszTmpPath);
               break;
            case 'f':         // sostituisce path + file
            case 'F':
               pszOut = sstrcpy(pszOut, pam->fsp.pszPath);
               if (*(pszOut - 1) != '\\') *pszOut++ = '\\';
               pszOut = sstrcpy(pszOut, pam->fsp.pszFile);
               break;
            case 'i':        // sostituisce file da importare
            case 'I':
               pszOut = sstrcpy(pszOut, pszImp);
               break;
            case 'p':
            case 'P':
               pszOut = sstrcpy(pszOut, pam->fsp.pszPath);
               break;
            case '%':        // sostituisce segno percentuale
               *pszOut++ = '%';
               break;
            default :        // mostra msg errore
               sprintf(pszStart, "%s (%s) %s",
                       ERR_INV_PARMS, pam->fsp.pszFile, pszErr);
               PMPrint(hwnd, pszStart);
               return NULL;
               break;
         } /* endswitch */
         ++pszParms;
      } else {
         *pszOut++ = *pszParms++;
      } /* endif */
   } /* endwhile */
   *pszOut = 0;
   return pszStart;
}


//==========================================================================\
// subclassa una finestra memorizzando l'indice della procedura originale   |
// in QWL_USER                                                              |
//==========================================================================/

BOOL Subclass(HWND hwnd, USHORT usID, PFNWP newProc) {
   HWND hTmp = WinWindowFromID(hwnd, usID);
   return WinSetWindowPtr(hTmp, QWL_USER,
                          (PVOID)WinSubclassWindow(hTmp, newProc));
}


//==========================================================================\
// subclassa la listbox file                                                |
//==========================================================================/

BOOL SubclassFileList(HWND hwnd, PATTMAN pam, PFNWP newProc) {
   static LBOXFILE lbfile;
   HWND hTmp = WinWindowFromID(hwnd, LB_FILE);
   lbfile.pfnwp = WinSubclassWindow(hTmp, newProc);
   lbfile.pam = pam;
   return WinSetWindowPtr(hTmp, QWL_USER, (PVOID)&lbfile);
}


//==========================================================================\
// Terminate: libera anchor block e handle message queue                    |
//==========================================================================/

int Terminate(HAB hab, HMQ hmq, int rc) {
   WinDestroyMsgQueue(hmq);
   WinTerminate(hab);
   return rc;
}


//==========================================================================\
// i2fstr: converte un numero in una stringa formattata in cui le migliaia  |
//         sono separate dal carattere ch                                   |
//==========================================================================/

PSZ i2fstr(int i, PSZ psz, CHAR ch) {
   char swap = 0;
   PSZ s = psz;
   PSZ start = psz;
   int cnum = 0;

   if (i < 0) { swap = '-'; i *= -1; }
   do {
      if (cnum++ == 3) {
         cnum = 1;
         *s++ = ch;
      } /* endif */
      *s++ = i % 10 + '0'; } while (i /= 10);                    // convert
   if (swap) *s++ = swap;
   *s-- = 0;
   while (start < s) { swap = *start; *start++ = *s; *s-- = swap; } //reverse
   return psz;
}


//==========================================================================\
// registra i controlli 3D e quelli superclassati                           |
//==========================================================================/

BOOL RegisterCustomControls(HAB hab) {
   CLASSINFO ci;
   // registra statusbar e groupbox3D
   if (!RegisterStatusBarClass(hab) ||
       !RegisterGroupBox3DClass(hab))
      return FALSE;
   // superclassa statusbar
   if (!Superclass(hab, WC_STATUSBAR, "ACCHelpStatusBar", ACCHSBarWinProc,
                   &pfnwpSbar, FALSE) ||
       // superclassa bottoni
       !Superclass(hab, WC_BUTTON, "ACCHelpButton", ACCHBtnWinProc,
                   &pfnwpBtn, TRUE) ||
       // superclassa listbox
       !Superclass(hab, WC_LISTBOX, "ACCmenuLbox", ACCMLBoxWinProc,
                   &pfnwpLBox, TRUE) ||
       // superclassa finestre testo statico
       !Superclass(hab, WC_STATIC, "ACCmenuStatic", ACCMSTextWinProc,
                   &pfnwpSText, TRUE) ||
       // superclassa finestre MLE
       !Superclass(hab, WC_MLE, "ACCmenuMLE", ACCMMLEWinProc,
                   &pfnwpMle, TRUE))
      return FALSE;
   return TRUE;
}


//==========================================================================\
// crea una nuova classe di finestre da una preesistente:                   |
// parametri:                                                               |
// HAB hab = anchor block handle                                            |
// PSZ pszClass = nome classe originale                                     |
// PSZ pszNewClass = nome nuova classe                                      |
// PFNWP pfnwpNew = puntatore alla window procedure della nuova classe      |
// PFNWP pfnwpDefault = puntatore alla window procedure della classe origin.|
// BOOL flag = TRUE significa che la classe originale Š pubblica e che      |
//             biogna sottrarre lo stile CS_PUBLIC                          |
// valore restituito:                                                       |
// BOOL: TRUE = successo, FALSE = errore                                    |
//==========================================================================/

BOOL Superclass(HAB hab, PSZ pszClass, PSZ pszNewClass, PFNWP pfnwpNew,
               PFNWP *pfnwpDefault, BOOL flag) {
   CLASSINFO ci;
   if (!WinQueryClassInfo(hab, pszClass, &ci) ||
       !WinRegisterClass(hab, pszNewClass, pfnwpNew,
                         (flag? ci.flClassStyle & ~CS_PUBLIC: ci.flClassStyle),
                         ci.cbWindowData))
      return FALSE;
   *pfnwpDefault = ci.pfnWindowProc;
   return TRUE;
}


//==========================================================================\
// formatta la data secondo il formato tipico della nazionalit…             |
// PFDATE pfd = indirizzo struttura dati da formattare                      |
// PFFDATE pffd = indirizzo struttura dati formattata                       |
// ULONG ulFrm = tipo formattazione (1=d/m/y, 2 =y/m/d, 3=m,d,y)            |
//==========================================================================/

VOID FormatDate(PFDATE pfd, PFFDATE pffd, ULONG ulFrm) {
   pffd->d = pfd->year > 19? pfd->year - 20: pfd->year + 80;
   switch (ulFrm) {
      case 1:
         pffd->a = pfd->day;
         pffd->b = pfd->month;
         pffd->c = pffd->d;
         break;
      case 2:
         pffd->a = pffd->d;
         pffd->b = pfd->month;
         pffd->c = pfd->day;
         break;
      default: 
         pffd->a = pfd->month;
         pffd->b = pfd->day;
         pffd->c = pffd->d;
         break;
   } /* endswitch */
}
