/*
Creare un file FILE1 contenente un buco
(far stampare il contenuto del file col buco con "od –c" e "cat"
Copiare il contenuto di FILE1 in un file FILE2 eliminando il buco
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h> 



int main()
{

  int  fdin, fdout, n;
  char  c, buf1[]="Prima del buco", buf2[]="Dopo il buco";

  fdin=open("FILE1", O_RDWR|O_CREAT|O_TRUNC,0644);
  fdout=open("FILE2", O_RDWR|O_CREAT|O_TRUNC,0644);

  write(fdin,buf1,sizeof(buf1)-1);
  lseek(fdin,20,SEEK_CUR);
  write(fdin,buf2,sizeof(buf2)-1);

  lseek(fdin,0,SEEK_SET);

  while(read(fdin,&c,1))
    if(c!='\0')
       write(fdout,&c,1);

  exit(0);
}
