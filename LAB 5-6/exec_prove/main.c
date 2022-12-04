#include <stdio.h>
#include <unistd.h>

//usare la exec per eseguire codice esterno

int main(){
    printf("Sono un processo con pid: %d\n",getpid());
    printf("Provo ad eseguire un codice esterno\n");

    execl("./esterno",NULL);

    printf("Sostituzione codice fallita\n");

    return 0;
}