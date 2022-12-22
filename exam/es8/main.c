/*
Scrivere un programma in linguaggio C che in sequenza:
crei 2 pipe e un figlio (le 2 pipe saranno utilizzate per una comunicazione bidirezionale tra padre
e figlio);
il padre, dopo la creazione del figlio, prenda in input dall'utente il nome di un file;
invii al figlio il nome del file utilizzando la prima pipe;
faccia controllare al figlio se il file è contenuto nella current working directory e comunichi tale
informazione al padre utilizzando la seconda pipe;
in caso affermativo comunichi al padre anche il numero di vocali presenti nel file;
faccia stampare al padre le informazioni ricevute dal figlio.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <fcntl.h>
#include <ctype.h>

int contaVocali(char *);
int isVocal(char );

int main(){
    int sonToDad[2];
    int dadToSon[2];

    pipe(sonToDad);
    pipe(dadToSon);

    struct dirent *dir;
    DIR *d;
    struct stat buf;

    pid_t pid;

    pid = fork();
    if(pid == 0){
        close(dadToSon[1]);
        close(sonToDad[0]);

        char input[9];
        read(dadToSon[0],input,sizeof input);
        printf("DEBUG: %s\n",input);

        bool flag = false;
        int count = 0;

        char fullPath[255];
        getcwd(fullPath,255);
        d = opendir(fullPath);

        while((dir = readdir(d)) != NULL){
            if(strcmp(dir->d_name,input) == 0){
                write(sonToDad[1],"SI",3);
                flag = true;
            }
        }
        if(flag == false)
            write(sonToDad[1],"NO",3);


        char risposta[7];
        read(dadToSon[0],&risposta,sizeof risposta);
        if(strcmp(risposta,"VAI") == 0){
            if(lstat(input,&buf) == -1) {
                if (stat(input, &buf) == -1) {
                    perror("stat");
                    exit(1);
                }
            }
            if(S_ISREG(buf.st_mode))
                count = contaVocali(input);

            write(sonToDad[1],&count,sizeof count);
        }
        exit(1);
    }
    else if(pid > 0){
        close(dadToSon[0]);
        close(sonToDad[1]);
        char input[] = "ciao.txt";


        write(dadToSon[1],input,sizeof(char) * strlen(input));

        char risposta[3];
        read(sonToDad[0],&risposta,sizeof risposta);

        if(strcmp(risposta,"SI") == 0){
            write(dadToSon[1],"VAI",4);
            int count;
            read(sonToDad[0],&count,sizeof count);

            printf("Vocali nel file %s: %d\n",input,count);
        }
        else{
            write(dadToSon[1],"NO VAI",7);
            printf("File %s non trovato\n",input);
        }

        wait(NULL);
        exit(1);
    }
}

int contaVocali(char *pathname){
    int count = 0;

    int fd = open(pathname,O_RDONLY);
    char c;
    while(read(fd,&c,1) > 0){
        if(isVocal(c))
            count++;
    }
    return count;
}

int isVocal(char c){
    c = tolower(c);
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return 1;
    else return 0;
}