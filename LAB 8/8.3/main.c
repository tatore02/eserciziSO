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
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define filename "ELENCO.txt"

int main(){

    FILE *fp = fopen(filename,"r");

    bool flag = false;
    pid_t pid = fork();

    if(pid == 0){
        char line1[100], line2[100];
        fpos_t pos;
        fpos_t pos1,pos2;
        int i=0;    //per iterare il fpos_t vett[10]
        while(fscanf(fp,"%s",line1) != EOF){
            fgetpos(fp,&pos);
            while(fscanf(fp,"%s",line2) != EOF){
                if(strcmp(line1,line2) == 0){
                    fgetpos(fp,&pos2);   //fine stringa dupl
                    fseek(fp,-(long)(strlen(line2) +1),SEEK_CUR);
                    fgetpos(fp,&pos1);   //inizio stringa dupl

                    fsetpos(fp,&pos2);  //riporto il puntatore
                                        //a fine stringa
                    ...

                    flag = true; //esistono duplicati
                }
            }
            fsetpos(fp,&pos); //resetto il puntatore a file
                             //dopo il while interno
        }

        if(flag == true)
            exit(1);
        else
            exit(0);
    }
    else if(pid > 0){
        sleep(1);   //per essere sicuri che venga eseguito
                    //prima il figlio
        int status;
        wait(&status);
        if(status == 1){    //esistono duplicati
            pid_t figlio2 = fork();
            if(figlio2 == 0){

            }
        }
        else if(status == 0){
            printf("Non esistono duplicati in %s\n",filename);
        }
    }
    exit(1);
}