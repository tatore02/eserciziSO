#include <stdio.h>
#include <unistd.h>

//usare la exec per eseguire un commando da shell

int main(){
    printf("Eseguiamo la ls:\n");
    execl("/bin/ls","-l",NULL);

    printf("ls fallita\n");
}