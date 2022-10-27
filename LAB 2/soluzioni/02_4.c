//ESERCIZIO:
//Copiare il contenuto di un file in un altro
//utilizzando esclusivamente read da standard input e write su 
//standard output

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{

  int  fdin, fdout, dupin, dupout, c;


  if((fdin=open("FILE1",O_RDONLY))<0) //Apre il file da copiare  
    printf(" infile open error\n");             //in modalita' read-only 
 
  if((fdout=open("FILE2",O_CREAT|O_WRONLY|O_TRUNC,0644))<0) //Apre il file
    printf("outfile open error\n");    //in cui copiare in modalita' write-only
 
  if((dupin=dup2(fdin,STDIN_FILENO))<0)   //assegna 0 a fdin e chiude
    printf("dupin error\n");             //STDIN_FILENO
 
  if((dupout=dup2(fdout,STDOUT_FILENO))<0)   //assegna 1 a fdout e chiude 
    printf("dupout error\n");               //STDOUT_FILENO

  //Ora lo standard input/output e' ridiretto verso fin/fout
  //per cui si possono utilizzare le funzioni read(0,..) e write(1,...)
  //per copiare il file
 
  while ( read(STDIN_FILENO, &c, 1) > 0) 
          write(STDOUT_FILENO, &c, 1); 


printf("Copia terminata\n");
  exit(0);
}
 
    






