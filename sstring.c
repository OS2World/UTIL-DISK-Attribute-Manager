//==========================================================================\
// sstring.c : funzioni per elaborazione stringhe alternative               |
//==========================================================================/


#define INCL_WIN
#define INCL_WINSTDDRAG
#include <os2.h>
#include "funzioni.h"

// copia source su target, ritorna un puntatore alla fine di target
char* sstrcpy(char* target, char *source) {
   while (*target++ = *source++);
   return --target;
}


// ritorna la lunghezza della stringa s
ULONG sstrlen(const char* s) {
   const char* o = s;
   while (*s) ++s;
   return s - o;
}


// sstrcat concatena in ad out restituendo un puntatore alla fine di out
PSZ sstrcat(char* out, const char* in) {
   while (*out) ++out;
   while (*in) *out++ = *in++;
   *out = 0;
   return out;
}


// sstrcmp: compara due stringhe restituendo 0 se sono =
int sstrcmp(const char* s1, const char* s2) {
   for (; *s1 == *s2; s1++, s2++)
      if (!*s1) return 0;
   return *s1 - *s2;
}


// sstricmp: compara due stringhe in modo case insensitivo

int sstricmp(const char* s1, const char* s2) {
   char c1, c2;
   do {
      // converte in minuscolo copiandoli in c1 e c2 *s1 e *s2
      c1 = (*s1 > '@' && *s1 < '[')? *s1 + 32: *s1;
      c2 = (*s2 > '@' && *s2 < '[')? *s2 + 32: *s2;
      s1++;
      s2++;
      if (!c1) break;
   } while (c1 == c2); /* enddo */
   return c1 - c2;
}


// sstrnicmp: compara due stringhe in modo case insensitivo per n caratteri
int sstrnicmp(char* s1, const char* s2, unsigned int n) {
   char c1, c2;
   do {
      // converte in minuscolo copiandoli in c1 e c2 *s1 e *s2
      c1 = (*s1 > '@' && *s1 < '[')? *s1 + 32: *s1;
      c2 = (*s2 > '@' && *s2 < '[')? *s2 + 32: *s2;
      s1++;
      s2++;
      if (!c1 || !--n) break;
   } while (c1 == c2); /* enddo */
   return c1 - c2;
}


// sstrncmp: compara s1 con s2 per n caratteri
int sstrncmp(char* s1, const char* s2, unsigned int c) {
   for (;*s1 == *s2; s1++, s2++) {
      if (!--c)   return *s1 - *s2;
      if (!*s1) return 0;
   } // end for
   return *s1 - *s2;
}
