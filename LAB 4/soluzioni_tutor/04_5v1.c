#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

void capitalize(char *file);



int main(void)
{
  capitalize("NOMI.txt");
  return(0);
}

void capitalize(char *file){
  FILE *nomi;
  char nome1[255];
  int c;

  nomi=fopen(file,"r");

  while ((c = fgetc(nomi)) != EOF)
    {
        putchar(toupper(c));
    }

}
