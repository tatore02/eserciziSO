//zombie

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();
    if(pid == 0){
        printf("PID del figlio: %d\n",getpid());
        exit(0);
    }
    sleep(2);
    system("ps -T");
    exit(0);
}
