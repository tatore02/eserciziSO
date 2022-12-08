#include <stdio.h>

int main(){
    FILE *fp1 = fopen("ELENCO.txt","r");
    FILE *fp2 = fopen("RISULTATO.txt","w");

    char c;
    char buffer[255];

    while(!feof(fp1)){
        c = getc(fp1);
        if(c == '!')
            ungetc('+',fp1);
        else ungetc(c,fp1);

        fgets(buffer,255,fp1);
        fputs(buffer,stdout);   //su terminale
        fputs(buffer,fp2);      //su file
    }

    fclose(fp1);
    fclose(fp2);
}