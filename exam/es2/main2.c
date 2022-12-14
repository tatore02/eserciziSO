//CONTA_VOCALI

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char *argv[]){
    if(argc != 2){
        perror("n parametri");
    }

    DIR *d;
    struct dirent *dir;
    struct stat buf;

    d = opendir(".");
    while((dir = readdir(d)) != NULL){
        if(strcmp(dir->d_name,argv[1]) == 0){
            lstat(argv[1],&buf);
            if(S_ISREG(buf.st_mode)){
                int fd = open(argv[1],O_RDONLY);
                int count = 0;
                char c;
                while(read(fd,&c,1) > 0)
                    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                        count++;
                printf("Numero di vocali del file %s: %d\n",argv[1],count);
            }
        }
    }


}

