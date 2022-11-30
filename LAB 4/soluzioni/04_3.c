#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int find_dup(char *file);
void rem_dup(char *file);
void compatta(char *file, fpos_t pos1, fpos_t pos2);

int main(void){
    int nomi, pid, stato, stato1;
    rem_dup("NOMI.txt");
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


