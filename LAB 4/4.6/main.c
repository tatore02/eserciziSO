#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
    FILE *fp1 = fopen("ELENCO.txt","r");

    char c;
    char *vettore = calloc(200,sizeof(char));
    while((c = fgetc(fp1)) != EOF){
        c = toupper(c);
        strcat(vettore,&c);
    }

    fclose(fp1);

    FILE *fp2 = fopen("ELENCO.txt","w");

    for(int i=0;vettore[i] != '\0';i++){
        fputc(vettore[i],fp2);
    }

    fclose(fp2);
}