#include  <sys/types.h>
#include  <fcntl.h>
#include  <sys/stat.h>
#include  <unistd.h>
#include  <stdio.h>
#include  <stdlib.h>

int main(){
  int fd;

  if((fd = open("FILE1.txt",O_RDWR|O_CREAT|O_TRUNC,0644)) < 0){
    fprintf(stderr,"ERROR open & create file\n");
    exit(0);
  }


  FILE *file = fopen("FILE1.txt","r+");

  fprintf(file,"questa è una prova della funzione ftell\n");

  printf("Posizione puntatore: %ld\n",ftell(file));

}
