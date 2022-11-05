#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int my_acces(char *path,int mode){
  uid_t user = getuid();
  uid_t group = getgid();

  return 0;
}

int main(){

}
