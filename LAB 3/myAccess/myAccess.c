#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char* argv[]){

  if(argc != 2){
    puts("Error: usage ./a.out <pathname>");
    exit(0);
  }

  int fd = open("ciao.txt",O_WRONLY | O_CREAT | O_TRUNC, 0200);

  int mode;

  printf("In quale modalità accedere al file?\n");
  printf("0 : per verificare se esiste\n");
  printf("1 : per verificare se può essere eseguito\n");
  printf("4 : per verificare se può essere letto\n");
  printf("6 : per verificare se può essere scritto\n");

  scanf("%d",&mode);

  if(mode == 0){
    if(open("ciao.txt",O_RDONLY) < 0)
      printf("ERROR: il file non esiste\n");
  }
  else if(mode == 1){
    if(open("ciao.txt",O_RDONLY,0100) < 0)
      printf("ERROR: il file non può essere eseguito\n");
  }
  else if(mode == 4){
    if(open("ciao.txt",O_RDONLY,0400) < 0)
      printf("ERROR: il file non può essere letto\n");
  }
  else if(mode == 6){
    if(open("ciao.txt",O_WRONLY,0200) < 0)
      printf("ERROR: il file non può essere scritto\n");
  }
  else exit(0);

}
