/*
copiare il contenuto di un file in un altro
usando esclusivamente read da standard input
e write su standard output
*/

#include  <sys/types.h>
#include  <fcntl.h>
#include  <sys/stat.h>
#include  <unistd.h>
#include  <stdio.h>

int main(){
  int fd = open("file.txt",O_RDWR);
  int fd2 = open("file2.txt",O_CREAT | O_WRONLY | O_TRUNC,0644);

  dup2(fd,0);   //settare file.txt a standar_input
  dup2(fd2,1);  //settare file2.txt a standar_output

  char c;
  int n;

  while((n = read(0,&c,1)) > 0)
    write(1,&c,n);

  //proviamo a stampare con printf..
  printf("Prova sa sa, prova\n");

  //proviamo a eseguire una scanf
  lseek(fd,0,SEEK_SET);
  char buffer[20];
  scanf("%s",buffer);
  printf("\nProva con la scanf: %s",buffer);

  //ripristiniamo gli standard input e output
  dup2(STDIN_FILENO,0);
  dup2(STDOUT_FILENO,1);
/*
  printf("\nOra gli standard input e output sono stati ripristinati\n");
  printf("Prova ad inserire una stringa,");
  printf("se è andato tutto liscio essa sarà stampata a schermo:\n");
  scanf("%s",buffer);
  printf("%s\n",buffer);
*/

}
