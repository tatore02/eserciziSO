#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char* argv[]){

  if(argc != 2){
    puts("Error: usage ./a.out <pathname>");
    exit(0);
  }

  struct stat buf;
  stat("ciao.txt",&buf);

  if()


}
