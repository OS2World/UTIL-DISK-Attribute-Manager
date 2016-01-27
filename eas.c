//==========================================================================\
// eas.c funzioni relative alla gestione degli attributi estesi             |
//==========================================================================/

#define INCL_WIN
#include <os2.h>
#include <string.h>
#include "attman.h"
#include "definitions.h"
#include "funzioni.h"


//===============================[PutEa()]==================================\
// scrive nel file l'attributo specificato e il valore corrispondente       |
// sintassi:                                                                |
// ULONG PutEa(CHAR *pszFile,            nome del file                      |
//             CHAR *pszAttName,         nome attributo da scrivere         |
//             USHORT cbAttName,         lunghezza nome attributo           |
//             CHAR *AttValue,           buffer x valore attrib da scrivere |
//             ULONG *cbValue)           lunghezza valore attributo         |
// riisultato: TRUE = successo, FALSE = errore                              |
//==========================================================================/

BOOL PutEa(CHAR *pszFile, CHAR *pszAttName, USHORT cbAttName,
            CHAR *AttValue, ULONG *cbValue) {

   EAOP2       eaop;                    /* eaop structure             */
   PFEA2       pfea;                    /* pfea structure             */
   
   eaop.fpFEA2List = (PFEA2LIST)AttValue;
   eaop.fpGEA2List = NULL;
   pfea = &eaop.fpFEA2List->list[0];    /* point to first FEA         */
   pfea->oNextEntryOffset = 0;   
   pfea->fEA = '\0';                    /* set the flags              */
   pfea->cbName = (BYTE)cbAttName;      /* Size of FEA name field     */
   pfea->cbValue = *cbValue;            // lunghezza valore relativo attr
   strcpy((PSZ)pfea->szName, pszAttName); // nome attributo
   memmove((PSZ)pfea->szName + (pfea->cbName + 1), // valore attributo
          AttValue + 0x200, *cbValue);
   eaop.fpFEA2List->cbList =  sizeof(ULONG) + sizeof(FEA2) +
                              pfea->cbName + pfea->cbValue;
   return !DosSetPathInfo(pszFile, FIL_QUERYEASIZE, (PSZ)&eaop,
                          sizeof(EAOP2), DSPI_WRTTHRU);
}


//===============================[GetEa()]==================================\
// legge dal file l'attributo specificato                                   |
// sintassi:                                                                |
// ULONG GetEa(CHAR *pszFile,            nome del file                      |
//             CHAR *pszAttName,         nome attributo da leggere          |
//             USHORT cbAttName,         lunghezza nome attributo           |
//             CHAR *AttValue,           buffer x il valore attributo letto |
//             ULONG *cbValue)           lunghezza valore attributo         |
//==========================================================================/

ULONG GetEa(CHAR *file,
            CHAR *attName,
            USHORT cbAttName,
            CHAR *attVal,
            ULONG *cbValue) {

   static UCHAR  geabuff[256];          /* buffer for GEA             */
   EAOP2       eaop;                    /* eaop structure             */
   PGEA2       pgea;                    /* pgea structure             */
   PFEA2       pfea;                    /* pfea structure             */
   
   eaop.fpGEA2List = (PGEA2LIST)geabuff;
   eaop.fpFEA2List = (PFEA2LIST)attVal;
   eaop.oError = 0;                     /* no error occurred yet      */
   pgea = &eaop.fpGEA2List->list[0];    /* point to first GEA         */
   eaop.fpGEA2List->cbList = sizeof(ULONG) + // dimens primo GEA
                             sizeof(GEA2) + cbAttName;
   eaop.fpFEA2List->cbList = (ULONG)0xffff; // dimens buffer lettura EA
   pgea->cbName = cbAttName;               /* fill in the EA name length */
   strcpy(pgea->szName, attName);          // scrive nome attributo da leggere
   pgea->oNextEntryOffset = 0;
   DosQueryPathInfo(file, 3, (PSZ)&eaop, sizeof(EAOP2));
   pfea = &(eaop.fpFEA2List->list[0]);  /* point to the first FEA     */
   *cbValue = (size_t)pfea->cbValue;
   memmove(attVal, ((PSZ)pfea->szName+(pfea->cbName+1)), *cbValue);
   return 0;
}


//==============================[Attr2Text]=================================\
// converte l'attributo letto in testo ASCII o in [...] se Š rapppresentato |
// dati in forma binaria. Restituisce la lunghezza del testo ottenuto       |
// sintassi                                                                 |
// USHORT Attr2Text(CHAR *buffer,        i dati da convertire in testo      |
//                  ULONG cbAttr,        la lunghezza dei dati              |
//                  BOOL mode)           dargli valore 1 per resettarlo     |
//==========================================================================/

USHORT Attr2Text(CHAR *buffer, ULONG cbAttr, BOOL mode) {
   USHORT i;                         // uso vario
   static USHORT cbWrote;            // caratteri scritti
   static USHORT cbRead;             // caratteri letti
   CHAR *cursor;

   if (mode)
      cbWrote = cbRead = 0;
   cursor = buffer + cbRead;
   if (cbAttr <= cbRead)
      return cbWrote;
   if (*((PUSHORT)cursor) == EAT_MVMT || *((PUSHORT)cursor) == EAT_MVST) {
      cbRead += 6;
      for (i = 0; i < *(((PUSHORT)cursor) + 2); i++)
         Attr2Text(buffer, cbAttr, 0);
   } else if (*((PUSHORT)cursor) == EAT_ASCII) {// dato di tipo ASCII
      i = *(((PUSHORT)cursor) + 1);             // lunghezza del singolo valore
      // copia il valore corrente a inizio stringa
      memmove(buffer + cbWrote, cursor + 4, (size_t)i);
      *(buffer + cbWrote + i) = '\r'; // aggiunge carattere di a capo
      *(buffer + cbWrote + i + 1) = '\n';
      cbWrote += i + 2;
      cbRead += i + 4;
   } else {                          // dato di tipo binario
      i = *(((PUSHORT)cursor) + 1);
      memmove(buffer + cbWrote, "[...]\r\n", 7);
      cbWrote += 7;
      cbRead += i + 4;
   }
   return cbWrote;
}


//============================[Text2Attr()]=================================\
// converte le coppie \r\n in multipli EAT_ASCII                            |
// VOID Text2Attr(CHAR *buffer,        dati da convertire in EA             |
//                ULONG *cbData)       lunghezza dei dati                   |
//==========================================================================/

VOID Text2Attr(CHAR *buffer, ULONG *cbData) {
   USHORT i, numEntries, writeCur, readCur;  // cos vale solo per alcuni
                                             // tipi di EA!!!
   if (*cbData) {
      *((PUSHORT)buffer) = EAT_MVMT;
      *(((PUSHORT)buffer) + 1) = 0;
      *(((PUSHORT)buffer) + 3) = EAT_ASCII;
      for (i = 0, numEntries = 1, writeCur = 10, readCur = 0x8000 - 0x200;
           readCur + i - (0x8000 - 0x200) < *cbData; i++) {
         if (*(buffer + readCur + i) == '\r') {
            numEntries++;
            memmove(buffer + writeCur, buffer + readCur, i);
            *((PUSHORT)(buffer + writeCur - 2)) = i;
            *((PUSHORT)(buffer + writeCur + i)) = EAT_ASCII;
            writeCur += i + 4;
            readCur += i + 2;
            i = 0;
         } /* endif */
      } /* endfor */
      memmove(buffer + writeCur, buffer + readCur, i);;
      *((PUSHORT)(buffer + writeCur - 2)) = i;
      *(((PUSHORT)buffer) + 2) = numEntries;
      *cbData = writeCur + i;
   } /* endif */
}
