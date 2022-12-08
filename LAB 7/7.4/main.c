/*
Scrivere un programma C, che usi la chiamata di sistema fork(), per
generare la successione di Fibonacci all’interno del processo figlio.
Il processo figlio produrrà anche le relative stampe.
Il padre dovrà rimanere in attesa tramite wait() fino alla terminazione del figlio.
Il numero di termini da generare sarà specificato a riga di comando.
Implementare i necessari controlli per garantire che il valore in ingresso sia un numero intero non negativo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int fibonacci(int );

int main(int argc,char *argv[]){

    if(argc != 2){
        printf("ERRORE: Inserire parametro\n");
        exit(1);
    }
    if(atoi(argv[1]) < 0){
        printf("ERRORE: Inserire parametro positivo\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    pid_t pid;
    pid = fork();

    if(pid == 0){
        for(int i=0;i < n+1;i++)
            printf("%d ",fibonacci(i));

        printf("\n");
        exit(1);
    }
    else if(pid > 0){
        wait(NULL);
        exit(1);
    }

}

int fibonacci(int n){
    if(n == 0)
        return 0;
    else if(n == 1)
        return 1;
    else
        return fibonacci(n-1) + fibonacci(n-2);

}