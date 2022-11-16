/*
Sia ELENCO.TXT un file contenente dei record del tipo:
  Cognome \t Nome\n
Scrivere un programma che cancelli eventuali record duplicati
*/

#include <stdio.h>
#include <string.h>

struct data{
  char *nome;
  char *cognome;
};

int main(){
  FILE *fp1 = fopen("ELENCO.txt","r+");

  struct data array[100];

  int i=0;

  while(!feof(fp1)){
    fscanf(fp1,"%s %s",&array[i].nome,&array[i].cognome);
    //DEBUG
    printf("Nome: %s Cognome: %s\n",array[i].nome,array[i].cognome);
    i++;
  }


}
