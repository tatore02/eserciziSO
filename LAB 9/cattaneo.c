#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

// da provare su linux
int main(){
  int fd;
  if((fd = open("/dev/pts/1",O_WRONLY)) < 0){
    perror("open");
    exit(1);
  }
  char *msg = "scemo chi legge";

  if(write(fd,msg,strlen(msg) < 0)){
    perror("write");
    exit(1);
  }


}
