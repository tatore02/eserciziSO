#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void my_exit1(){
  printf("sono il primo handler\n");
}

void my_exit2(){
  printf("sono il secondo handler\n");
}

int main(){
  atexit(my_exit2);
  atexit(my_exit1);
  printf("ho finito il main");
  _exit(1);
}
