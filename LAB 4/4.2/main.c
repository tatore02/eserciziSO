/*
Rendere unbuffered gli stream utilizzati realizzando
una funzione my_setbuf() (che funzioni come setbuf() )
implementata utilizzando la funzione setvbuf().
*/

#include  <unistd.h>
#include  <stdio.h>

/*
modeOfBuf == 0: use buf of lenght BUFSIZ
modeOfBuf == 1: steam unbeffered
*/
void my_setbuf(FILE *fp,char *buf){
  setvbuf(fp,NULL,_IONBF,0);
}
