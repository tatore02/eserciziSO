/*
Sia ELENCO.TXT un file contenente dei record del tipo:
Cognome \t Nome\n
Scrivere un programma che cancelli eventuali record duplicati
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(char **,int,int);

int main(){
    FILE *fp1 = fopen("ELENCO.txt","r");

    char *lista[20];
    char buffer[50];

    int i=0;

    while(!feof(fp1)){
        fscanf(fp1,"%s\n",buffer);
        lista[i] = calloc(strlen(buffer),sizeof(char));
        strcat(lista[i],buffer);
        i++;
    }

    fclose(fp1);

    for(int j=0; j < i-1;j++){
        for(int k = j+1; k < i;k++){
            if(strcmp(lista[j],lista[k]) > 0){
                swap(lista,j,k);
            }
        }
    }

    FILE *fp2 = fopen("ELENCO.txt","w");

    for(int j=0;j < i;j++)
        fprintf(fp2,"%s\n",lista[j]);

    fclose(fp2);
}


void swap(char **lista,int x,int y){
    char *tmp = lista[x];
    lista[x] = lista[y];
    lista[y] = tmp;
}
