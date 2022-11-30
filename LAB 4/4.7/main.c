#include <stdio.h>

int main(){
    FILE *fp = fopen("ELENCO.txt","r");

    char c;
    char buffer[200];

    while(!feof(fp)){
        c = fgetc(fp);
        if(c == '!')
            ungetc('+',fp);
        else ungetc(c,fp);

        putchar(c);
    }
    fclose(fp);
}