#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int vocale(char );

int main(int argc,char *argv[]){
    if(argc != 3){
        printf("Errore numero parametri\n");
        exit(1);
    }

    int child1 = 0;
    int child2 = 0;

    int fd1, fd2, fs;

    char buf1[20], buf2[20];
    char a,b;

    char cons = '1';
    char voca = '2';

    char check1;
    char check2;

    int count1 = 0;
    int count2 = 0;

    fd1 = open(argv[1],O_RDONLY,0644);
    fd2 = open(argv[2],O_RDWR | O_CREAT | O_TRUNC,0644);
    fs = open("semaforo",O_RDWR,0644);

    if(fork() == 0){
        child1 = 1;
    }else{
        if(fork() == 0){
            child2 = 1;
        }
    }

    //il primo figlio legge le vocali
    if(child1 == 1){
        printf("Sono nel primo figlio\n");
        while((read(fd1,&a,1)) == 1){
            if(vocale(a))
                buf1[count1] = a;
            count1++;
        }
        for(int i=0;i<count1;i++){
            if(buf1[1] != '\0') {
                a = buf1[i];
                write(fd2,&a,1);
            }

            while(check1 == '1'){
                lseek(fs,0,SEEK_SET);
                read(fs,&a,1);
                check1 = a;
                sleep(1);
            }

            lseek(fs,0,SEEK_SET);
            write(fs,&cons,1);

        }
    }
    else if(child2 == 1){
        printf("Sono nel secondo figlio\n");
        while((read(fd2,&b,1)) == 1){
            if(!vocale(b))
                buf2[count2] = b;
            count2++;
        }
        for(int i=0;i<count2;i++){
            if(buf2[1] != '\0') {
                b = buf2[i];
                write(fd2,&b,1);
            }

            lseek(fs,0,SEEK_SET);
            write(fs,&voca,1);

            while(check2 == '0'){
                //se nel semaforo sto leggendo 0 allora è il turno di una vocale, aspetto
                lseek(fs,0,SEEK_SET);
                read(fs,&b,1);
                check2 = b;
                sleep(1);
            }
        }
    }
    else{
        printf("Sono nel padre\n");
        sleep(5);
        exit(0);
    }


    exit(0);
}

int vocale(char c){
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return 1;
    else return 0;
}
