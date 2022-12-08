//elimina gli spazi all'inizio di
//una frase in un file

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void elimina_spazio(char *,int );

int main(){
    FILE *fp1 = fopen("ELENCO.txt","r+");

    char *buf;
    buf = calloc(200,sizeof(char));
    char c;
    int i=0;

    while(!feof(fp1)){
        c = fgetc(fp1);
        buf[i] = c;
        i++;
    }
    fclose(fp1);

    printf("%s\n",buf);

    int lung = strlen(buf);

    for(i=0;i<lung;i++)
        if(buf[i] == ' ') {
            elimina_spazio(buf, i);
            lung--;
        }

    printf("%s\n",buf);
    /*
    fp1 = fopen("ELENCO.txt","w");
    fprintf(fp1,"%s",buf);
    fclose(fp1);
    */
    return 0;
}

void elimina_spazio(char *str,int i){
    for(int j=i;j<strlen(str);j++){
        str[j] = str[j+1];
    }
}
