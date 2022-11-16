#include <unistd.h>
#include <stdio.h>

int main(){
 char *stringa="Uno alla volta?";
 setbuf(stdout,NULL);
 while (*stringa){
    putchar(*stringa++);
    sleep(1);  /* fermiamo il processo per un secondo */
}
 sleep(4);

}
