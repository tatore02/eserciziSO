/*
scrivere un programma che intercetta il ctrl-C
 da tastiera (SIGINT) e gli fa stampare un messaggio.
 */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void func(int sig);

int main(){
    while(1)
    signal(SIGINT,func);
}

void func(int sig){
    puts("\nCiao mondo");
    exit(1);
}