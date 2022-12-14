/*
Scrivere un programma in linguaggio C che in sequenza:
a) crei 2 pipe e un figlio (le 2 pipe saranno utilizzate per una comunicazione
    bidirezionale tra padre e figlio);
b) dopo la creazione del figlio, il padre prenda in input dall’utente una stringa e la
    invii al figlio utilizzando la prima pipe; dopo aver ricevuto le risposte del figlio, le
    stampi e completi la sua esecuzione;
c) faccia controllare al figlio se esista una directory nella current working directory
    con lo stesso nome (si utilizzino le system call che permettono di leggere il contenuto
    di una directory) ed invii al padre tale informazione.
 */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

    int dadToSon[2];
    int sonToDad[2];

    pipe(dadToSon);
    pipe(sonToDad);

    char nome[20];
    char risposta[6];

    struct stat buf;
    struct dirent *d_struct;
    DIR *d;

    pid_t pid = fork();
    if(pid == 0){
        close(sonToDad[0]);
        close(dadToSon[1]);

        read(dadToSon[0],nome,sizeof(nome));

        d = opendir(".");
        while((d_struct = readdir(d)) != NULL){
            if(strcmp(d_struct->d_name,nome) == 0){
                lstat(d_struct->d_name,&buf);

                if(S_ISDIR(buf.st_mode)){
                    printf("Directory %s trovata\n",d_struct->d_name);
                    write(sonToDad[1],"Si",3);

                    read(dadToSon[0],risposta,sizeof(risposta));
                    if(strcmp(risposta,"Conta") == 0){
                        int count = 0;
                        d = opendir(nome);
                        chdir(nome);
                        while((d_struct = readdir(d)) != NULL){
                            lstat(d_struct->d_name,&buf);
                            if(S_ISREG(buf.st_mode))
                                count++;
                        }
                        write(sonToDad[1],&count,sizeof(int));
                    }
                }
                else
                    write(sonToDad[1],"NO",3);
            }
        }
        exit(1);
    }

    close(dadToSon[0]);
    close(sonToDad[1]);

    printf("Inserire una stringa: ");
    scanf("%s",nome);

    write(dadToSon[1],nome,sizeof(nome));
    printf("Faccio cercare una directory %s a mio figlio\n",nome);
    read(sonToDad[0],risposta,3);

    printf("La risposta del figlio è stata %s\n",risposta);

    if(strcmp(risposta,"Si") == 0){
        write(dadToSon[1],"Conta",6);
        int count;
        read(sonToDad[0],&count,sizeof(int));
        printf("Il figlio ha contato ben %d file\n",count);
    }
    else if(strcmp(risposta,"NO") == 0){
        printf("La directory %s non esiste\n",nome);
    }

    wait(NULL);
    exit(1);
}