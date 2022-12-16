/*
Scrivere un programma che crea due processi figli,
il primo figlio stamperà il listing (ls -l) della directory corrente
 in un file passato come parametro;
 il secondo figlio aprirà quel file stampandone il contenuto in STDOUT.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char *argv[]){
    if(argc != 2){
        puts("Inserire 2 parametri");
        exit(1);
    }

    int fd;

    pid_t pid1,pid2;
    pid1 = fork();
    if(pid1 == 0){
        fd = open(argv[1],O_RDONLY | O_CREAT | O_TRUNC,0644);
        dup2(fd,STDOUT_FILENO);
        execl("/bin/ls","ls","-l",NULL);
        exit(1);
    }

    else if(pid1 > 0){
        sleep(1);
        pid2 = fork();
        if(pid2 > 0){
            fd = open(argv[1],O_RDONLY);
            char c;
            while(read(fd,&c,1) > 0)
                write(1,&c,1);
            exit(1);
        }
    }

    wait(NULL);
    wait(NULL);
    exit(1);
}
