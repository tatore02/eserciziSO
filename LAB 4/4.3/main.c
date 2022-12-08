/*
Sia ELENCO.TXT un file contenente dei record del tipo:
Cognome \t Nome\n
Scrivere un programma che cancelli eventuali record duplicati
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void rimuovi(char **lista,int ,int*);
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
  int tagliaLista = i;

  fclose(fp1);

  for(int j=0;j < tagliaLista-1;j++){
      for(int k = j+1;k<tagliaLista;k++){
          if(strcmp(lista[j],lista[k]) == 0){
                rimuovi(lista,k,&tagliaLista);
          }
      }
  }

  /*
  for(int j=0;j < tagliaLista;j++)
    printf("%s\n",lista[j]);
  */



  FILE *fp2 = fopen("ELENCO.txt","w");

  for(int j=0;j < tagliaLista;j++)
      fprintf(fp2,"%s\n",lista[j]);

  fclose(fp2);
}
//metto la stringa doppia in fondo alla lista
void rimuovi(char **lista,int pos,int *taglia){
    *(taglia) += -1;    //decremento la variabile della taglia della lista

    for(int i = pos; i < *taglia;i++){
        swap(lista,i,i+1);
    }
}

void swap(char **lista,int x,int y){
    char *tmp = lista[x];
    lista[x] = lista[y];
    lista[y] = tmp;
}
