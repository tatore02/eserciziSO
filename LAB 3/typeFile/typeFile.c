//Questo programma prende come parametro un file e stampa il suo tipo

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]){

  struct stat buf;

  lstat("ciao.txt",&buf);

  if (S_ISREG(buf.st_mode))
    puts("regular");
  else if (S_ISDIR(buf.st_mode))
    puts("directory");
  else if (S_ISCHR(buf.st_mode))
    puts("“character special”");
  else if (S_ISBLK(buf.st_mode))
    puts("“block special”");
  else if (S_ISFIFO(buf.st_mode))
    puts("pipe or FIFO");
  else if (S_ISLNK(buf.st_mode))
    puts("symbolic link");
  else if (S_ISSOCK(buf.st_mode)){
    puts("socket");
  }

}
