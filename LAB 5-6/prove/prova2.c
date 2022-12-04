#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int glob=10;

int main(){
  int var=100;
  pid_t pippo;
  printf("prima della fork");
  pippo=fork();
  if(pippo == 0){
    glob++;
    var++;
  }
  else sleep(2);
  printf("pid=%d, glob=%d, var=%d\n",getpid(),glob,var);
  exit(0);
}
