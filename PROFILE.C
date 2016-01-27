//==========================================================================\
// profile.c : funzioni di lettura/scrittura file inizializzazione          |
//==========================================================================/

#define INCL_WIN
#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"
#include "preferences.h"

//========================[GetDefaultProfile()]=============================\
// crea il nome del file INI partendo dal nome dell'eseguibile              |
// void GetDefaultProfile(PSZ pszExe, PSZ pszProfile)                       |
// PSZ pszExe     = nome dell'eseguibile                                    |
// PSZ pszProfile = buffer in cui viene scritto il nome del file INI        |
//==========================================================================/

void GetDefaultProfile(PSZ pszExe, PSZ pszProfile) {
   char* ext = NULL;
   while (*pszExe) {
      if (*pszExe == '.')
         ext = pszProfile + 1;
      *pszProfile++ = *pszExe++;
   } /* endwhile */
   if (ext == NULL) {
      ext = pszProfile;
      *ext++ = '.';
   } // endif
   *ext++ = 'i'; *ext++ = 'n'; *ext++ = 'i'; *ext++ = 0;
}


//=============================[ParseProfile()]=============================\
// legge il file di inizializzazione                                        |
// VOID ParseProfile(HAB hab, PSZ pszProfile)                               |
// HAB hab        = anchor block handle                                     |
// PSZ pszProfile = nome file inizializzazione                              |
//==========================================================================/

BOOL ParseProfile(HAB hab, PSZ pszProfile, PAM_PRO ppro) {
   HINI hini;
   ULONG ulSize = sizeof(SWP);
   hini = PrfOpenProfile(hab, pszProfile);

   // posizione e dimensioni finestra principale
   if (!PrfQueryProfileData(hini, "pos", "main", (PVOID)&ppro->swp, &ulSize))
      WinQueryTaskSizePos(hab, 0, &ppro->swp);

   // posizione e dimensioni finestra mask selection
   ulSize = sizeof(POINTL);
   if (!PrfQueryProfileData(hini, "pos", "mask", (PVOID)&ppro->msk.pos, &ulSize)) {
      ppro->msk.pos.x = 0;
      ppro->msk.pos.y = 0;
   } // end if

   // posizione e dimensioni finestra preferenze
   ulSize = sizeof(POINTL);
   if (!PrfQueryProfileData(hini, "pos", "pref", (PVOID)&ppro->pos, &ulSize)) {
      ppro->pos.x = 0;
      ppro->pos.y = 0;
   } // end if

   // estensioni memorizzate per la mask selection
   ppro->msk.ulLen = PrfQueryProfileInt(hini, "mask", "len", 19);
   if ((ppro->msk.pszExt = (PSZ)malloc((size_t)ppro->msk.ulLen)) == NULL) {
      PMPrint(HWND_DESKTOP, ERR_ALLOC_MASK_BUFFER);
      return TRUE;
   } // end if
   if (!PrfQueryProfileData(hini, "mask", "ext",(PVOID)ppro->msk.pszExt,
                            &ppro->msk.ulLen)) {
      if (ppro->msk.ulLen == 19) {
         int i;
         PBYTE pbTmp = ppro->msk.pszExt;
         PBYTE pbNew = (PBYTE)"*.ARJ\0*.RAR\0*.ZIP\0";
         for (i = 0; i < ppro->msk.ulLen; i++)
              *(ppro->msk.pszExt + i) = *pbNew++;
      } else {
         PMPrint(HWND_DESKTOP, ERR_INIFILE_CORRUPTED);
         free(ppro->msk.pszExt); 
         return TRUE;
      } // end if
   } // end if

   // pagina 1: generale
   // logo: general->logo
   ppro->gen.nologo = PrfQueryProfileInt(hini, "gen", "nologo", FALSE);
   // abilitazione bubble help toolbar
   ppro->gen.bubble = PrfQueryProfileInt(hini, "gen", "bubble", TRUE);
   // lunghezza EA subject: general->subject length
   ppro->gen.subj = PrfQueryProfileInt(hini, "gen", "subj", -40);
   // readonly mode: general->readonly mode
   ppro->gen.ronly = PrfQueryProfileInt(hini, "gen", "ronly", FALSE);
   // ultimo path di lavoro : general->lastPath
   PrfQueryProfileString(hini, "gen", "path", "", ppro->gen.lastPath, 256);
   // font: general->font
   PrfQueryProfileString(hini, "gen", "font", "5.System VIO",
                         ppro->gen.font, 256);
   // larghezza listbox drive
   ppro->gen.cxDrv = PrfQueryProfileInt(hini, "gen", "cxdrv", 0);
   // larghezza listbox folder
   ppro->gen.cxFld = PrfQueryProfileInt(hini, "gen", "cxfld", 0);

   // pagina 2: selezione
   // selezione: selection->extended selection
   ppro->sel.extsel = PrfQueryProfileInt(hini, "sel", "extsel", TRUE);
   // directory drop: selection->select all files
   ppro->sel.dir = PrfQueryProfileInt(hini, "sel", "allfiles", FALSE);
   // single mouse click: selection->single mouse click (LN_ENTER/LN_SELECT)
   ppro->sel.monoclick = PrfQueryProfileInt(hini, "sel", "1clk", LN_ENTER);
   // browse mode: selection->browse mode
   ppro->sel.browse = PrfQueryProfileInt(hini, "sel", "browse", FALSE);
   // browse only if dir: selection->browse only if dir
   ppro->sel.browsedir = PrfQueryProfileInt(hini, "sel", "browsedir", FALSE);

   // pagina 3: import (1)
   // autoimport: import->enable auto
   ppro->imp.autoimp = PrfQueryProfileInt(hini, "imp", "autoimp", FALSE);
   // autoimport viewonly: import->view only
   ppro->imp.view = PrfQueryProfileInt(hini, "imp", "view", TRUE);
   // import to: import->import to
   ppro->imp.imp_to = PrfQueryProfileInt(hini, "imp", "imp_to", RADIO_TO_CMNT);
   // modalit… importazione defult: import->default mode
   ppro->imp.def_imp = PrfQueryProfileInt(hini, "imp", "def_imp",
                                          RADIO_IMP_AUTO);
   // nome file description: import->4 OS/2-DOS file
   PrfQueryProfileString(hini, "imp", "4OS2", "DESCRIPT.ION",
                         ppro->imp.quattro, 256);
   // file da importare userdef
   PrfQueryProfileString(hini, "imp", "file2imp", "", ppro->imp.ftoimp, 256);
   // nome programma userdef
   PrfQueryProfileString(hini, "imp", "xtrprg", "", ppro->imp.xtrprog, 256);
   // parametri programma userdef
   PrfQueryProfileString(hini, "imp", "xtrparms", "", ppro->imp.xtrparms, 256);

   // pagina 4: import (2)
   ppro->imp.unarc.ulItems = PrfQueryProfileInt(hini, "imp", "unarcItems", 1);
   ppro->imp.unarc.ulSize = PrfQueryProfileInt(hini, "imp", "unarcSize",
                            37 + 2 * sizeof(UNARC_ITEM));
   if ((ppro->imp.unarc.pui =
              (PUNARC_ITEM)malloc((size_t)ppro->imp.unarc.ulSize)) == NULL) {
      PMPrint(HWND_DESKTOP, ERR_ALLOC_UNARC_DBASE);
      free(ppro->msk.pszExt); // la libera
      return TRUE;
   } // end if
   if (!PrfQueryProfileData(hini, "imp", "unarc", (PVOID)ppro->imp.unarc.pui,
                          &ppro->imp.unarc.ulSize)) {
      // se non ci sono dati perch‚ Š la prima esecuzione del programma
      if (ppro->imp.unarc.ulSize == 37 + 2 * sizeof(UNARC_ITEM)) {
         int i;
         PBYTE pbTmp = (PBYTE)"*.zip\0unzip.exe\0file_id.diz\0-C %f %i";
         // imposta dati di default:
         ppro->imp.unarc.pui[0].ulExt = 0x20;
         ppro->imp.unarc.pui[0].ulProg = 0x26;
         ppro->imp.unarc.pui[0].ulImp = 0x30;
         ppro->imp.unarc.pui[0].ulParms = 0x3c;
         ppro->imp.unarc.pui[1].ulExt = ppro->imp.unarc.ulSize;
         ppro->imp.unarc.pui[1].ulProg = ppro->imp.unarc.ulSize;
         ppro->imp.unarc.pui[1].ulImp = ppro->imp.unarc.ulSize;
         ppro->imp.unarc.pui[1].ulParms = ppro->imp.unarc.ulSize;
         for (i = ppro->imp.unarc.pui->ulExt; i < ppro->imp.unarc.ulSize; i++)
            *((PBYTE)ppro->imp.unarc.pui + i) = *pbTmp++;
      } else {
         PMPrint(HWND_DESKTOP, ERR_INIFILE_CORRUPTED);
         free(ppro->msk.pszExt); // la libera
         return TRUE;
      } /* endif */
   } // end if

   // pagina 5 - 6 : report (1)
   // abilita auto report: report->enable auto
   ppro->rep.autorep = PrfQueryProfileInt(hini, "rep", "autorep", FALSE);
   // if arg is directory: report->only dir
   ppro->rep.repdir = PrfQueryProfileInt(hini, "rep", "repdir", FALSE);
   // view: show/hide/show only rep
   ppro->rep.view = PrfQueryProfileInt(hini, "rep", "view", RADIO_SHOW);
   // modalit… report: report->mode
   ppro->rep.repmode = PrfQueryProfileInt(hini, "rep", "mode", RADIO_SEL_FILES);
   // abilitazione formattazione report
   ppro->rep.formflag = PrfQueryProfileInt(hini, "rep", "form", FALSE);
   // programma formattazione report
   PrfQueryProfileString(hini, "rep", "formprg", "", ppro->rep.formprog, 256);
   // parametri programma formattazione report
   PrfQueryProfileString(hini, "rep", "formparms", "", ppro->rep.formparms, 256);
   // abilita salvataggio automatico report
   ppro->rep.autosave = PrfQueryProfileInt(hini, "rep", "save", FALSE);
   // nome file salvataggio automatico
   PrfQueryProfileString(hini, "rep", "savefile", "", ppro->rep.savefile, 256);

   // pagina 7: find
   // abilita programma di find
   ppro->find.flag = PrfQueryProfileInt(hini, "find", "flag", FALSE);
   // programma di ricerca
   PrfQueryProfileString(hini, "find", "prg", "", ppro->find.prog, 256);
   // Parametri programma di ricerca
   PrfQueryProfileString(hini, "find", "parms", "", ppro->find.parms, 256);
   PrfCloseProfile(hini);
   return FALSE;
}


//============================[WriteSettings()]=============================\
// scrive nel file di inizializzazione le nuove impostazioni                |
// parametri:                                                               |
// HWND hwnd     = handle finestra                                          |
// PAM_PRO ppref = puntatore struttura impostazioni                         |
//==========================================================================/

VOID WriteAMSettings(HWND hwnd, PSZ pszProfile, PAM_PRO ppref) {
   HAB hab;
   HINI hini;
   SWP swpCurr;
   char buf[8];
   char * bool[] = {"0", "1"};

   hab = WinQueryAnchorBlock(hwnd);
   hini = PrfOpenProfile(hab, pszProfile);
   // posizione finestra (le dimensioni vengono aggiornate dinamicamente)
   WinQueryWindowPos(hwnd, &swpCurr);
   ppref->swp.x = swpCurr.x;
   ppref->swp.y = swpCurr.y;
   PrfWriteProfileData(hini, "pos", "main", (PVOID)&ppref->swp, sizeof(SWP));
   
   // posizione finestra mask selection
   PrfWriteProfileData(hini, "pos", "mask", (PVOID)&ppref->msk.pos, sizeof(POINTL));
   
   // posizione finestra preferenze
   PrfWriteProfileData(hini, "pos", "pref", (PVOID)&ppref->pos, sizeof(POINTL));
   
   // estensioni memorizzate per la mask selection
   PrfWriteProfileString(hini, "mask", "len", i2str(ppref->msk.ulLen, buf));
   PrfWriteProfileData(hini, "mask", "ext",(PVOID)ppref->msk.pszExt,
                       ppref->msk.ulLen);
   free(ppref->msk.pszExt);
   
   // pagina 1: generale
   // logo: general->logo
   PrfWriteProfileString(hini, "gen", "nologo", bool[ppref->gen.nologo!= 0]);
   // bubble help toolbar
   PrfWriteProfileString(hini, "gen", "bubble", bool[ppref->gen.bubble!= 0]);
   // lunghezza EA subject: general->subject length
   PrfWriteProfileString(hini, "gen", "subj", i2str(ppref->gen.subj, buf));
   // readonly mode: general->readonly mode
   PrfWriteProfileString(hini, "gen", "ronly", bool[ppref->gen.ronly!= 0]);
   // ultimo path di lavoro : general->lastPath
   if (*ppref->gen.lastPath)
      QueryCurrentPath(ppref->gen.lastPath, NULL);
   PrfWriteProfileString(hini, "gen", "path", ppref->gen.lastPath);
   // font: general->font
   PrfWriteProfileString(hini, "gen", "font", ppref->gen.font);
   // larghezza listbox drive
   PrfWriteProfileString(hini, "gen", "cxdrv", i2str(ppref->gen.cxDrv, buf));
   // larghezza listboz folder
   PrfWriteProfileString(hini, "gen", "cxfld", i2str(ppref->gen.cxFld, buf));

   // pagina 2: selezione
   // selezione: selection->extended selection
   PrfWriteProfileString(hini, "sel", "extsel", bool[ppref->sel.extsel!= 0]);
   // directory drop: selection->select all files
   PrfWriteProfileString(hini, "sel", "allfiles", bool[ppref->sel.dir!= 0]);
   // single mouse click: selection->single mouse click (LN_ENTER/LN_SELECT)
   PrfWriteProfileString(hini, "sel", "1clk", i2str(ppref->sel.monoclick, buf));
   // browse mode: selection->browse mode
   PrfWriteProfileString(hini, "sel", "browse", bool[ppref->sel.browse!= 0]);
   // browse only if dir: selection->browse only if dir
   PrfWriteProfileString(hini, "sel", "browsedir", bool[ppref->sel.browsedir!= 0]);

   // pagina 3: import (1)
   // autoimport: import->enable auto
   PrfWriteProfileString(hini, "imp", "autoimp", bool[ppref->imp.autoimp!= 0]);
   // autoimport viewonly: import->view only
   PrfWriteProfileString(hini, "imp", "view", bool[ppref->imp.view!= 0]);
   // import to: import->import to
   PrfWriteProfileString(hini, "imp", "imp_to", i2str(ppref->imp.imp_to, buf));
   // modalit… importazione defult: import->default mode
   PrfWriteProfileString(hini, "imp", "def_imp", i2str(ppref->imp.def_imp, buf));
   // nome file description: import->4 OS/2-DOS file
   PrfWriteProfileString(hini, "imp", "4OS2", ppref->imp.quattro);
   // file da importare userdef
   PrfWriteProfileString(hini, "imp", "file2imp", ppref->imp.ftoimp);
   // nome programma userdef
   PrfWriteProfileString(hini, "imp", "xtrprg", ppref->imp.xtrprog);
   // parametri programma userdef
   PrfWriteProfileString(hini, "imp", "xtrparms", ppref->imp.xtrparms);

   // pagina 4: import (2)
   // struttura UNARCDATA
   PrfWriteProfileString(hini, "imp", "unarcItems", i2str(ppref->imp.unarc.ulItems, buf));
   PrfWriteProfileString(hini, "imp", "unarcSize", i2str(ppref->imp.unarc.ulSize, buf));
   PrfWriteProfileData(hini, "imp", "unarc", (PVOID)ppref->imp.unarc.pui,
                       ppref->imp.unarc.ulSize);
   free(ppref->imp.unarc.pui);

   // pagina 5 - 6: report (1)
   // abilita auto report: report->enable auto
   PrfWriteProfileString(hini, "rep", "autorep", bool[ppref->rep.autorep!= 0]);
   // if arg is directory: report->only dir
   PrfWriteProfileString(hini, "rep", "repdir", bool[ppref->rep.repdir!= 0]);
   // view: show/hide/show only rep
   PrfWriteProfileString(hini, "rep", "view", i2str(ppref->rep.view, buf));
   // modalit… report: report->mode
   PrfWriteProfileString(hini, "rep", "mode", i2str(ppref->rep.repmode, buf));
   // abilitazione formattazione report
   PrfWriteProfileString(hini, "rep", "form", bool[ppref->rep.formflag]);
   // programma formattazione report
   PrfWriteProfileString(hini, "rep", "formprg", ppref->rep.formprog);
   // parametri programma formattazione report
   PrfWriteProfileString(hini, "rep", "formparms", ppref->rep.formparms);
   // abilita salvataggio automatico report
   PrfWriteProfileString(hini, "rep", "save", i2str(ppref->rep.autosave, buf));
   // nome file salvataggio automatico
   PrfWriteProfileString(hini, "rep", "savefile", ppref->rep.savefile);

   // pagina 7: find
   // abilita programma di find
   PrfWriteProfileString(hini, "find", "flag", bool[ppref->find.flag!= 0]);
   // programma di ricerca
   PrfWriteProfileString(hini, "find", "prg", ppref->find.prog);
   // Parametri programma di ricerca
   PrfWriteProfileString(hini, "find", "parms", ppref->find.parms);
   PrfCloseProfile(hini);
}
