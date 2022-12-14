/*
Scrivere un programma in linguaggio C che prenda come parametro sulla riga di
comando il nome di un file e stampi il numero di vocali contenute nel file.
Si supponga di compilare tale programma e di assegnargli il nome CONTA_VOCALI

Successivamente scrivere un secondo programma in linguaggio C che in sequenza:
• crei 1 pipe e un figlio;
• dopo la creazione del figlio, prenda in input dall’utente un nome di file;
• lo invii al figlio con la pipe ed attenda la sua terminazione;
• faccia eseguire al figlio, utilizzando una delle funzioni exec,
 il comando “CONTA_VOCALI” utilizzando come argomento il nome del file.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(){
    int fdPipe[2];
    pipe(fdPipe);

    pid_t pid = fork();
    if(pid > 0){
        close(fdPipe[0]);

        char filename[100];
        printf("Inserire nome file: ");
        scanf("%s", filename);

        write(fdPipe[1],filename,sizeof(filename));
    }
    else if(pid == 0){
        close(fdPipe[1]);

        char risposta[100];
        read(fdPipe[0],risposta,sizeof(risposta));

        char curDir[255];
        getcwd(curDir,255);
        strcat(curDir,"/CONTA_VOCALI.out");
        execl(curDir,"CONTA_VOCALI.out",risposta,NULL); //FAI VEDERE AD ANTONIO
        exit(1);
    }

    wait(NULL);
    exit(1);
}
