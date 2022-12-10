/*
Scrivere un programma che:
prenda in input il nome di un file di testo
crei due figli che comunicano tramite pipe
il primo figlio esegue cat file e manda l’output al fratello tramite la pipe
il secondo figlio visualizza a video le informazioni ricevute dalla pipe con il comando more
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[]){

    if(argc != 2){
        printf("ERRORE: inserire parametro\n");
        exit(1);
    }

    int fd[2];

    pid_t pid1,pid2;

    pipe(fd);

    pid1 = fork();
    if(pid1 == 0) {
        close(fd[0]);
        dup2(fd[1],1);
        execl("/bin/cat", "cat",argv[1],NULL);
        exit(1);
    }
    else if(pid1 > 0){
        wait(NULL);
    }

    pid2 = fork();
    if(pid2 == 0) {
        close(fd[1]);
        dup2(fd[0],0);
        execl("/bin/more","more",NULL);
        exit(1);
    }
    else if(pid2 > 0){
        wait(NULL);
    }

    exit(0);
}