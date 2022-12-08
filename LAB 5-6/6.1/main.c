/*
Scrivere un programma che effettui la copia di un file utilizzando 2 figli:
uno specializzato nella copia delle vocali ed uno nella copia delle consonanti.
Per la sincronizzazione tra i processi figli utilizzare un semaforo
implementato tramite file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

void swap(pid_t a,pid_t b){
  if(a == 0){
    a = 1;
    b = 0;
  }
  else if(b == 0){
    b = 1;
    a = 0;
  }
}

int main(){
  int fd1 = open("copia.txt",O_RDONLY);
  int fd2 = open("incolla.txt",O_WRONLY | O_CREAT | O_TRUNC,0644);

  pid_t t1;
  pid_t t2;

  t1 = fork();
  //creazione secondo figlio tramite genitore
  if(t1 > 0){
    t2 = fork();
  }
  //tot processi: 3

  if(t1 == 0 || t2 == 0){
      printf("Sono il processo %d figlio di %d\n",getpid(),getppid());
  }
}
