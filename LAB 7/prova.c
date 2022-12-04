#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void sig_usr(int);

int main(){
    signal(SIGUSR1, sig_usr);
    signal(SIGUSR2, sig_usr);
    while(1)
        pause();
}
void sig_usr(int signo){
    if(signo == SIGUSR1)
        printf("SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("SIGUSR2\n");
    else printf("Segnale %d\n",signo);
}