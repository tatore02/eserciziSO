#include <stdio.h>

int main () {
   FILE *fp, *fp2;
   int c;
   char buffer [256];

   fp = fopen("ELENCO.txt", "r+");

   if( fp == NULL ) {
      perror("Error in opening file");
      return(-1);
   }
   while(!feof(fp)) {
      c = getc (fp);
      //printf("stampo c: %c\n",c);
      /* replace ! with + */
      if( c == '!' ) {
         ungetc ('+', fp);
      } else {
         ungetc(c, fp);
      }
      fgets(buffer, 255, fp);
      fputs(buffer, stdout);
   }
   return(0);
}
