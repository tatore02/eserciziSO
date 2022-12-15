#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sig_catch(int signo);
int flag=1;

int main(){

    int fd[2], num;
    pid_t pid, pid1, pid2;
    FILE *in;


    signal(SIGALRM,sig_catch);
    in = fopen("TEMP","r");
    pipe(fd);

    pid=fork();

    if(pid==0){
       close(fd[1]);
       pid1=getpid();
       while(1){
          read(fd[0],&num,sizeof(num));
          read(fd[0],&pid2,sizeof(pid2));
          if(num==-1){
             kill(pid2,SIGKILL);
             printf("Fine esecuzione del figlio\n");
             exit(0);
          }
          printf("%d %d\n",num,pid1);
       }
    }

    else if(pid) {
       alarm(20);
       close(fd[0]);
       pid1=getpid();
       while(flag)  {
          fscanf(in,"%d %d", &num, &pid2);
          write(fd[1],&num, sizeof(num));
          write(fd[1],&pid1, sizeof(pid1));
          sleep(1);
       }
       num=-1;
       write(fd[1],&num, sizeof(num));
       write(fd[1],&pid2, sizeof(pid2));
       printf("Uccidilo!!\n");
       wait(NULL);
       printf("Fine esecuzione del padre\n");
       exit(0);
    }
}



void sig_catch(int signo){
    flag = 0;
    return;
}

