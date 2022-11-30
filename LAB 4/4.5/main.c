#include <stdio.h>
#include <ctype.h>

int main(){
    FILE *fp = fopen("ELENCO.txt","r");

    char c;
    while((c = fgetc(fp)) != EOF){
        c = toupper(c);
        putchar(c);
    }

    fclose(fp);
}