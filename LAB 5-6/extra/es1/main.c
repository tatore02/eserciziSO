/*
Esercizio 5: Il processo figlio crea un nuovo file (il cui nome deve essere specificato come argomento),
 il processo padre attende il completamento del figlio e successivamente legge il contenuto del file.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

    pid_t pid;
    int fd;
    char vett[10];
    int n = 1;

    pid = fork();
    if(pid < 0){
        fprintf(stderr,"error fork");
        exit(0);
    }

    //processo figlio
    if(pid == 0){
        if((fd = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC,0644)) < 0){
            fprintf(stderr,"error open first file");
            exit(0);
        }
        char str[20];
        printf("Inserire stringa: ");
        scanf("%s",str);

        char *c;
        c = str;

        while(*c != '\0'){
            if(write(fd,c,1) < 0) {
                fprintf(stderr,"error write");
                exit(0);
            }else c++;
        }
        exit(1);
    }
    else{   //processo padre
        wait(NULL);

        lseek(fd,0,SEEK_SET);
        char c;
        int i=0;
        while(read(fd,&c,1) > 0){
            write(STDOUT_FILENO,&c,1);
        }
        printf("Il figlio ha scritto: %s\n",vett);
        close(fd);
    }
    exit(0);
}
