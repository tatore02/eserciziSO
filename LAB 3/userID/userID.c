#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc,char *argv[]){

  struct stat buf;
  lstat("ciao.txt",&buf);

  if(S_ISUID(buf.st_uid) & S_ISGID(buf.st_gid))
  puts("flag settato");
  else puts("flag NON settato");


}
