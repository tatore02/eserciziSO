/*
copiare il contenuto di un file in un altro
usando esclusivamente read da standard input
e write su standard output
*/

#include  <sys/types.h>
#include  <fcntl.h>
#include  <sys/stat.h>
#include  <unistd.h>

int main(){
  int fd = open("file.txt",O_RDWR);
  int fd2 = open("file2.txt",O_RDWR,0644);

  dup2(fd,0);   //settare file.txt a standar_input
  dup2(fd2,1);  //settare file2.txt a standar_output

  char buffer[20];
  int n;

  while((n = read(0,buffer,1)) > 0){
    write(1,buffer,1);
  }
}
