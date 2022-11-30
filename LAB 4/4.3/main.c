/*
Sia ELENCO.TXT un file contenente dei record del tipo:
Cognome \t Nome\n
Scrivere un programma che cancelli eventuali record duplicati
*/

#include <stdio.h>
#include <string.h>


int main(){
  FILE *fp1 = fopen("ELENCO.txt","r+");

  int i,j;
  char line1[50];
  char line2[50];

  for(i=0;i<4;i++){

      for(j=0;j<=i;j++)
        fscanf(fp1,"%s\n",line1);

      while(!feof(fp1)){
        fscanf(fp1,"%s\n",line2);
        if(strcmp(line1,line2) == 0) {

        }
      }
      rewind(fp1);
  }

}
