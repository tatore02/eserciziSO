#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main () {
    int pid, status;
    int myvar = 1;
    if ((pid = fork()) < 0){
        perror("fork error");
        exit(1);
    }

    if(pid==0){
        sleep(2);
        myvar = 2;
        printf("Figlio: sono il processo %d e sono figlio di %d \n",getpid(),getppid());
        printf("myvar: %d \n", myvar);
        exit(1);
    }
    else{
        wait(&status);
        printf("Padre: sono il processo %d e sono figlio di %d \n",getpid(),getppid());
        printf("Padre: status = %d \n", WEXITSTATUS(status));
        printf("myvar: %d \n", myvar);
    }
}
