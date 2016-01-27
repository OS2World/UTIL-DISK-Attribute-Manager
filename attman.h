//==========================================================================\
// attman.h : header principale definizioni strutture, variabili globali    |
// e funzioni                                                               |
//==========================================================================/
#ifndef __ATTMAN_STRUCTS__

   #define __ATTMAN_STRUCTS__

   #ifndef INCL_WIN
      #define INCL_WIN
   #endif

   #ifndef INCL_WINSTDDRAG
      #define INCL_WINSTDDRAG
   #endif

   #ifndef __OS2_H__
      #include <os2.h>
   #endif
   
   #define ALL_DIR MUST_HAVE_DIRECTORY | FILE_READONLY | FILE_HIDDEN |\
                   FILE_SYSTEM | FILE_ARCHIVED | FILE_DIRECTORY
   #define ANYFILE FILE_READONLY | FILE_HIDDEN |\
                   FILE_SYSTEM | FILE_ARCHIVED | FILE_DIRECTORY
   #define LPATH CCHMAXPATH
   #define LFILE
   #define LPARM

   // variabili globali
   extern PFNWP pfnwpSbar, pfnwpBtn, pfnwpLBox, pfnwpSText, pfnwpMle;

   // struttura usata x formattare la data secondo nazionalit…
   #pragma pack(1)
   typedef struct {
      UCHAR a;
      UCHAR b;
      UCHAR c;
      UCHAR d;
   } FFDATE, * PFFDATE;

   // struttura mask selection
   typedef struct _MASKSEL {
      USHORT usSize;         // dimensione struttura
      ULONG ulLen;           // lunghezza dati puntati da pszExt
      PSZ pszExt;            // indirizzo prima voce memorizzata
      POINTL pos;            // posizione finestra
      CHAR achSel[64];       // specifiche file prescelto
   } MASKSEL, * PMASKSEL;

   typedef struct _UNARC_ITEM {  // offset relativo a UNARCDATA.pui
      ULONG ulExt;           // offset all'estensione
      ULONG ulProg;          // offset nome programma
      ULONG ulImp;           // offset nome file da importare
      ULONG ulParms;         // offset stringa parametri
   } UNARC_ITEM, * PUNARC_ITEM;

   typedef struct _UNARCDATA {  // Š sempre presente un item fittizio
      ULONG ulItems;         // numero items UNARC_ITEM
      ULONG ulSize;          // memoria da allocare per i dati UNARC_ITEM
      PUNARC_ITEM pui;       // puntatore inizio array strutture UNARC_ITEM
   } UNARCDATA, * PUNARCDATA;

   // struttura variabili blocco impostazioni pagina 1 (general)
   typedef struct _PREF_GEN {
      USHORT usSize;         // dimensione della struttura
      BOOL nologo;           // se TRUE il logo NON viene visualizzato
      BOOL bubble;           // se TRUE mostra bubble help toolbar
      LONG subj;             // lunghezza campo subject (< 0 = default)
      BOOL ronly;            // se TRUE non si possono editare gli attributi
      CHAR lastPath[256];    // se = "" non salva ultimo path
      CHAR font[256];        // font utilizzato in tutte le finestre
      ULONG cxFont;          // larghezza massima font
      ULONG cyFont;          // altezza massima font
      ULONG cyItem;          // altezza item listbox folder
      LONG clrBack;          // colore background listbox
      LONG clrFore;          // colore foreground listbox
      LONG clrHiBack;        // colore hilite background listbox
      LONG clrHiFore;        // colore hilite foreground listbox
      PSWP pswp;             // puntatore array swp controlli fin princ
      ULONG cxDrv;           // larghezza lbox drive
      ULONG cxFld;           // larghezza lbox folder
   } PREF_GEN, * PPREF_GEN;
   
   // struttura variabili blocco impostazioni pagina 2 (selection)
   typedef struct _PREF_SEL {
      USHORT usSize;         // dimensione della struttura
      BOOL extsel;           // TRUE abilit… modalit… selezione estesa
      BOOL dir;              // TRUE seleziona tutti i file nella dir
      BOOL monoclick;        // TRUE abilita selezione con singolo click
      BOOL browse;           // TRUE visualizza finestra browsing drv/dir/file
      BOOL browsedir;        // TRUE abilita finestra browsing se arg = dir
   } PREF_SEL, * PPREF_SEL;
   
   // struttura variabili blocco impostazioni pagina 3, 4 e 5 (import)
   typedef struct _PREF_IMPORT {
      USHORT usSize;       // dimensione della struttura
      BOOL autoimp;        // TRUE importa automaticamente commento se mancant
      BOOL view;           // TRUE commento visualizzato ma non salvato in EAs
      ULONG imp_to;        // target auto import (subj/comment/auto)
      ULONG def_imp;       // default import-file (file_id.diz/4DOS/user/other)
      CHAR quattro[256];   // nome decript.ion file
      CHAR ftoimp[256];    // nome file da importare
      CHAR xtrprog[256];   // programma estrazione descrizione
      CHAR xtrparms[256];  // parametri programma estrazione descrizione
      UNARCDATA unarc;     // UNARCDATA
   } PREF_IMPORT, * PPREF_IMPORT;
   
   // struttura variabili blocco impostazioni pagina 6 e 7 (report)
   typedef struct _PREF_REPORT {
      USHORT usSize;       // dimensione della struttura
      BOOL autorep;        // TRUE mostra report x ogni nuovo file/dir
      BOOL repdir;         // TRUE mostra report solo se arg = dir
      ULONG view;          // show/hide/show_only_report
      ULONG repmode;       // modalit… report (selected files/all files/tree)
      BOOL formflag;       // TRUE formattazione abilitata
      CHAR formprog[256];  // programma formattazione report
      CHAR formparms[256]; // parametri programma formattazione
      BOOL autosave;       // TRUE slava report con nome file indicato
      CHAR savefile[256];  // nome file salvataggio automatico
   } PREF_REPORT, * PPREF_REPORT;

   // struttura variabili blocco impostazioni pagina 8
   typedef struct _PREF_FIND {
      USHORT usSize;         // dimensione della struttura
      BOOL flag;
      CHAR prog[256];
      CHAR parms[256];
   } PREF_FIND, * PPREF_FIND;
   
   // struttura usate per memorizzare le preferenze nel programma e nel profile
   typedef struct _AM_PRO {
      USHORT usSize;         // dimensione della struttura
      ULONG ulVer;           // versione OS/2
      HWND hPref;            // handle dialogo preferenze
      SWP swp;               // posizione-dimensione finestra principale
      POINTL pos;            // posizione finestra preferenze
      PREF_GEN gen;          // pagina preferenze generali
      PREF_SEL sel;          // pagina preferenze selezione
      PREF_IMPORT imp;       // pagina preferenze modalit… importazione
      PREF_REPORT rep;       // pagina preferenze modalit… report
      PREF_FIND find;        // pagina programma find
      MASKSEL msk;           // struttura masksel
   } AM_PRO, * PAM_PRO;
   
   // struttura usata per memorizzare dati file (path, nome file, attrib. ord.)
   typedef struct _FILESPECS {
      CHAR pszFile[256];     // dati completi file corrente
      CHAR pszPath[256];     // path completo file corrente (= sopra se dir)
      FILESTATUS4 fs;        // dati file corrente
      FILESTATUS3 fsNew;     // dati file corrente modificati (data/ora e attr)
      USHORT currDir;        // valore handle item della dir corrente
      INT subjChanged;       // flag cambiamento entryfield subject
      CHAR subjUndo[256];    // buffer x UNDO entryfield subject
      CHAR subjCurr[256];    // buffer corrente contenuto subj
      PSHORT psSel;          // array indici file selezionati
      SHORT sPrvDrv;         // precedente drive selezionato
      SHORT sPrvDir;         // precedente dir selezionata
      BOOL hpfs;             // TRUE = drive corrente HPFS
      CHAR chD;              // separatore data
      CHAR chT;              // separatore ora
      CHAR milSep;           // separatore migliaia
      ULONG dtFrm;           // formato data
   } FILESPECS, * PFILESPECS;

   // struttura di variabili usate dal programma
   typedef struct _ATTMAN {
      USHORT cbSize;         // dimensione della struttura
      AM_PRO pro;            // impostazioni programma
      HPOINTER hIco;         // icona applicazione
      HPOINTER hClose;       // icona cartella chiusa
      HPOINTER hOpen;        // icona cartella aperta
      HWND hMMain;           // icona menu principale
      HWND hMEdit;           // icona menu editazione
      HAPP hSt[4]; // array handle applicazioni WinStartApp
      SHORT cyNoBrowse;      // cy modalit… no browse
      POINTS min;            // dimensioni minime finestra
      CHAR pszProfile[256];  // path completo file INI
      CHAR pszTmpPath[256];  // path creazione file temporanei
      FILESPECS fsp;         // struttura dati file
      int LMsel;             // TRUE quando la selezione viene da un msg
      SHORT sMenuFrom;       // sorgente WM_CONTEXTMENU o comando import
      HWND hCtlHelp;         // handle finestra generatrice WM_BUBBLEHELP
      int szCtl;             // flag x il ridimensionamento listbox
   } ATTMAN, * PATTMAN;

   typedef struct _LBOXFILE {
      PFNWP pfnwp;
      PATTMAN pam;
   } LBOXFILE, * PLBOXFILE;

   // struttura per dialogo Edit date time
   typedef struct {
      USHORT usSize;         // dimensione struttura
      ULONG ulVer;           // versione S.O.
      PFTIME pft;            // ora file
      PFDATE pfd;            // data file
      ULONG style;           // stile: gg/mm/yy - mm/gg/yy - yy/mm/gg
      POINTS pts;            // posizione visualizzazione dialogo
      PSZ pszTitle;          // titolo finestra
   } EDITDATETIME, *PEDITDATETIME;

   typedef PSZ* PPSZ;
//   #define DEBUGGING
   #ifdef DEBUGGING
      #include "debug.h"
   #else
      #define dprintf  ;
   #endif

#endif
