//dire cosa stamperà in outout

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void exit1();
void exit2();

int main(void) {
    int pid;
    char array[]="Dopo\n";
    atexit(exit1);
    printf("Prima");
    pid=fork();
    if(pid==0) {
        atexit(exit2);
        printf("Sono il figlio");
        write(1,array,5);
        exit(0);
    }
    wait(NULL);
    printf("Sono il padre\n");
    write(1,array,5);
    printf("Fine esecuzione");
    _exit(0);
}
void exit1() {
    printf("Sono il primo handler\n");
}
void exit2() {
    printf("Sono il secondo handler\n");
}