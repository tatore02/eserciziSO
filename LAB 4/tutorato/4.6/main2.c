#include <stdio.h>
#include <ctype.h>

int main(){
    FILE *fp = fopen("ELENCO.txt","r+");

    char c;
    while((c = fgetc(fp) != EOF){
       if(fseek(fp,-1,SEEK_CUR) == -1)
           return 0;
        fputc(toupper(c),fp);
    }
    fclose(fp);
    return 0;
}