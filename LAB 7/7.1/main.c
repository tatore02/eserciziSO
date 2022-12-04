/*
Scrivere un programma che crei un processo zombie.
Fare in modo che un processo figlio diventi figlio del processo init.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

    pid_t pid;
    int status;

    pid = fork();
    if(pid == 0){
        printf("Sono il processo figlio %d del genitore: %d\n",getpid(),getppid());
        //exit(1);
    }
    else if(pid > 0){
        execl("/usr/bin","ps",NULL);
        printf("Sono il genitore %d\n",getpid());
    }
}