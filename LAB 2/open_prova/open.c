#include  <sys/types.h>
#include  <fcntl.h>
#include  <sys/stat.h>
#include  <unistd.h>

int main(void){
  int    fd,i,n;
  char   buf[50];
  fd=open("text.txt",O_RDONLY);
  //i=lseek(fd,50,SEEK_CUR);
  n=read(fd,buf,50);
  write(1,buf,n);
}
