//==========================================================================\
// ordattrs.c : funzioni relative agli attributi ordinare e alla data/ora   |
// dei file                                                                 |
// VOID GetOrdAttrs(HWND hwnd, PFILESPECS pfsp);                            |
// VOID ShowFileFlags(HWND hwnd, PFILESPECS pfsp);                          |
// VOID ShowDateTime(HWND hwnd, PFILESPECS pfsp);                           |
// VOID ReadNewOrdAttrs(HWND hwnd, PFILESPECS pfsp);                        |
// BOOL isOrdAttrChanged(HWND hwnd, PFILESPECS pfsp);                       |
// VOID UpdateOrdAttr(HWND hwnd, PFILESTATUS3 pfs,                          |
//                    PFILESPECS pfsp, ULONG mask);                         |
//==========================================================================/

#define INCL_WIN
#include <os2.h>
#include <stdio.h>
#include <spinbtn.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"


//==========================================================================\
// legge attributi ordinari e data ora del file memorizzandoli nel membro   |
// "fs" della struttura globale "am"                                        |
// WHND hwnd   = handle finestra principale                                 |
// PSZ pszFile = nome del file corrente                                     |
//==========================================================================/

VOID GetOrdAttrs(HWND hwnd, PFILESPECS pfsp) {

   DosQueryPathInfo(pfsp->pszFile, FIL_QUERYEASIZE,
                    (PVOID)&pfsp->fs, sizeof(FILESTATUS4));
   // inizializza struttura usata poi x editare attributi ordinari
   pfsp->fsNew.fdateCreation = pfsp->fs.fdateCreation;
   pfsp->fsNew.ftimeCreation = pfsp->fs.ftimeCreation;
   pfsp->fsNew.fdateLastAccess = pfsp->fs.fdateLastAccess;
   pfsp->fsNew.ftimeLastAccess = pfsp->fs.ftimeLastAccess;
   pfsp->fsNew.fdateLastWrite = pfsp->fs.fdateLastWrite;
   pfsp->fsNew.ftimeLastWrite = pfsp->fs.ftimeLastWrite;
   pfsp->fsNew.attrFile = pfsp->fs.attrFile;
   pfsp->fsNew.cbFile = 0;     // usato come flag x determinare cambiamento
   ShowFileFlags(hwnd, pfsp);
   ShowDateTime(hwnd, pfsp);
}


//==========================================================================\
// setta le checkbox degli attributi nella finestra del dialogo principale  |
// secondo gli attributi correnti                                           |
// HWND hwnd = handle finestra principale                                   |
//==========================================================================/

VOID ShowFileFlags(HWND hwnd, PFILESPECS pfsp) {
   WinCheckButton(hwnd, CBOX_A, pfsp->fs.attrFile & FILE_ARCHIVED ? 1: 0);
   WinCheckButton(hwnd, CBOX_S, pfsp->fs.attrFile & FILE_SYSTEM ? 1: 0);
   WinCheckButton(hwnd, CBOX_H, pfsp->fs.attrFile & FILE_HIDDEN ? 1: 0);
   WinCheckButton(hwnd, CBOX_R, pfsp->fs.attrFile & FILE_READONLY ? 1: 0);
}


//==========================================================================\
// setta gli spinbuttons nella finestra principale secondo data e ora del   |
// file                                                                     |
// HWND hwnd = handle della finestra principale                             |
//==========================================================================/

VOID ShowDateTime(HWND hwnd, PFILESPECS pfsp) {
   CHAR buf[36];
   FFDATE ffd;

   i2fstr(pfsp->fs.cbFile, sstrcpy(buf, "File size: "), pfsp->milSep);
   WinSetDlgItemText(hwnd, TXT_FSIZE, buf);   // dimensione file
   i2fstr(pfsp->fs.cbList, sstrcpy(buf, "EAs size : "), pfsp->milSep);
   WinSetDlgItemText(hwnd, TXT_EASIZE, buf);  // dimensione EAs
   // data e ora ultima scrittura
   FormatDate(&pfsp->fsNew.fdateLastWrite, &ffd, pfsp->dtFrm);
   sprintf(buf, "C~hanged  : %02u%c%02u%c%02u - %02u%c%02u%c%02u",
           ffd.a, pfsp->chD, ffd.b, pfsp->chD, ffd.c,
           pfsp->fsNew.ftimeLastWrite.hours, pfsp->chT,
           pfsp->fsNew.ftimeLastWrite.minutes, pfsp->chT,
           pfsp->fsNew.ftimeLastWrite.twosecs * 2);
   WinSetDlgItemText(hwnd, STB_WRITTEN, buf);
   // se il file system non supporta data creazione/accesso terimina
   if (!pfsp->hpfs) return;
   // data ora creazione
   FormatDate(&pfsp->fsNew.fdateCreation, &ffd, pfsp->dtFrm);
   sprintf(buf, "C~reated  : %02u%c%02u%c%02u - %02u%c%02u%c%02u",
           ffd.a, pfsp->chD, ffd.b, pfsp->chD, ffd.c,
           pfsp->fsNew.ftimeCreation.hours, pfsp->chT,
           pfsp->fsNew.ftimeCreation.minutes, pfsp->chT,
           pfsp->fsNew.ftimeCreation.twosecs * 2);
   WinSetDlgItemText(hwnd, STB_CREATED, buf);
   // data ora ultimo accesso
   FormatDate(&pfsp->fsNew.fdateLastAccess, &ffd, pfsp->dtFrm);
   sprintf(buf, "~Accessed : %02u%c%02u%c%02u - %02u%c%02u%c%02u",
           ffd.a, pfsp->chD, ffd.b, pfsp->chD, ffd.c,
           pfsp->fsNew.ftimeLastAccess.hours, pfsp->chT,
           pfsp->fsNew.ftimeLastAccess.minutes, pfsp->chT,
           pfsp->fsNew.ftimeLastAccess.twosecs * 2);
   WinSetDlgItemText(hwnd, STB_ACCESSED, buf);
}


//==========================================================================\
// copia nella struttura FILESTATUS3 i nuovi attributi del file secondo i   |
// valori impostati nelle checkbox                                          |
//==========================================================================/

VOID ReadNewOrdAttrs(HWND hwnd, PFILESPECS pfsp) {
   
   pfsp->fsNew.attrFile = WinQueryButtonCheckstate(hwnd, CBOX_A) ?
                          pfsp->fsNew.attrFile | FILE_ARCHIVED :
                          pfsp->fsNew.attrFile & ~FILE_ARCHIVED;
   pfsp->fsNew.attrFile = WinQueryButtonCheckstate(hwnd, CBOX_H) ?
                          pfsp->fsNew.attrFile | FILE_HIDDEN :
                          pfsp->fsNew.attrFile & ~FILE_HIDDEN;
   pfsp->fsNew.attrFile = WinQueryButtonCheckstate(hwnd, CBOX_R) ?
                          pfsp->fsNew.attrFile | FILE_READONLY :
                          pfsp->fsNew.attrFile & ~FILE_READONLY;
   pfsp->fsNew.attrFile = WinQueryButtonCheckstate(hwnd, CBOX_S) ?
                          pfsp->fsNew.attrFile | FILE_SYSTEM :
                          pfsp->fsNew.attrFile & ~FILE_SYSTEM;
}


//==========================================================================\
// restituisce TRUE se uno degli attributi ordinari o data/ora del file     |
// Š stato modificato                                                       |
// NOTA: cbFile Š usato come flag di cambiamento data/ora ed Š settato      |
//       se viene premuto OK nel dialogo editazione data/ora                |
// HWND hwnd = handle finestra principale                                   |
//==========================================================================/

BOOL isOrdAttrChanged(HWND hwnd, PFILESPECS pfsp) {
   ReadNewOrdAttrs(hwnd, pfsp);
   return (pfsp->fsNew.attrFile != pfsp->fs.attrFile ||
           pfsp->fsNew.cbFile) ?
           TRUE : FALSE;
}


//==========================================================================\
// aggiorna gli attributi e data/ora del file pszFile copiando in am.fs i   |
// dati presenti in am.fsNew selettivamente secondo la maschera mask        |
// HWND hwnd   = handle della finestra principale                           |
// PFILESPECS pfsp = indirizzo struttura dati file                          |
// ULONG mask  = maschera degli attributi da aggiornare                     |
//==========================================================================/

VOID UpdateOrdAttr(HWND hwnd, PFILESTATUS3 pfs, PFILESPECS pfsp, ULONG mask) {

   if (mask & UPDT_A) {                  // aggiorna "ARCHIVE"
      pfs->attrFile = (pfsp->fsNew.attrFile & FILE_ARCHIVED)?
                       pfs->attrFile | FILE_ARCHIVED:
                       pfs->attrFile & ~FILE_ARCHIVED;
   } /* endif */
   if (mask & UPDT_H) {                  // aggiorna "HIDDEN"
      pfs->attrFile = (pfsp->fsNew.attrFile & FILE_HIDDEN)?
                       pfs->attrFile | FILE_HIDDEN:
                       pfs->attrFile & ~FILE_HIDDEN;
   } /* endif */
   if (mask & UPDT_R) {                  // aggiorna "READONLY"
      pfs->attrFile = (pfsp->fsNew.attrFile & FILE_READONLY)?
                       pfs->attrFile | FILE_READONLY:
                       pfs->attrFile & ~FILE_READONLY;
   } /* endif */
   if (mask & UPDT_S) {                  // aggiorna "SYSTEM"
      pfs->attrFile = (pfsp->fsNew.attrFile & FILE_SYSTEM)?
                       pfs->attrFile | FILE_SYSTEM:
                       pfs->attrFile & ~FILE_SYSTEM;
   } /* endif */
   if (mask & UPDT_CHTIME)               // aggiorna l'ora last changed
      pfs->ftimeLastWrite = pfsp->fsNew.ftimeLastWrite;
   if (mask & UPDT_CHDATE)               // aggiorna la data last changed
      pfs->fdateLastWrite = pfsp->fsNew.fdateLastWrite;
   if (mask & UPDT_CRTIME)               // aggiorna l'ora last changed
      pfs->ftimeCreation =  pfsp->fsNew.ftimeCreation;
   if (mask & UPDT_CRDATE)               // aggiorna la data last changed
      pfs->fdateCreation = pfsp->fsNew.fdateCreation;
   if (mask & UPDT_ACTIME)               // aggiorna l'ora last changed
      pfs->ftimeLastAccess = pfsp->fsNew.ftimeLastAccess;
   if (mask & UPDT_ACDATE)               // aggiorna la data last changed
      pfs->fdateLastAccess = pfsp->fsNew.fdateLastAccess;
   DosSetPathInfo(pfsp->pszFile, FIL_STANDARD, pfs,
                  sizeof(FILESTATUS3), 0L);
}
