/*
Scrivere un programma che prende in input dall'utente il nome di un file ed esegue
(tramite fork+exec) un programma che restituisce all'utente l'elenco dei seguenti attributi del file:
● Tipo di file
● Permessi
● ID number del proprietario del file
● Dimensione del file (se regolare)
Alla fine dell'esecuzione il processo figlio comunicherà al padre
 l'esistenza o meno del file di cui testare le caratteristiche.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc,char *argv[]){
    if(argc != 2){
        perror("Inserire 2 parametri\n");
        exit(1);
    }

    pid_t pid = fork();
    if(pid == 0){
        execl("/bin/ls","ls","-l",argv[1],NULL);
        

    }
}