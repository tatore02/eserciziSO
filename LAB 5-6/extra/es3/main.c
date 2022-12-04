//utilizzo di exec

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

    char *args[] = {"ls","-l","/usr/bin",NULL};
    int status;
    pid_t pid;

    pid = fork();
    if(pid == 0){
        execv("/bin/ls",args);
        //exit(1);
    }
    else if(pid > 0){
        wait(&status);
        printf("Il processo figlio %d ha terminato con status exit %d\n",pid,status);
        exit(0);
    }

}