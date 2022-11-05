//ESERCIZIO:
//Scrivere un programma che cerca un link in una directory
//e stampa il contenuto del file puntato dal link

#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>
#include  <unistd.h>
#include  <dirent.h>
#include <stdlib.h>

int main()
{
  char c, cwd[100];
  int  fd;
  struct stat buf;
  struct dirent   *drn;
  DIR             *dp;


  getcwd(cwd,sizeof(cwd)); 

  if((dp=opendir(cwd))==NULL)       //'carica' la struttura associata alla 
    printf("opendir error\n");           //directory

  while((drn=readdir(dp))!=NULL)        //legge il contenuto della dir
    {
      if(lstat(drn->d_name,&buf) <0)
         printf("Errore lstat su %s\n",drn->d_name);

      if(S_ISLNK(buf.st_mode))
         {
           printf("Trovato il link %s\n",drn->d_name);
           fd=open(drn->d_name,O_RDONLY);
           while ( read(fd, &c, 1) > 0) 
               write(STDOUT_FILENO, &c, 1); 
         }
    }

  closedir(dp);
  
  exit(0);
}

	

