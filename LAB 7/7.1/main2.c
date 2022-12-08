#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

  int status;
  pid_t pid;

  pid = fork();


  if(pid == 0)
    printf("Ciao, sono il processo %d figlio di %d\n",getpid(),getppid());

  if(pid > 0){
    printf("Ciao, sono il processo padre %d\n",getpid());
    printf("Terminazione processo padre..\n");

    exit(1);
  }

  printf("Oh no, mio padre è morto,\nora sono stato adotatto dal processo con pid %d\n",getppid());
  exit(1);
}
