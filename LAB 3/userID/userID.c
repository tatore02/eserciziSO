/*
scrivere un programma che testa se un file ha il flag set-user-id settato
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){

  int fd = open("ciao.txt",O_RDWR,0644);

  struct stat buf;
  stat("ciao.txt",&buf);

  if(buf.st_mode & S_ISUID)
    puts("flag user-id settato");
  else puts("flag user-id NON settato");

  if(buf.st_mode & S_ISGID)
    puts("flag group-id settato");
  else puts("flag group-id NON settato");




}
