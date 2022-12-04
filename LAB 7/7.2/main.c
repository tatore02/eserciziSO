/*
Dire cosa fa il seguente programma
 */

#include <stdio.h>
#include <unistd.h>

int main(){

        int j, ret;
        j = 10;
        ret = fork();
        printf("Child created \n");
        j = j * 2;
        if(ret == 0){
            j = j * 2;
            printf("The value of j is %d \n", j);
        }
        else {
            ret = fork();
            j = j * 3;
            printf("The value of j is %d \n", j);
        }
        printf("Done \n");
}
