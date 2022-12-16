/*
a) crei 2 pipe e un figlio (le 2 pipe saranno utilizzate per una comunicazione
bidirezionale tra padre e figlio);
b) dopo la creazione del figlio, il padre prenda in input dall’utente una stringa e la
invii al figlio utilizzando la prima pipe; dopo aver ricevuto le risposte del figlio, le
stampi e completi la sua esecuzione;
c) faccia controllare al figlio se esista una directory nella current working directory
con lo stesso nome (si utilizzino le system call che permettono di leggere il
contenuto di una directory) ed invii al padre tale informazione.
d) Nel caso la directory esista, faccia contare al figlio il numero di file standard
contenuti ed invii al padre la risposta;
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>

int main(){

    int sonToDad[2];
    int dadToSon[2];

    pipe(sonToDad);
    pipe(dadToSon);

    struct dirent *dir;
    DIR *d;
    struct stat buf;

    pid_t pid1,pid2;
    pid1 = fork();
    if(pid1 == 0){
        close(sonToDad[0]);
        close(dadToSon[1]);

        char buffer[20];
        read(dadToSon[0],buffer,sizeof buffer);
        printf("Messagio ricevuto dal padre: %s\n",buffer);

        d = opendir(".");
        while((dir = readdir(d)) != NULL){
            if(strcmp(dir->d_name,buffer) == 0)
                lstat(buffer,&buf);
        }
        bool flag = false;
        if(S_ISDIR(buf.st_mode))
            flag = true;

        write(sonToDad[1],&flag,sizeof flag);

        exit(1);
    }
    else if(pid1 > 0){
        close(sonToDad[1]);
        close(dadToSon[0]);

        char buffer[20];
        printf("Inserire cartella da cercare: ");
        scanf("%s",buffer);
        write(dadToSon[1],buffer,sizeof buffer);

        bool flag = false;
        read(sonToDad[0],&flag,sizeof flag);
        if(flag == true) {
            char fullPath[255];
            getcwd(fullPath,sizeof fullPath);
            strcat(fullPath,"/");
            strcat(fullPath,buffer);
            chdir(fullPath);
            d = opendir(".");

            int count = 0;
            while((dir = readdir(d)) != NULL)
                if(lstat(dir->d_name,&buf) != -1)
                    if(S_ISREG(buf.st_mode))
                        count++;

            printf("Numero di file regolari %d\n",count);
        }
        wait(NULL);
        exit(1);
    }

}