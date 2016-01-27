// definitions.h : definizioni di costanti e macro
#ifndef __ATTMAN_DEFINITIONS_
   #define __ATTMAN_DEFINITIONS_

   #ifndef __OS2_H__
      #define INCL_WIN
      #include <os2.h>
   #endif


//=========================================================================\
//                         PROTEZIONE SCADENZA                             |
//                data di scadenza 31 12 1998 (1998 12 31)                 |
// #define EXPIRE_DATE     19981231 * 3 - 99999
//=========================================================================/

   // id timer x help contestuale
   #define TID_CONTEXTHELP  1

   // formato data
   #define MM_DD_YY       0
   #define DD_MM_YY       1
   #define YY_MM_DD       2

   // FLAG usate come valori di ritorno da WinDismissDlg nel dialogo 4
   #define UPDT_A         0x0001
   #define UPDT_H         0x0002
   #define UPDT_R         0x0004
   #define UPDT_S         0x0008
   #define UPDT_SUBJ      0x0010
   #define UPDT_KEY       0x0020
   #define UPDT_CMNT      0x0040
   #define UPDT_CHTIME    0x0080
   #define UPDT_CHDATE    0x0100
   #define UPDT_CRTIME    0x0200
   #define UPDT_CRDATE    0x0400
   #define UPDT_ACTIME    0x0800   
   #define UPDT_ACDATE    0x1000
   #define UPDT_ORDATTR   UPDT_A + UPDT_H + UPDT_R + UPDT_S + UPDT_CHTIME +\
                          UPDT_CHDATE + UPDT_CRTIME + UPDT_CRDATE +\
                          UPDT_ACTIME + UPDT_ACDATE

   // loop eterno
   #define forever for(;;)

   // seleziona un item
   #define MyDlgLboxSelectItem(hDlg, LboxID, item)\
           {pam->LMsel = TRUE;\
           ((BOOL)WinSendDlgItemMsg(hDlg, (LboxID), LM_SELECTITEM,\
                                    MPFROMLONG(item), MPFROMLONG(TRUE)));\
           pam->LMsel = FALSE;}
   
   // deseleziona un item
   #define MyDlgLboxDeselectItem(hDlg, LboxID, item)\
           {pam->LMsel = TRUE;\
           ((BOOL)WinSendDlgItemMsg(hDlg, (LboxID), LM_SELECTITEM,\
                                    MPFROMLONG(item), MPFROMLONG(FALSE)));\
           pam->LMsel = FALSE;}

   // cancella tutti gli item
   #define MyDlgLboxDeleteAll(hwndDlg, LboxID)\
           {pam->LMsel = TRUE;\
           ((LONG)WinSendDlgItemMsg(hwndDlg, (LboxID), LM_DELETEALL,\
                                    NULL, NULL));\
           pam->LMsel = FALSE;}

   // mostra-nasconde un controllo di un dialogo
   #define DlgShowCtl(hwnd, ID, flag) \
           (WinShowWindow(WinWindowFromID(hwnd, (ID)), (flag)))
   // riporta la posizione di un controllo in un dialogo
   #define DlgQueryCtlPos(hwnd, ID, pswp) \
           (WinQueryWindowPos(WinWindowFromID(hwnd, (ID)), (pswp)))
   // riposiziona un controllo
   #define DlgSetCtlPos(hwnd, ID, f1, x, y, cx, cy, f2) \
           (WinSetWindowPos(WinWindowFromID(hwnd, (ID)), (f1), (x), (y), \
                                            (cx), (cy), (f2)))
   // settaggio stili controllo
   #define DlgSetCtlBits(hwnd, ID, f1, f2, f3) \
           (WinSetWindowBits(WinWindowFromID(hwnd, (ID)), (f1), (f2), (f3)))
   // richiesta dati USHORT controllo
   #define DlgQueryCtlUShort(hwnd, ID, f1) \
           (WinQueryWindowUShort(WinWindowFromID(hwnd, (ID)), (f1)))

   // per scrivere messaggi errore
   #define PMPrint(hwnd, psz)  WinMessageBox(HWND_DESKTOP, hwnd,\
                               (psz), NULL, 0, MB_OK | MB_ERROR | MB_MOVEABLE)

   // indici array handle applicazioni avviate da WinStartApp
   #define WSTART_IMP_FID       0      // imp file_id.diz
   #define WSTART_UDEF          1      // imp userdef extract
   #define WSTART_REPORT        2      // report format
   #define WSTART_FIND          3      // find program
   #define WSTART_SIZE          4      // elementi array

   //-----------------------------------------------------------------------\
   //                               MESSAGGI                                |
   //-----------------------------------------------------------------------/

   // messaggio per l'aggiornamento delle impostazioni
   #define WM_UPD_SETTINGS         WM_USER
   // messaggio per recuperare l'indirizzo della window procedure originale MLE
   #define WM_BUBBLEHELP           WM_USER + 1
   // usato per trasmettere l'handle della main window al dialogo preferenze
   #define WM_SEND_MAINHWND        WM_USER + 2
   // usato per notificare chiusura blocco impostazioni alle pagine
   #define WM_CLOSE_PREFERENCES    WM_USER + 3
   // usato per comunicare tra i processi avviati da WinStartApp
   #define WM_PROC_READY           WM_USER + 4
   // usato per indicare WM_CONTEXTMENU, in mp1 c'Š l'ID del controllo
   // in mp2 l'handle
   #define WM_POPUPMENU            WM_USER + 5
   // messaggio trasmesso alla frame quando viene rilevato WM_BUTTON1UP
   // in una listbox, allo scopo di implementare il singleclick
   // in mp1 c'Š l'ID del controllo, in mp2 l'handle
   #define WM_LBOXBTN1UP           WM_USER + 6

   // mandati in risposta ai msg  DM_* sulla barra del titolo
   #define TTL_DRAGOVER            WM_USER + 10
   #define TTL_DRAGLEAVE           WM_USER + 11
   #define TTL_DROP                WM_USER + 12

#endif                              
