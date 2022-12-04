#include <stdio.h>
#include <unistd.h>

//codice esterno

int main(){
    printf("Codice esterno\n");
    printf("Pid del processo: %d\n",getpid());
}