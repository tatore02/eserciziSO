//ESERCIZIO:
//Prendere un input da tastiera e scaricarlo in FILE1
//Copiare in ordine inverso il contenuto di FILE1 in FILE2
//utilizzando read e write

#include  <sys/types.h>
#include  <sys/stat.h>
#include   <fcntl.h>
#include   <unistd.h>
#include <stdlib.h>


int main()
{

  int  fdin, fdout, n;
  int  c, buf[90];


  if((fdin=open("FILE1",O_RDWR|O_CREAT|O_TRUNC,0644))<0)   //Crea FILE1  
    write(1,"FILE1 open error\n",17);             //in modalita' read-write
 
  if((fdout=open("FILE2",O_CREAT|O_RDWR|O_TRUNC,0644))<0) //Apre il file
    write(1,"FILE2 open error\n",17);    //in cui copiare in modalita' read-write
 
  n=read(STDIN_FILENO,buf,90);   //leggo da standard input
  write(fdin,buf,n);             //scrivo su FILE1

  n=lseek(fdin,-1,SEEK_END);        //mi posiziono alla fine di FILE1
 

  while ( n >= 0)  {
       read(fdin, &c, 1);
       write(fdout, &c, 1);
       n=lseek(fdin,-2,SEEK_CUR);
  }

  lseek(fdout,0,SEEK_SET);

  while ( read(fdout, &c, 1) > 0) 
          write(STDOUT_FILENO, &c, 1); 

  exit(0);
}
 
    






