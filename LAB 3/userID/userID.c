#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc,char *argv[]){

  struct stat buf;
  stat("ciao.txt",&buf);

  // if(S_ISUID(buf.st_mode) & S_ISGID(buf.st_mode))
  // puts("flag settato");
  // else puts("flag NON settato");

  printf("%d",S_ISUID(buf.st_mode));
}
