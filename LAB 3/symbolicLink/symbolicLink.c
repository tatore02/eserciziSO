#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int main(){

  DIR *d;
  if((d = opendir("..") == NULL)){
    printf("ERROR\n");
    exit(1);
  }

  struct dirent *str_dir;

  struct stat buf;
  struct stat buf2;

  while((str_dir = readdir(d)) != NULL){
    lstat(str_dir->d_name,&buf);

    if(S_ISLNK(buf.st_mode)){
      printf("OK\n");
    }
  }
}
