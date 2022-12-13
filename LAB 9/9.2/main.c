/*
Un processo P1 crea una pipe e un figlio F1.
Un secondo processo P2 comunicherà con P1 tramite un file TEMP.
P2 ogni secondo genera un numero casuale da 1 a 100 e lo scrive
nel FILE seguito dal proprio pid.
 P1 dopo 20 secondi dalla creazione
 del figlio scrive nella pipe il pid di P2, seguito dal numero -1,
 poi stampa un messaggio sullo schermo e termina la sua esecuzione.
 Durante questi 20 secondi P1 leggerà i numeri nel file TEMP
 e scriverà sulla pipe il suo pid con il numero che ha letto.
 F1 leggerà dalla pipe i pid seguiti dal numero.
 Se il numero è -1 ucciderà P2 e poi terminerà;
 altrimenti stamperà al terminale il proprio pid seguito dal numero che ha letto.
*/

#include <sdtio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int fd[2];
    pipe(fd);

    int file = open("tmp.txt",O_RDWR | O_CREAT | O_TRUNC,0644);

    pid_t f1,p2;

    f1 = fork();

    if(f1 > 0)
        p2 = fork();


    if(p2 == 0){
        int randNum = (rand() % 100) + 1;
        char str[10];
        sprintf(str, "%d %d ", randNum, getpid());
        lseek(file,0,SEEK_SET);
        write(file, str, strlen(str));
        sleep(1);
    }
    else if(p2 > 0){
        char numberRead[3];
        int n;
        n = read(file,numberRead,3);

        close(fd[0]);
        write(fd[1],numberRead,n);
    }
    else if(f1 == 0){
        close(fd[1]);
        char *buf
        read(fd[0],buf,3);
        int number = atoi(buf);
        if(number == -1){
            kill(p2,SIGKILL);
            exit(1);
        }
        else
            printf("pid: %d number: %d\n",getpid(),number);

    }


}