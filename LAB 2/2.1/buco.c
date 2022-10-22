#include  <sys/types.h>
#include  <fcntl.h>
#include  <sys/stat.h>
#include  <unistd.h>
#include  <string.h>

int main(){
  int fd1,fd2,rd,i;
  char buf[7]="ciao";
  char buf1[9]="ciao2";

  char ch;

  fd1=open("FILE1.txt",O_RDWR|O_CREAT|O_TRUNC,0644);

  write(fd1,buf,sizeof(buf));

  int j=0;
  while(write(fd1,&buf1[j],sizeof(char)) > 0){
    lseek(fd1,sizeof(char),SEEK_CUR);
    j++;
  }

  fd2=open("FILE2.txt",O_RDWR|O_CREAT|O_TRUNC,0644);

  lseek(fd1,0,SEEK_SET);

  while((rd=read(fd1,&ch,sizeof(char)))>0){
      write(fd2,&ch,sizeof(char));
  }

  close(fd1);
  close(fd2);
}
