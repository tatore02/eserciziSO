/*
Scrivere uno programma che crea due processi figlio,
il padre legge i caratteri dal file Input.txt e li passa 2 alla volta al primo figlio.
 Questo passa il primo carattere al secondo figlio
 solo se primo e secondo carattere sono uguali.
 Il secondo figlio stamperà i caratteri ricevuti in Output.txt
 */

//NON FUNZIONA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int dadToSon[2];
    int sonToDad[2];
    pipe(dadToSon);
    pipe(sonToDad);

    pid_t pid1 = fork();
    if(pid1 == 0){
        close(dadToSon[1]);
        close(sonToDad[0]);

        char out[2];
        read(dadToSon[0],out,2);
        if(out[0] == out[1])
            write(sonToDad[1],&out[0],1);
        exit(1);
    }
    else if(pid1 > 0){
        close(dadToSon[0]);
        close(sonToDad[1]);

        int fd = open("input.txt",O_RDONLY);
        char inp[2];

        if(read(fd,inp,2) > 0)
            write(dadToSon[1],inp,2);

        char c;
        read(sonToDad[0],&c,1);                   //ricevo il carattere dal figlio 1
        write(dadToSon[1],&c,1);    //mando il carattere al figlio 2

        //al padre faceva stampare il carattere, al secondo figlio no :(

        pid_t pid2 = fork();
        if(pid2 == 0){
            close(sonToDad[0]);
            close(sonToDad[1]);
            close(dadToSon[1]);

            char x;
            read(dadToSon[0],&x,1);
            printf("%c\n",x);
            exit(1);
        }
    }
    wait(NULL);
    wait(NULL);
    exit(1);
}