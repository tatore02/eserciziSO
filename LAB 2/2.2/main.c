#include  <sys/types.h>
#include  <fcntl.h>
#include  <sys/stat.h>
#include  <unistd.h>
#include  <stdio.h>
#include  <stdlib.h>

int main(){
  char buffer[20];
  int n,m;

  int fd = open("file.txt",O_RDWR,0644);
  int fd2 = open("file2.txt",O_RDWR,0644);

  lseek(fd,0,SEEK_SET);
  lseek(fd2,0,SEEK_SET);

  while((n = read(0,buffer,20)) > 0){
    if(n > 2)
      break;
    write(fd,buffer,1);
  }

  int i = -1;
  m = lseek(fd,i,SEEK_END);
  i--;

  while(m >= 0){
    if((n = read(fd,buffer,1)) > 0)
      write(fd2,buffer,n);
    m = lseek(fd,i,SEEK_CUR);
  }

  /*
  while((n = read(fd,buffer,1) > 0)){
    write(fd2,buffer,n);
  }
  */
}
