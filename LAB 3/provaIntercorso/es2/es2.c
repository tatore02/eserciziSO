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
  struct stat buf;

  char *fullPath;

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
    fullPath = strcat(cwd,"/");
    fullPath = strcat(fullPath,argv[1]);

    if(lstat(fullPath,&buf) != 0)
      if(stat(fullPath,&buf) != 0)
        printf("ERROR stat\n");


    if(S_ISREG(buf.st_mode))
      printf("%s è un file regolare\n",argv[1]);
    else if(S_ISDIR(buf.st_mode)){
      printf("%s è una directory\n",argv[1]);
      flag = 0;
    }
    else if(S_ISLNK(buf.st_mode)){
      printf("%s è un link\n",argv[1]);
      flag = 0;
    }
  }

  if(flag == 1){
    int fd;
    if((fd = open(argv[1],O_RDONLY)) < 0)
      printf("ERROR open\n");

    int count = 0;
    char c;
    while(read(fd,&c,1) > 0)
      if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        count++;

    printf("Numero di vocali: %d\n",count);

    //permessi
    if(buf.st_mode & S_IRUSR)
      printf("L'utente può leggere il file\n");
    if(buf.st_mode & S_IWUSR)
      printf("L'utente può scrivere il file\n");
    if(buf.st_mode & S_IXUSR)
      printf("L'utente può eseguire il file\n");

    if(buf.st_mode & S_IRGRP)
      printf("Il gruppo può leggere il file\n");
    if(buf.st_mode & S_IWGRP)
      printf("Il gruppo può scrivere il file\n");
    if(buf.st_mode & S_IXGRP)
      printf("Il gruppo può eseguire il file\n");

    if(buf.st_mode & S_IROTH)
      printf("Gli altri possono leggere il file\n");
    if(buf.st_mode & S_IWOTH)
      printf("Gli altri possono scrivere il file\n");
    if(buf.st_mode & S_IXOTH)
      printf("Gli altri possono eseguire il file\n");
  }
}
