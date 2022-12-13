#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

int fd[2], t;
pid_t pid, pid1;

if(argc != 2)  {
   printf("Numero di argomenti errato!\n");
   exit(1);
}

pipe(fd);

pid=fork();

if(pid==0) {
  close(fd[0]);
  close(1);
  dup(fd[1]);
  close(fd[1]);
  execlp("cat", "cat",argv[1],(char *)0);
  }

else if(pid) {
  pid1=fork();
  if(pid1==0) {
    close(fd[1]);
    close(0);
    dup(fd[0]);
    close(fd[0]);
    execlp("more","more",(char *)0);
    }

  else if(pid1) {
  close(fd[0]);
  close(fd[1]);
  wait(NULL);
  wait(NULL);
  }
}
}
