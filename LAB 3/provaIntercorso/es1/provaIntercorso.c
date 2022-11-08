/*
a) utilizzando le sytem call che permettono di leggere il contenuto di una directory,
controlli se all’interno della directory (primo parametro) sia presente tale file (secondo parametro);

b) nel caso sia presente, controlli se si tratta di un file standard
o di un link simbolico e stampi a video tale informazione;

c) nel caso si tratti di un file standard stampi in output la dimensione e
il numero di stringhe che iniziano con una vocale contenute nel file.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>

int main(int argc,char* argv[]){

    if(argc != 3){
        printf("Error: insert 3 parametr\n");
        exit(1);
    }

    char cwd[100];
    getcwd(cwd,sizeof(cwd));
    char *fullPath;

    struct dirent *dir;
    DIR *d;
    struct stat buf;
    int fd;
    int flag = 0;   //segnala se un file è presente nella directory

    if((d = opendir(argv[1])) == NULL)
        printf("Error: open dir\n");

    while((dir = readdir(d)) != NULL){
        if(strcmp(argv[2],dir->d_name) == 0){
            printf("File: %s trovato nella directory: %s\n",argv[2],argv[1]);

            fullPath = strcat(cwd,"/directory/file.txt");

            if(lstat(fullPath,&buf) != 0){
                if(stat(fullPath,&buf) != 0)
                    printf("Error stat file\n");
            }
            fd = open(fullPath,O_RDONLY);
            flag = 1;
            break;
        }
    }

    if(flag == 1){
      if (S_ISREG(buf.st_mode))
        puts("regular");
      else if (S_ISLNK(buf.st_mode)){
        puts("symbolic link");
        flag = 0;
      }
      else{
        puts("ne regolare ne link simbolico");
        flag = 0;
      }
    }


    if(flag == 1){
        long size = buf.st_size;
        printf("Taglia del file: %lu byte\n",size);

        char *c;
        int n=0;    //numero di stringhe che iniziano con una vocale
        while(read(fd,c,2) > 1){
          if(c[0] == ' '){
            if(c[1] == 'a' || c[1] == 'e' || c[1] == 'i' || c[1] == 'o' || c[1] == 'u')
              n++;
          }
        }
        printf("Stringhe che iniziano con una vocale: %d\n",n);
    }

}
