//dire cosa stamperà in outout

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void exit1();
void exit2();

int main(void) {

    FILE *fp = fopen("prova.txt","w");

    fprintf(fp,"ciao");

    //fflush(fp);

    _exit(1);
}
void exit1() {
    printf("Sono il primo handler\n");
}
void exit2() {
    printf("Sono il secondo handler\n");
}
