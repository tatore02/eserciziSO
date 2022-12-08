/*
Si assuma di avere nella cwd un file di nome file1
Scrivere un codice C che:
- scriva su standard output la parola “ordina”
- mandi in esecuzione il comando sort File1
- scriva su standard output la parola “fine”
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    printf("Ordina..\n");

    pid_t pid = fork();

    if(pid == 0){
        execl("/usr/bin/sort","sort","file1",NULL);
        exit(1);
    }
    else if(pid > 0){
        wait(NULL);
        printf("fine\n");
        exit(1);
    }

}
