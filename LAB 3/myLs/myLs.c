#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

//programma che simula il comando ls

int main(){

DIR *dh= opendir(".");

struct dirent *d;

  while((d = readdir(dh)) != NULL){
    if(strncmp(d->d_name,".",1) != 0)   //per non stampare gli hidden file
      printf("%s\n",d->d_name);
  }
}
