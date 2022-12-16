/*
Si scriva un programma in linguaggio C per ambiente Unix che realizza un
meccanismo di mailbox tra due processi. Le caselle di posta dei due processi sono
costituite da due file chiamati mail1.txt e mail2.txt che si riferiscono rispettivamente al
processo 1 e al processo 2. Il processo 1 deve leggere una stringa di 5 caratteri da
tastiera, mettere tale stringa nella mailbox del processo 2 (il file mail2.txt) e avvisare il
processo 2, mediante un segnale SIGUSR1, che gli è stata inviata della posta. II
processo 2 deve leggere la posta, invertire l'ordine dei caratteri nella stringa (il primo
carattere diventa l'ultimo mentre l'ultimo diventa il primo e così via) e mettere la stringa
invertita nella mailbox del processo 1 (il file mail1.txt).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

void funct();

void swap(char *a,char *b);
void reverse(char *,int,int);

int main(){
    creat("mail1.txt",0644);
    creat("mail2.txt",0644);

    pid_t pid = fork();
    if(pid == 0){
        signal(SIGUSR1,funct);
        pause();
        char buffer[5];
        int fd1 = open("mail1.txt",O_WRONLY);
        int fd2 = open("mail2.txt",O_RDONLY);
        read(fd2,buffer,sizeof buffer);
        reverse(buffer,0, strlen(buffer)-1);
        write(fd1,buffer,sizeof buffer);

        close(fd1);
        close(fd2);
        exit(1);
    }

    char buffer[50];
    while(strlen(buffer) != 5){
        printf("Inserire una stringa di 5 caratteri: ");
        scanf("%s",buffer);
    }
    int fd = open("mail2.txt",O_WRONLY);
    write(fd,buffer,sizeof(char) * strlen(buffer));
    close(fd);
    kill(pid,SIGUSR1);

    wait(NULL);
    exit(1);
}

void funct(){
    printf("Segnale ricevuto\n");
}

void swap(char *a,char *b){
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse(char *str,int start,int end){
    if(start < end){
        swap(&str[start],&str[end]);
        reverse(str,++start,--end);
    }
    else return;
}
