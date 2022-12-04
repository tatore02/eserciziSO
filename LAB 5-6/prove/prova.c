#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
  pid_t a = fork();
  if(a == 0)
  printf("Pid del processo %d\nPid del padre: %d\n",getpid(),getppid());

}
