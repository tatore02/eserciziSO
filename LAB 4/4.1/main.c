/*
Risolvere l'esercizio dell'inversione di un file
utilizzando gli stream e le funzioni di I/O che
leggono o scrivono un carattere alla volta.
*/

#include <stdio.h>

int main(){
    FILE *fp1 = fopen("copia.txt","r");
    FILE *fp2 = fopen("incolla.txt","w+");

    int n;

    fseek(fp1,-1,SEEK_END);

    char c;
    while(ftell(fp1) >= 0){
        c = getc(fp1);
        putc(c,fp2);
        if(fseek(fp1,-2,SEEK_CUR) != 0)
            break;
    }
}
