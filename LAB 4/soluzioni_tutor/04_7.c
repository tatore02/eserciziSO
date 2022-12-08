#include <stdio.h>

int main () {
   FILE *fp, *fp2;
   int c;
   char buffer [256];

   fp = fopen("testo.txt", "r+");
   fp2 = fopen("risultato.txt", "w");

   if( fp == NULL ) {
      perror("Error in opening file");
      return(-1);
   }
   while(!feof(fp)) {
      c = getc (fp);

      if( c == '!' ) {
         ungetc ('+', fp);
      } else {
         ungetc(c, fp);
      }

      fgets(buffer, 255, fp);
      fputs(buffer, fp2);
   }
   return(0);
}
