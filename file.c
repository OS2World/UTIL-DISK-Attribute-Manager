//==========================================================================\
// file.c : funzioni relative ai file                                       |
// VOID ProcessFileSelection(HWND hwnd, PATTMAN pam);                       |
// BOOL isChanged(HWND hwnd, PATTMAN pam);                                  |
// VOID SetWinTitle(HWND hwnd, PATTMAN pam);                                |
// VOID DeselectAllFiles(HWND hwnd, PATTMAN pam);                           |
// VOID UpdateSelFilesArray(HWND hwnd, PATTMAN pam);                        |
//==========================================================================/

#define INCL_WIN
#include <os2.h>
#include <listbox.h>
#include <stdio.h>
#include <stdlib.h>
#include <mledlg.h>
#include <efdlg.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"

//==========================================================================\
// imposta il titolo della finestra e chiama GetAttr() con gli opportuni    |
// argomenti                                                                |
//==========================================================================/

VOID ProcessFileSelection(HWND hwnd, PATTMAN pam) {
   int idx;
   idx = DlgLboxQuerySelectedItem(hwnd, LB_FILE);
   // se il primo file selezionato non Š uguale al primo precedente
   if (idx != pam->fsp.psSel[1]) {      // aggiorna dati file
      // se prima esecuzione o attrib immutati o salvati:
      if (pam->fsp.psSel[0] < 0 || !isChanged(hwnd, pam)) {
         dprintf("Lettura attributi file");
         UpdateSelFilesArray(hwnd, pam);    // aggiorna array file selezionati
         SetWinTitle(hwnd, pam);            // aggiorna titolo finestra
         if (GetAttr(hwnd, &pam->fsp) == 0 && pam->pro.imp.autoimp) {
            pam->sMenuFrom = LB_FILE; // indica che viene da selezione file
            ImportFileData(hwnd, pam);
         } // end if
      } else { // Š stato premuto cancel x cui ripristina file preced selez
         dprintf("Ripristino precedente selezione (%d files)\n", pam->fsp.psSel[0]);
         DeselectAllFiles(hwnd, pam);   // cancella nuova selezione
         for (idx = 1; idx <= pam->fsp.psSel[0]; idx++)
            MyDlgLboxSelectItem(hwnd, LB_FILE, pam->fsp.psSel[idx]);
      } /* endif */
   } else {
      UpdateSelFilesArray(hwnd, pam);    // aggiorna array file selezionati
      SetWinTitle(hwnd, pam);            // aggiorna titolo finestra
   } // end if
}


//==========================================================================\
//  BOOL isChanged(HWND hwnd)             mostra un dialogo con i pulsanti  |
//  Save - Discard - Cancel. Salva il file e ritorna FALSE se si preme Save |
// ritorna FALSE se si preme discard e ritorna TRUE se si preme Cancel o si |
// chiude il dialogo                                                        |
//==========================================================================/

BOOL isChanged(HWND hwnd, PATTMAN pam) {
   if (pam->pro.gen.ronly) return FALSE; // se read only restituisce FALSE
   if (DlgMleQueryChanged(hwnd, MLE_KEY) ||
       DlgMleQueryChanged(hwnd, MLE_COMNT) ||
       pam->fsp.subjChanged > 0 ||
       isOrdAttrChanged(hwnd, &pam->fsp)) {  
      WinAlarm(HWND_DESKTOP, WA_NOTE); 
      switch (WinDlgBox(HWND_DESKTOP, hwnd, NULL,
              NULLHANDLE, SAVE_DLG, NULL)) {
         case BTN_2_SAVE :
            WriteNewAttr(hwnd, pam);
            return FALSE;
         case BTN_2_DISCARD :
            pam->fsp.subjChanged = -1;
            return FALSE;
         default :
            return TRUE;
      } // end switch
   } // end if
   return FALSE;
}


//==========================================================================\
// SetWinTitle: imposta il titolo della finestra secondo i file selezionati |
//==========================================================================/

VOID SetWinTitle(HWND hwnd, PATTMAN pam) {
   CHAR buf[LPATH + 32];

   dprintf("Settaggio titolo finestra\n");
   DlgLboxQueryItemText(hwnd, LB_FILE, pam->fsp.psSel[1], buf, LPATH + 32);
   // se Š una dir ed Š attiva opzione Selez All files in directory legge
   // attr primo file selezionato e titolo = nomedir\*.*
   if (pam->pro.sel.extsel && pam->pro.sel.dir &&
       pam->fsp.pszFile[0] == '\\' && pam->fsp.psSel[0]) {
      sstrcpy(pam->fsp.pszFile, buf); //copia in pszFile nome Iø file selez
      sprintf(buf, "%s%s%s & *.*", pam->fsp.pszPath,
              (pam->fsp.pszPath[3]? "\\": ""), pam->fsp.pszFile);
   // se Š una dir con opzione SelectAll non attiva o non ci sono file selez
   // legge attr dir corrente e titolo = nomedir\.
   } else if (pam->fsp.pszFile[0] == '\\' || !pam->fsp.psSel[0]) {
      if (!pam->fsp.psSel[0]) MyDlgLboxSelectItem(hwnd, LB_FILE, 0);
      pam->fsp.pszFile[0] = '.'; pam->fsp.pszFile[1] = 0;
      sstrcpy(buf, pam->fsp.pszPath);
      sstrcat(buf, pam->fsp.pszPath[3]? "\\.": ".");
   // se Š un file specificato con una mask di wildchar e ci sono + file
   // selez legge attr primo file e titolo = nomefile & mask
   } else if (isWildCh(pam->fsp.pszFile) && pam->fsp.psSel[0] > 1) {
      char tmp[256];
      sstrcpy(tmp, buf);
      sprintf(buf, "%s%s%s & %s", pam->fsp.pszPath,
              (pam->fsp.pszPath[3]? "\\": ""), tmp, pam->fsp.pszFile);
      sstrcpy(pam->fsp.pszFile, tmp);
   // pi— file selezionati non secondo una mask di wildchars
   } else if (pam->fsp.psSel[0] > 1) {
      sstrcpy(pam->fsp.pszFile, buf);
      sprintf(buf, "%s%s%s & ...", pam->fsp.pszPath,
              (pam->fsp.pszPath[3]? "\\": ""), pam->fsp.pszFile);
   // un solo file selezionato
   } else {
      sstrcpy(pam->fsp.pszFile, buf);
      sprintf(buf, "%s%s%s", pam->fsp.pszPath,
              (pam->fsp.pszPath[3]? "\\": ""), pam->fsp.pszFile);
   } // endif   ---  se Š autoimport e subject e comment sono vuoti
   WinSetWindowText(hwnd, buf);
}


//==========================================================================\
// Deseleziona tutti i file                                                 |
//==========================================================================/

VOID DeselectAllFiles(HWND hwnd, PATTMAN pam) {
   SHORT idx;
   for (idx = DlgLboxQuerySelectedItem(hwnd, LB_FILE);
        idx != LIT_NONE;
        idx = DlgLboxQueryNextSelItem(hwnd, LB_FILE, idx))
      MyDlgLboxDeselectItem(hwnd, LB_FILE, idx);
}


//==========================================================================\
// aggiorna l'array dei file selezionati                                    |
// allocazione minima 4KB se necessario alloca ulteriore memoria            |
//==========================================================================/

VOID UpdateSelFilesArray(HWND hwnd, PATTMAN pam) {
   int i, count, space;
   dprintf("UpdateSelFilesArray!!!\n");
   if (pam->fsp.psSel[0] >= 2000) { // precedente allocazione > minimo
      dprintf("Nuova allocazione\n");
      free(pam->fsp.psSel);
      if ((pam->fsp.psSel = malloc((size_t)4000)) == NULL) {
         PMPrint(hwnd, ERR_ALLOC_SELFILES);
         ProcessTermination(hwnd, FALSE);
         return;
      } /* endif */
   } /* endif */
   count = 1;      // numero items selezionati
   space = 4000;   // memoria allocata   --- primo item selezionato
   i = DlgLboxQuerySelectedItem(hwnd, LB_FILE);
   forever {
      dprintf("loop memorizzazione file selezionati: i = %d, count = %d\n", i, count);
      pam->fsp.psSel[count] = i;
      i = DlgLboxQueryNextSelItem(hwnd, LB_FILE, i);
      if (i == LIT_NONE) break;
      if (++count >= space / 2) {    // se serve > memoria:
         space += 4000;           // prova ad allocare altri 4KB
         if ((pam->fsp.psSel = realloc(pam->fsp.psSel, space)) == NULL) {
            PMPrint(hwnd, ERR_ALLOC_SELFILES);
            ProcessTermination(hwnd, FALSE);
            return;
         } /* endif */
      } /* endif */
   } /* endwhile */
   // abilita disabilita pulsanti per la selezione file precedente/successivo
   pam->fsp.psSel[0] = count;
   WinEnableControl(hwnd, BTN_UP, pam->fsp.psSel[1]);
   WinEnableControl(hwnd, BTN_DOWN, pam->fsp.psSel[count] !=
                    DlgLboxQueryItemCount(hwnd, LB_FILE) - 1);
}
