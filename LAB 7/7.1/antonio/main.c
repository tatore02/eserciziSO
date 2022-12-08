/*
    Scrivere un programma che crei un processo zombie.
    Fare in modo che un processo figlio diventi figlio del processo init.

    Antonio Facchiano
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
    pid_t pid;
    int c;

    /* 2. Parent terminates before child: child gets init assigned as new parent */
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }

    /* Parent */
    if (pid != 0)
    {
        printf("[parent] terminating!\n");
        _exit(EXIT_SUCCESS);
    }

    /* Child */
    printf("[child] ppid = %d\n", getppid());

    return EXIT_SUCCESS;
}
