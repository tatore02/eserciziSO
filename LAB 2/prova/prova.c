#include  <sys/types.h>
#include  <fcntl.h>
#include  <sys/stat.h>
#include  <unistd.h>
#include  <stdio.h>

int main(void){
  int    fd,i,n;
  char   buf[50];

  //crea un file con solo il permesso di lettura da parte dell'utente
  remove("text.txt");   //se il file esiste già, viene rimosso
  creat("text.txt",0466);
}
