/*
lanciare in background (&) il programma precedente e vedere con che pid gira
scrivere un programma che manda il segnale a questo processo con
kill(pid, SIGUSR1) ;
kill(pid, SIGUSR2) ;
oppure usare kill(1) da linea di comando:
    kill –USR1 pid  //si otterrà SIGUSR1
    kill –USR2 pid  //si otterrà SIGUSR2
    kill pid    //si sta mandando SIGTERM e con esso il processo termina perché tale segnale non è catturato e di default termina
*/
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sig_usr(int);

int main (void){
    signal(SIGUSR1, sig_usr);
    signal(SIGUSR2, sig_usr);

    pid_t padre = getpid();
    pid_t pid = fork();
    if(pid > 0) {
        while (1)
            pause();
    }
    else if(pid == 0){
        sleep(1);
        kill(padre,SIGUSR1);
        kill(padre,SIGUSR2);
        exit(1);
    }
}
void sig_usr(int signo) {
    if(signo == SIGUSR1)
        printf("SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("SIGUSR2\n");
    else printf("Segnale %d\n",signo);
}