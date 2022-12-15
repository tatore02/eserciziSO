/*
Sia S un processo server che effettua semplici operazioni aritmetiche
e C un processo figlio di S (client) che prende in input i due operandi
e l'operatore e li invia al server per ottenere il risultato.
La comunicazione da Client a Server sarà effettuata tramite pipe
mentre il risultato elaborato da S sarà mostrato su standard output
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){

    int fdPipe[2];
    pipe(fdPipe);

    int op1;
    int op2;
    char operatore;

    pid_t pid = fork();
    if(pid == 0){
        close(fdPipe[0]);
        puts("Inserire calcolo:");
        scanf("%d %c %d",&op1,&operatore,&op2);

        write(fdPipe[1],&op1,sizeof(int));
        write(fdPipe[1],&op2,sizeof(int));
        write(fdPipe[1],&operatore,sizeof(char)*2);

        exit(1);
    }
    close(fdPipe[1]);
    read(fdPipe[0],&op1,sizeof(int));
    read(fdPipe[0],&op2,sizeof(int));
    read(fdPipe[0],&operatore,sizeof(char)*2);

    if(operatore == '+')
        printf("Risultato: %d\n",(op1+op2));
    else if(operatore == '-')
        printf("Risultato: %d\n",(op1-op2));
    else if(operatore == '*')
        printf("Risultato: %d\n",(op1*op2));
    else if(operatore == '/')
        printf("Risultato: %d\n",(op1/op2));

    wait(NULL);
    exit(1);
}