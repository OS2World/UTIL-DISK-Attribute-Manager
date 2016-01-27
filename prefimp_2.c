//==========================================================================\
// prefimp_2.c : funzioni dialoghi settaggio preferenze pagina import 2     |
//==========================================================================/

#define INCL_WIN
#include <os2.h>
#include <stdlib.h>
#include <efdlg.h>
#include <listbox.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "messages.h"
#include "preferences.h"
#include "prefmessages.h"

//==========================================================================\
// procedura dialogo quarta pagina : Import (2)                             |
//==========================================================================/

MRESULT EXPENTRY Imp2DlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2) {
   static PPREF_IMPORT pimp;
   static UNARCDATA unarcNew;     // struttura nuovi dati unarc
   static BOOL updated = FALSE;   // TRUE se Š stato modificato qualche dato

   switch (msg) {
      case WM_INITDLG:
         pimp = (PPREF_IMPORT)PVOIDFROMMP(mp2);
         InitImport2Page(hwnd, pimp, &unarcNew, TRUE);
         break;
      case WM_CONTROL:
         ProcPrefImp2WMCtl(hwnd, mp1, &unarcNew);
         break;
      case WM_COMMAND:
         switch (LOUSHORT(mp1)) {
            case BTN_REPLACE:
               updated |= ReplaceUnarcItem(hwnd, &unarcNew);
               break;
            case BTN_ADD:
               updated |= AddUnarcItem(hwnd, &unarcNew);
               break;
            case BTN_REMOVE:
               updated |= RemUnarcItem(hwnd, &unarcNew);
               break;
            case BTTN_UNDO:
               if(updated) {
                  updated = FALSE;
                  DlgLboxDeleteAll(hwnd, LB_ATYPE);
                  CleanUnarcEntries(hwnd);
                  free(unarcNew.pui);
                  WinEnableControl(hwnd, BTN_REMOVE, FALSE);
                  InitImport2Page(hwnd, pimp, &unarcNew, FALSE);
               } // end if
               break;
            case BTTN_DEFAULT:
               updated |= SetImport2Default(hwnd, &unarcNew);
               break;  
            default:
               break;
         } /* endswitch */
         break;
      case WM_CLOSE_PREFERENCES:
         // se la struttura Š stata aggiornata libera precedente struttura
         // e la aggiorna facendo puntare pimp->unarc->pui alla nuova
         if (updated) {
            free(pimp->unarc.pui);
            pimp->unarc = unarcNew;
         } else {
            if (unarcNew.pui != NULL) free(unarcNew.pui);
         } /* endif */
         break;
      default: 
         return WinDefDlgProc(hwnd, msg, mp1, mp2);
         break;
   } /* endswitch */
   return (MRESULT) FALSE;
}


//==========================================================================\
// setta i controlli secondo i valori delle impostazioni correnti in        |
// all'inizializzazione del dialogo o della pressione di UNDO (pagina 3)    |
// parametri:                                                               |
// HWND hwnd         = handle del dialogo                                   |
// PPREF_IMPORT pimp = puntatore alla struttura delle impostazioni pag imp1 |
// PUNARCDATA punarcNew = puntatore a struttura nuovi dati prg unarc        |
// BOOL flag = TRUE: inizializzazione, FALSE = undo                         |
//==========================================================================/

VOID InitImport2Page(HWND hwnd, PPREF_IMPORT pimp, PUNARCDATA punarcNew,
                     BOOL flag) {
   int i;
   PBYTE pbTemp, pbRef;

   *punarcNew = pimp->unarc;
   // copia i dati PUNARC in memoria per eventuale successivo Undo
   if ((punarcNew->pui = (PUNARC_ITEM)malloc((size_t)pimp->unarc.ulSize))
       == NULL) {  // in caso di fallita allocazione visualizza msg errore
      PMPrint(hwnd, ERR_ALLOC_UNARC_DBASE);
      EnableImp2Entries(hwnd, FALSE);           // e disabilita i controlli
      WinEnableControl(hwnd, BTTN_UNDO, FALSE);
      WinEnableControl(hwnd, BTTN_DEFAULT, FALSE);
   } else {
      if (flag) {  // se inizializzazione imposta limiti entryfield
         DlgEFSetTxtLimit(hwnd, EF_ATYPE, 31);
         DlgEFSetTxtLimit(hwnd, EF_F_TOIMP, 255);
         DlgEFSetTxtLimit(hwnd, EF_IMP_PROG, 255);
         DlgEFSetTxtLimit(hwnd, EF_IMP_PARMS, 255);
      } /* endif */
      pbTemp = (PBYTE)punarcNew->pui;
      pbRef = (PBYTE)pimp->unarc.pui;
      i = punarcNew->ulSize;
      while (i--) *pbTemp++ = *pbRef++;
   } /* endif */
   // riempie la listbox "Archive type" con le estensioni riconosciute
   for (i = 0; i < punarcNew->ulItems; i++) {
      DlgLboxInsertItem(hwnd, LB_ATYPE, LIT_END, 
                        ((PSZ)punarcNew->pui) + punarcNew->pui[i].ulExt);
   } /* endfor */
}


//==========================================================================\
// ProcPrefImp2WMCtl: processa msg WM_CONTROL                               |
//==========================================================================/

VOID ProcPrefImp2WMCtl(HWND hwnd, MPARAM mp1, PUNARCDATA punNew) {
   int idx;
   static BOOL selection;

   // selezione item listbox
   if (SHORT1FROMMP(mp1) == LB_ATYPE && SHORT2FROMMP(mp1) == LN_SELECT) {
      // rileva presenza selezione nella listbox per abilitare pulsante 
      if ((idx = DlgLboxQuerySelectedItem(hwnd, LB_ATYPE)) != LIT_NONE) {
         WinEnableControl(hwnd, BTN_REMOVE, TRUE);
         // ogni volta che viene selezionata una voce scrive i relativi
         // settaggi nei vari entryfield per permetterne la modifica
         WinSetDlgItemText(hwnd, EF_ATYPE, ((PSZ)punNew->pui) +
                      punNew->pui[idx].ulExt);
         WinSetDlgItemText(hwnd, EF_F_TOIMP, ((PSZ)punNew->pui) +
                      punNew->pui[idx].ulImp);
         WinSetDlgItemText(hwnd, EF_IMP_PROG, ((PSZ)punNew->pui) +
                      punNew->pui[idx].ulProg);
         selection = TRUE;
         WinSetDlgItemText(hwnd, EF_IMP_PARMS, ((PSZ)punNew->pui) + 
                      punNew->pui[idx].ulParms);
      } // end if
   // cambiamento stato entryfield
   } else if (SHORT1FROMMP(mp1) >= EF_ATYPE &&
              SHORT1FROMMP(mp1) <= EF_IMP_PARMS &&
              SHORT2FROMMP(mp1) == EN_CHANGE) {
      if (selection) { // non cambia stato del pulsante ADD se il
         selection = FALSE; // msg viene da una selezione nella LB
      } else {
         char achExt[32];
         BOOL flag = WinQueryDlgItemTextLength(hwnd, EF_ATYPE ) &&
                     WinQueryDlgItemTextLength(hwnd, EF_F_TOIMP) &&
                     WinQueryDlgItemTextLength(hwnd, EF_IMP_PROG) &&
                     WinQueryDlgItemTextLength(hwnd, EF_IMP_PARMS);
         idx = DlgLboxQuerySelectedItem(hwnd, LB_ATYPE);
         WinEnableControl(hwnd, BTN_REPLACE, flag && idx != LIT_NONE);
         WinQueryDlgItemText(hwnd, EF_ATYPE, 32, achExt);
         idx = isInListBox(hwnd, achExt, LB_ATYPE);
         WinEnableControl(hwnd, BTN_ADD, flag && idx < 0);
      } /* endif */
   } /* endif */
}


//==========================================================================\
// ReplaceUnarcItem: edita un item tipo di programma scompattazione         |
// parametri:                                                               |
// HWND hwnd                                                                |
// valore restituito:                                                       |
// BOOL = TRUE: base dati aggiornata, FALSE: aggiornamento fallito          |
//==========================================================================/

BOOL ReplaceUnarcItem(HWND hwnd, PUNARCDATA puNew) {
   UNARCDATA unarcTmp;    // struttura temporanea dati unarc
   ULONG ulNewPrg;        // offset aggiuntivo prg nuovo item
   ULONG ulNewImp;        // offset aggiuntivo file imp nuovo item
   ULONG ulNewParms;      // offset aggiuntivo parms nuovo item
   LONG lShift;           // offset aggiuntivo totale nuovo item
   PBYTE pbTmp;           // puntatori per copiare dati appesi
   PBYTE pbNew;           // alla fine dell'array di UNARC_ITEMs
   int i, idx;            // indice ciclo for - posiz inserz item
   // dimensione dati nuovo item: offset al programma
   ulNewPrg = WinQueryDlgItemTextLength(hwnd, EF_ATYPE) + 1;
   // offset al file da importare
   ulNewImp = WinQueryDlgItemTextLength(hwnd, EF_IMP_PROG) + 1 + ulNewPrg;
   // offset ai parametri
   ulNewParms =  WinQueryDlgItemTextLength(hwnd, EF_F_TOIMP) + 1 + ulNewImp;
   // totale dati/offset all'estensione item successivo
   lShift = WinQueryDlgItemTextLength(hwnd, EF_IMP_PARMS) + 1 +  ulNewParms;
   idx = DlgLboxQuerySelectedItem(hwnd, LB_ATYPE);
   // dati nuovo unarc-data
   unarcTmp.ulSize = puNew->ulSize + lShift -
                     (puNew->pui[idx + 1].ulExt - puNew->pui[idx].ulExt);
   unarcTmp.ulItems = puNew->ulItems;
   // allocazione memoria per il nuovo array di unarc-item
   if ((unarcTmp.pui = (PUNARC_ITEM)malloc((size_t)unarcTmp.ulSize)) == NULL) {
      PMPrint(hwnd, ERR_ALLOC_UPDATE_UNARC_DBASE);
      // cancella dati dagli entry field
      CleanUnarcEntries(hwnd);
      return FALSE;
   } // end if          - se allocazione Š riuscita:
   for (i = 0; i < idx; i++) {      // fino a est < estens corr
      unarcTmp.pui[i].ulExt = puNew->pui[i].ulExt;
      unarcTmp.pui[i].ulProg = puNew->pui[i].ulProg;
      unarcTmp.pui[i].ulImp = puNew->pui[i].ulImp;
      unarcTmp.pui[i].ulParms = puNew->pui[i].ulParms;
   } // endfor             - modifica dati estensione corrente
   unarcTmp.pui[i].ulExt = puNew->pui[i].ulExt;
   unarcTmp.pui[i].ulProg = unarcTmp.pui[i].ulExt + ulNewPrg;
   unarcTmp.pui[i].ulImp = unarcTmp.pui[i].ulExt + ulNewImp;
   unarcTmp.pui[i].ulParms = unarcTmp.pui[i].ulExt + ulNewParms;
   // inserisce dati dei restanti item
   lShift -= puNew->pui[i + 1].ulExt - puNew->pui[i].ulExt;
   while (++i <= unarcTmp.ulItems) {
      unarcTmp.pui[i].ulExt = puNew->pui[i].ulExt + lShift;
      unarcTmp.pui[i].ulProg = puNew->pui[i].ulProg + lShift;
      unarcTmp.pui[i].ulImp = puNew->pui[i].ulImp + lShift;
      unarcTmp.pui[i].ulParms = puNew->pui[i].ulParms + lShift;
   } /* endwhile */
   // copia le stringhe appese alla fine dell'array di strutt unarcitem
   pbTmp = ((PBYTE)unarcTmp.pui) + unarcTmp.pui->ulExt;
   pbNew = ((PBYTE)puNew->pui) + puNew->pui->ulExt;
   // copia dati precedenti nuovo item
   for (i = puNew->pui->ulExt; i < puNew->pui[idx].ulExt; i++)
      *pbTmp++ = *pbNew++;
   // copia dati nuovo item
   pbTmp += WinQueryDlgItemText(hwnd, EF_ATYPE, ulNewPrg, pbTmp) + 1;
   pbTmp += WinQueryDlgItemText(hwnd, EF_IMP_PROG, ulNewImp - ulNewPrg, pbTmp) + 1;
   pbTmp += WinQueryDlgItemText(hwnd, EF_F_TOIMP, ulNewParms - ulNewImp, pbTmp) + 1;
   pbTmp += WinQueryDlgItemText(hwnd, EF_IMP_PARMS,
                                unarcTmp.pui[idx + 1].ulExt -
                                unarcTmp.pui[idx].ulParms, pbTmp) + 1;
   // copia dati rimanenti
   pbNew = ((PBYTE)puNew->pui) + puNew->pui[idx + 1].ulExt;
   for (i = puNew->pui[idx + 1].ulExt; i < puNew->ulSize; i++)
      *pbTmp++ = *pbNew++;
   // libera memoria precedentemente allocata per puNew->pui spostando
   // il puntatore all'indirizzo di unrcTmp.pui
   free(puNew->pui);
   *puNew = unarcTmp;
   // vuota i vari entry field
   CleanUnarcEntries(hwnd);
   // aggiorna la list box Archive Type
   DlgLboxDeleteAll(hwnd, LB_ATYPE);
   for (i = 0; i < puNew->ulItems; i++)
      DlgLboxInsertItem(hwnd, LB_ATYPE, LIT_END, 
                        ((PSZ)puNew->pui) + puNew->pui[i].ulExt);
   WinEnableControl(hwnd, BTN_REMOVE, FALSE);
   return TRUE;
}


//==========================================================================\
// AddUnarcItem: aggiunge dati nuovo tipo di programma scompattazione al    |
// data base                                                                |
// parametri:                                                               |
// HWND hwnd                                                                |
// valore restituito:                                                       |
// BOOL = TRUE: base dati aggiornata, FALSE: aggiornamento fallito          |
//==========================================================================/

BOOL AddUnarcItem(HWND hwnd, PUNARCDATA puNew) {
   UNARCDATA unarcTmp;    // struttura temporanea dati unarc
   ULONG ulNewPrg;        // offset aggiuntivo prg nuovo item
   ULONG ulNewImp;        // offset aggiuntivo file imp nuovo item
   ULONG ulNewParms;      // offset aggiuntivo parms nuovo item
   LONG lShift;           // offset aggiuntivo totale nuovo item
   PBYTE pbTmp;           // puntatori per copiare dati appesi
   PBYTE pbNew;           // alla fine dell'array di UNARC_ITEMs
   int i, idx;            // indice ciclo for - posiz inserz item
   char achExt[32];
   WinQueryDlgItemText(hwnd, EF_ATYPE, 32, achExt); // legge nuova estensione
   // dimensione dati nuovo item: offset al programma
   ulNewPrg = WinQueryDlgItemTextLength(hwnd, EF_ATYPE) + 1;
   // offset al file da importare
   ulNewImp = WinQueryDlgItemTextLength(hwnd, EF_IMP_PROG) + 1 + ulNewPrg;
   // offset ai parametri
   ulNewParms =  WinQueryDlgItemTextLength(hwnd, EF_F_TOIMP) + 1 + ulNewImp;
   // totale dati/offset all'estensione item successivo
   lShift = WinQueryDlgItemTextLength(hwnd, EF_IMP_PARMS) + 1 +  ulNewParms;
   // calcola la posizione di inserzione del nuovo item
   idx = -isInListBox(hwnd, achExt, LB_ATYPE) - 1;
   unarcTmp.ulSize = puNew->ulSize + lShift + sizeof(UNARC_ITEM);
   unarcTmp.ulItems = puNew->ulItems + 1;
   // allocazione memoria per il nuovo array di unarc-item
   if ((unarcTmp.pui = (PUNARC_ITEM)malloc((size_t)unarcTmp.ulSize)) == NULL) {
      PMPrint(hwnd, ERR_ALLOC_UPDATE_UNARC_DBASE);
      // cancella dati dagli entry field
      CleanUnarcEntries(hwnd);
      return FALSE;
   } // end if          - se allocazione Š riuscita:
   for (i = 0; i < idx; i++) {       // fino a est < est corrente
      unarcTmp.pui[i].ulExt = puNew->pui[i].ulExt + sizeof(UNARC_ITEM);
      unarcTmp.pui[i].ulProg = puNew->pui[i].ulProg + sizeof(UNARC_ITEM);
      unarcTmp.pui[i].ulImp = puNew->pui[i].ulImp + sizeof(UNARC_ITEM);
      unarcTmp.pui[i].ulParms = puNew->pui[i].ulParms + sizeof(UNARC_ITEM);
   } /* endfor */
   // inserisce nuova estensione: (i = est corrente)
   unarcTmp.pui[i].ulExt = puNew->pui[i].ulExt + sizeof(UNARC_ITEM);
   unarcTmp.pui[i].ulProg = unarcTmp.pui[i].ulExt + ulNewPrg;
   unarcTmp.pui[i].ulImp = unarcTmp.pui[i].ulExt + ulNewImp;
   unarcTmp.pui[i].ulParms = unarcTmp.pui[i].ulExt + ulNewParms;
   lShift += sizeof(UNARC_ITEM);
   // inserisce precedenti item restanti
   while (++i <= unarcTmp.ulItems) {
      unarcTmp.pui[i].ulExt = puNew->pui[i - 1].ulExt + lShift;
      unarcTmp.pui[i].ulProg = puNew->pui[i - 1].ulProg + lShift ;
      unarcTmp.pui[i].ulImp = puNew->pui[i - 1].ulImp + lShift;
      unarcTmp.pui[i].ulParms = puNew->pui[i - 1].ulParms + lShift;
   } /* endwhile */
   // copia le stringhe appese alla fine dell'array di strutt unarcitem
   pbTmp = ((PBYTE)unarcTmp.pui) + unarcTmp.pui->ulExt;
   pbNew = ((PBYTE)puNew->pui) + puNew->pui->ulExt;
   // copia dati precedenti nuovo item
   for (i = puNew->pui->ulExt; i < puNew->pui[idx].ulExt; i++)
      *pbTmp++ = *pbNew++;
   // copia dati nuovo item
   pbTmp += WinQueryDlgItemText(hwnd, EF_ATYPE, ulNewPrg, pbTmp) + 1;
   pbTmp += WinQueryDlgItemText(hwnd, EF_IMP_PROG, ulNewImp - ulNewPrg, pbTmp) + 1;
   pbTmp += WinQueryDlgItemText(hwnd, EF_F_TOIMP, ulNewParms - ulNewImp, pbTmp) + 1;
   pbTmp += WinQueryDlgItemText(hwnd, EF_IMP_PARMS, lShift - ulNewParms, pbTmp) + 1;
   // copia dati rimanenti
   while (i++ < puNew->ulSize) *pbTmp++ = *pbNew++;
   // libera memoria precedentemente allocata per puNew->pui spostando
   // il puntatore all'indirizzo di unrcTmp.pui
   free(puNew->pui);
   *puNew = unarcTmp;
   // vuota i vari entry field
   CleanUnarcEntries(hwnd);
   // aggiorna la list box Archive Type
   DlgLboxDeleteAll(hwnd, LB_ATYPE);
   for (i = 0; i < puNew->ulItems; i++)
      DlgLboxInsertItem(hwnd, LB_ATYPE, LIT_END, 
                        ((PSZ)puNew->pui) + puNew->pui[i].ulExt);
   WinEnableControl(hwnd, BTN_REMOVE, FALSE);
   return TRUE;
}


//==========================================================================\
// RemUnarcItem: rimuove l'item selezionato dal data base                   |
// parametri:                                                               |
// HWND hwnd                                                                |
// valore restituito:                                                       |
// BOOL = TRUE: base dati aggiornata, FALSE: aggiornamento fallito          |
//==========================================================================/

BOOL RemUnarcItem(HWND hwnd, PUNARCDATA puNew) {
   UNARCDATA unarcTmp;
   LONG lShift;
   PBYTE pbTmp;           // puntatori per copiare dati appesi
   PBYTE pbNew;           // alla fine dell'array di UNARC_ITEMs
   int i;
   int idx = DlgLboxQuerySelectedItem(hwnd, LB_ATYPE);
   // quantit… di dati da cancellare:
   lShift = puNew->pui[idx + 1].ulExt - puNew->pui[idx].ulExt +
             sizeof(UNARC_ITEM);
   // calcola nuova dimensione da allocare x array unarc items
   unarcTmp.ulSize = puNew->ulSize - lShift;
   unarcTmp.ulItems = puNew->ulItems - 1;
   if ((unarcTmp.pui = (PUNARC_ITEM)malloc((size_t)unarcTmp.ulSize)) == NULL) {
      PMPrint(hwnd, ERR_ALLOC_UPDATE_UNARC_DBASE);
      // cancella dati dagli entry field
      DlgLboxDeselectItem(hwnd, LB_ATYPE, idx);
      CleanUnarcEntries(hwnd);
      return FALSE;
   } // end if
   for (i = 0; i < idx; i++) {
      unarcTmp.pui[i].ulExt = puNew->pui[i].ulExt - sizeof(UNARC_ITEM);
      unarcTmp.pui[i].ulProg = puNew->pui[i].ulProg - sizeof(UNARC_ITEM);
      unarcTmp.pui[i].ulImp = puNew->pui[i].ulImp - sizeof(UNARC_ITEM);
      unarcTmp.pui[i].ulParms = puNew->pui[i].ulParms - sizeof(UNARC_ITEM);
   } /* endfor */
   while (i <= unarcTmp.ulItems) {
      unarcTmp.pui[i].ulExt = puNew->pui[i + 1].ulExt - lShift;
      unarcTmp.pui[i].ulProg = puNew->pui[i + 1].ulProg - lShift ;
      unarcTmp.pui[i].ulImp = puNew->pui[i + 1].ulImp - lShift;
      unarcTmp.pui[i].ulParms = puNew->pui[i + 1].ulParms - lShift;
      i++;
   } /* endwhile */
   // copia le stringhe appese alla fine dell'array di strutt unarcitem
   pbTmp = ((PBYTE)unarcTmp.pui) + unarcTmp.pui->ulExt;
   pbNew = ((PBYTE)puNew->pui) + puNew->pui->ulExt;
   // copia dati precedenti nuovo item
   for (i = puNew->pui->ulExt; i < puNew->pui[idx].ulExt; i++)
      *pbTmp++ = *pbNew++;
   // salta dati item da rimuovere
   pbNew += lShift - sizeof(UNARC_ITEM);
   i += lShift - sizeof(UNARC_ITEM);
   while (i++ < puNew->ulSize) *pbTmp++ = *pbNew++;
   // libera risorse precedente data base
   free(puNew->pui);
   *puNew = unarcTmp;
   // vuota i vari entry field
   CleanUnarcEntries(hwnd);
   // aggiorna la list box Archive Type
   DlgLboxDeleteAll(hwnd, LB_ATYPE);
   for (i = 0; i < puNew->ulItems; i++)
      DlgLboxInsertItem(hwnd, LB_ATYPE, LIT_END, 
                        ((PSZ)puNew->pui) + puNew->pui[i].ulExt);
   WinEnableControl(hwnd, BTN_REMOVE, FALSE);
   return TRUE;
}


//==========================================================================\
// vuota tutti gli entry field                                              |
//==========================================================================/

VOID CleanUnarcEntries(HWND hwnd) {
   WinSetDlgItemText(hwnd, EF_ATYPE, "");
   WinSetDlgItemText(hwnd, EF_F_TOIMP, "");
   WinSetDlgItemText(hwnd, EF_IMP_PROG, "");
   WinSetDlgItemText(hwnd, EF_IMP_PARMS, "");
}


//==========================================================================\
// reimposta i valori di default                                            |
//==========================================================================/

BOOL SetImport2Default(HWND hwnd, PUNARCDATA puNew) {
   UNARCDATA unarcTmp;
   PBYTE pbTmp;           // puntatori per copiare dati appesi
   PBYTE pbNew;           // alla fine dell'array di UNARC_ITEMs
   int i;
   CleanUnarcEntries(hwnd);
   unarcTmp.ulItems = 1;
   unarcTmp.ulSize = 37 + 2 * sizeof(UNARC_ITEM);
   if ((unarcTmp.pui = (PUNARC_ITEM)malloc((size_t)unarcTmp.ulSize)) == NULL) {
      PMPrint(hwnd, ERR_ALLOC_UPDATE_UNARC_DBASE);
      // cancella dati dagli entry field
      return FALSE;
   } // end if
   unarcTmp.pui[0].ulExt = 0x20;
   unarcTmp.pui[0].ulProg = 0x26;
   unarcTmp.pui[0].ulImp = 0x30;
   unarcTmp.pui[0].ulParms = 0x3c;
   unarcTmp.pui[1].ulExt = unarcTmp.ulSize;
   unarcTmp.pui[1].ulProg = unarcTmp.ulSize;
   unarcTmp.pui[1].ulImp = unarcTmp.ulSize;
   unarcTmp.pui[1].ulParms = unarcTmp.ulSize;
   pbTmp = ((PBYTE)unarcTmp.pui) + unarcTmp.pui->ulExt;
   pbNew = (PBYTE)"*.zip\0unzip.exe\0file_id.diz\0-C %f %i";
   for (i = unarcTmp.pui->ulExt; i < unarcTmp.ulSize; i++)
      *pbTmp++ = *pbNew++;
   free(puNew->pui);
   *puNew = unarcTmp;
   // vuota i vari entry field
   CleanUnarcEntries(hwnd);
   // aggiorna la list box Archive Type
   DlgLboxDeleteAll(hwnd, LB_ATYPE);
   for (i = 0; i < puNew->ulItems; i++)
      DlgLboxInsertItem(hwnd, LB_ATYPE, LIT_END, 
                        ((PSZ)puNew->pui) + puNew->pui[i].ulExt);
   return TRUE;
}

//==========================================================================\
// abilita/disabilita i test statici e gli entry field corrispondenti       |
//==========================================================================/

VOID EnableImp2Entries(HWND hwnd, BOOL flag) {
   WinEnableControl(hwnd, TXT_NEWTYPE, flag);
   WinEnableControl(hwnd, EF_ATYPE, flag);
   WinEnableControl(hwnd, TXT_F_TOIMP, flag);
   WinEnableControl(hwnd, EF_F_TOIMP, flag);
   WinEnableControl(hwnd, TXT_IMP_PROG, flag);
   WinEnableControl(hwnd, EF_IMP_PROG, flag);
   WinEnableControl(hwnd, TXT_IMP_PARMS, flag);
   WinEnableControl(hwnd, EF_IMP_PARMS, flag);
}
