//PROVA: comunicazione tra fratelli

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    pid_t pid1,pid2;
    pid1 = fork();
    if(pid1 > 0)
        pid2 = fork();

    int fdPipe[2];
    pipe(fdPipe);

    if(pid1 == 0){
        close(fdPipe[0]);
        write(fdPipe[1],"ciao\n",5);
        exit(1);
    }
    else if(pid2 == 0){
        close(fdPipe[1]);
        char risposta[5];
        read(fdPipe[0],&risposta,sizeof(risposta));
        printf("%s\n",risposta);
        exit(1);
    }

    wait(NULL);
    wait(NULL);
    exit(1);
}
