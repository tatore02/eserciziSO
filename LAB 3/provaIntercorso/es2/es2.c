/*
Scrivere un programma che prenda come parametro sulla riga di comando
  il nome di un file ed effettui le seguenti operazioni:
a) controlli se all’interno della current working directory sia presente tale file;
b) nel caso sia presente, controlli se si tratta di un file standard,
  di una directory o di un link simbolico e stampi a video tale informazione;
c) nel caso si tratti di un file standard stampi in output i permessi
  e il numero di vocali contenuti nel file.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

int main(int argc,char* argv[]){
  if(argc != 2){
    printf("ERROR: inserire 2 parametri\n");
  }

  struct dirent *dir;
  DIR *d;
  struct stat *buf;

  int flag = 0;

  char cwd[100];
  getcwd(cwd,sizeof(cwd));

  d = opendir(cwd);
  while((dir = readdir(d)) != NULL){
    if(strcmp(dir->d_name,argv[1]) == 0){
      flag = 1;
      printf("File: %s trovato!\n",argv[1]);
    }
  }


  if(flag == 1){
    lstat(strcat(cwd,"/text"),buf);

    if(S_ISREG(buf->st_mode))
      printf("%s è un file regolare\n",argv[1]);
    else if(S_ISDIR(buf->st_mode)){
      printf("%s è una directory\n",argv[1]);
      flag = 0;
    }
    else if(S_ISLNK(buf->st_mode)){
      printf("%s è un link\n",argv[1]);
      flag = 0;
    }
  }

  if(flag == 1){
    int fd;
    if((fd = open(argv[1],O_RDONLY)) < 0)
      printf("ERROR open\n");

    int count = 0;
    char *c;
    while(read(fd,c,1) > 0)
      if(*c == 'a' || *c == 'e' || *c == 'i' || *c == 'o' || *c == 'u')
        count++;

    printf("Numero di vocali: %d\n",count);
  }
}
