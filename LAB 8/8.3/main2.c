/*
 Sia P un processo padre e F1 un processo figlio.
 Il processo figlio provvederà a testare l’esistenza
 di eventuali duplicati contenuti nel file NOMI.txt ed
 a comunicare tale esito al padre utilizzando il proprio exit status.
 Nel caso di esistenza di duplicati, il padre creerà un nuovo processo
 F2 che provvederà a cancellare tutti i duplicati.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int find_dup(char *);
void rem_dup(char *);
void compatta(char *, fpos_t,fpos_t);

int main(){

    pid_t pid = fork();
    if(pid == 0){
        if(find_dup("ELENCO.txt") == 1)
            exit(1);
        else
            exit(0);
    }
    else if(pid > 0){
        int status, status1;
        wait(&status1);
        status = WEXITSTATUS(status1);

        if(status == 1){
            puts("Duplicati trovati");

            pid = fork();
            if(pid == 0)
                rem_dup("ELENCO.TXT");
            else if(pid > 0)
                wait(NULL);
        }
        else{
            puts("Duplicati NON trovati");
        }
    }
    exit(1);
}

int find_dup(char *file){
    FILE *nomi;
    char nome1[255], nome2[255];
    fpos_t pos;
    int flag;

    nomi=fopen(file,"r");
    while(fscanf(nomi,"%s",nome1)!= EOF) {
        fgetpos(nomi,&pos);
        while(fscanf(nomi,"%s",nome2)!= EOF)
            if(strncmp(nome1,nome2,sizeof(nome1))==0) {
                flag = 1;
            }
        fsetpos(nomi,&pos);
    }
    return flag;
}


void rem_dup(char *file){
    FILE *nomi;
    char nome1[255], nome2[255];
    fpos_t pos, pos1, pos2;
    int test;

    nomi=fopen(file,"r");
    while(fscanf(nomi,"%s",nome1)!= EOF) {
        fgetpos(nomi,&pos);
        while(fscanf(nomi,"%s",nome2)!= EOF)
            if(strncmp(nome1,nome2,sizeof(nome1))==0) {
                fgetpos(nomi,&pos2);
                fseek(nomi,-(long)(strlen(nome2)+1),SEEK_CUR);
                fgetpos(nomi,&pos1);
                compatta("NOMI.txt",pos1,pos2);
                rewind(nomi);
                fsetpos(nomi,&pos1);
            }
        fsetpos(nomi,&pos);
    }
}

void compatta(char *file, fpos_t pos1, fpos_t pos2){
    FILE *nomi1, *nomi2;
    int c;
    long position;

    nomi1=fopen(file,"r+");
    nomi2=fopen(file,"r");
    fsetpos(nomi1,&pos1);
    fsetpos(nomi2,&pos2);

    while((c=fgetc(nomi2))!= EOF)
        fputc(c,nomi1);

    position=ftell(nomi1);
    truncate("NOMI.txt",position);
    return;
}