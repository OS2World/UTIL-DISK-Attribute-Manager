//==========================================================================\
// drive.c : operazioni relative ai drive                                   |
// BOOL SetDisk(HWND hwnd, BYTE newDisk, PBOOL phpfs);                      |
// VOID FillDriveList(HWND hwnd, PATTMAN pam);                              |
// VOID ProcessDriveSelection(HWND hwnd, MPARAM mp1, PATTMAN pam);          |
// BOOL isHPFS(UCHAR uchDrive);                                             |
//==========================================================================/

#define INCL_WIN
#define INCL_DOSMISC
#include <os2.h>
#include <listbox.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"
#include "interface.h"
#include "messages.h"


//==========================================================================\
// imposta un nuovo drive visualizzando Dialogo [Retry/Cancel] se il drive  |
// non Š disponibile                                                        |
// BYTE newDisk = lettera identificativa della partizione                   |
// HWND hwnd    = handle della finestra principale                          |
// BOOL result  = 0 se il driver Š disponibile, 1 se si Š premuto "Cancel"  |
//==========================================================================/

BOOL SetDisk(HWND hwnd, BYTE newDisk, PBOOL phpfs) {
   APIRET rc;
   BYTE buf[128];
   ULONG ulAct;
   CHAR ch = newDisk;
   newDisk = newDisk > 'Z'? newDisk - 'a' + 1: newDisk - 'A' + 1;
   DosError(0);                  // disabilita dialogo errore drive not ready
   rc = DosQueryFSInfo(newDisk, FSIL_VOLSER, buf, sizeof(buf));
   DosError(1);
   if (rc && rc != 125) {       // se drive not ready-> retry, cancel
      if (WinMessageBox(HWND_DESKTOP, hwnd, DRIVE_NOT_READY, NULL,
                        0, MB_RETRYCANCEL | MB_ERROR | MB_MOVEABLE) ==
          MBID_RETRY) {
         return SetDisk(hwnd, newDisk, phpfs);
      } else {
         return 1;
      } /* endif */
   } /* endif */
   DosSetDefaultDisk(newDisk);
   *phpfs = isHPFS(ch);
   if (hwnd != HWND_DESKTOP) {
      // mostra/nasconde data-ora creazione e ultimo accesso secondo FS
      DlgShowCtl(hwnd, STB_CREATED, *phpfs);
      DlgShowCtl(hwnd, STB_ACCESSED, *phpfs);
   } /* endif */
   return 0;
}


//==========================================================================\
// ottiene la lista dei drive presenti nel sistema e riempie la list box    |
//==========================================================================/

VOID FillDriveList(HWND hwnd, PATTMAN pam) {
   CHAR   szDrive[] = "[ ]";
   ULONG  ulDriveNum = 0   ;
   ULONG  ulDriveMap = 0   ;
   SHORT  i          = 0   ;

   DosQueryCurrentDisk(&ulDriveNum, &ulDriveMap);
   for (i = 0; i < 26; i++) {
      if (ulDriveMap & 1L << i) {
         szDrive[1] = (CHAR)(i + 'A');
         DlgLboxInsertItem(hwnd, LB_DRIVE, LIT_END, szDrive);
      } /* endif */
   } /* endfor */
   pam->fsp.sPrvDrv = ulDriveNum - 1;
   MyDlgLboxSelectItem(hwnd, LB_DRIVE, pam->fsp.sPrvDrv);
}


//==========================================================================\
// processa il msg LM_SELECT ricevuto dalla listbox drive                   |
//==========================================================================/

VOID ProcessDriveSelection(HWND hwnd, MPARAM mp1, PATTMAN pam) { 
   SHORT currIdx;                  // indice drive correntemente selezionato
   ULONG ulRes;

   currIdx = DlgLboxQuerySelectedItem(hwnd, LB_DRIVE);
   // controlla se Š selezionato dall'utente o come effetto collaterale
   if (pam->LMsel) return;                        // di un altro messaggio

   if (currIdx == pam->fsp.sPrvDrv) return; // non Š stato selez nuovo drive
   // se attributo non Š cambiato, modo readonly, o si Š prem Save o Discard
   if (!isChanged(hwnd, pam)) {  //nel dialogo "Save.."
      DlgLboxQueryItemText(hwnd, LB_DRIVE, currIdx, pam->fsp.pszPath, 256);
      // controlla che il drive selezionato sia disponibile
      if (SetDisk(hwnd, pam->fsp.pszPath[1], &pam->fsp.hpfs)) {//Cancel : rimane in curr dir
         QueryCurrentPath(pam->fsp.pszPath, pam->fsp.pszFile);
         MyDlgLboxSelectItem(hwnd, LB_DRIVE, pam->fsp.sPrvDrv);
      } else {                      // drive disponibile
         pam->fsp.psSel[1] = -2;          // forza aggiornamento dati
         QueryCurrentPath(pam->fsp.pszPath, pam->fsp.pszFile);
         FillDirList(hwnd, pam);
         pam->fsp.sPrvDrv = currIdx;
      } // endif
   } else {  // se si Š premuto Cancel riseleziona il drive precedente
      MyDlgLboxSelectItem(hwnd, LB_DRIVE, pam->fsp.sPrvDrv);
   } /* endif */
}


// ritorna TRUE se il file system Š HPFS
BOOL isHPFS(UCHAR uchDrive) {
   BYTE buf[512];
   ULONG ul = 512;
   CHAR pszDrv[] = "?:";
   pszDrv[0] = uchDrive;
   DosQueryFSAttach(pszDrv, 0L, FSAIL_QUERYNAME, (PFSQBUFFER2)buf, &ul);
   return (BOOL)!sstrcmp("HPFS", ((PSZ)(((PFSQBUFFER2)buf)->szName)) + 3);
}
