// il padre crea N figli e aspetta la fine della loro esecuzione

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define N 6

int main(){
    pid_t pid;
    int status,i;

    for(i=0;i<N;i++)
        if((pid = fork()) == 0)
            exit(i);

    while((pid = wait(&status)) > 0){
        if(WIFEXITED(status))
            printf("Il processo %d con padre %d ha terminato correttamente con exit status %d\n",pid,getppid(),
                   WIFEXITED(status));
        else
            printf("Il processo %d con padre %d NON ha terminato correttamente\n",pid,getppid());
    }

}