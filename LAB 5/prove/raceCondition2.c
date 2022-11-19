/*
Scrivere un programma C in cui un processo genera un processo figlio
il figlio scrive sullo standard output il proprio pid
Successivamente, il padre scrive il proprio pid
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();
    if(pid == 0){
        printf("pid figlio: %d\n",getpid());
        exit(1);
    }
    else{
        printf("pid padre: %d\n", getpid());
    }
}