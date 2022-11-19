#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void charAtTime(char *);

int main(void){
    pid_t pid;
    pid = fork();
    if (pid==0)
        charAtTime("output dal figlio\n");
    else
        charAtTime("output dal padre\n");

    exit(0);
}
void charAtTime(char *str){
    char *ptr;
    int c;
    setbuf(stdout, NULL); /* set unbuffered */
    for (ptr = str;*ptr != '\0';ptr++){
        c = *ptr;
        putc(c, stdout);
    }
}