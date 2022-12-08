#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

void uppercase(char *filename);
void lowercase(char *filename);



int main(void)
{
  FILE *nomi;
  char nome1[255], nome2[255];
  int c;

  uppercase("NOMI.txt");
  //lowercase("NOMI.txt");

  exit(0);
}


void uppercase(char *filename)
{
  FILE *nomi1, *nomi2;
  int c;

  nomi1=fopen(filename,"r+");
  nomi2=fopen(filename,"r");

  while((c=fgetc(nomi2))!= EOF) fputc(toupper(c),nomi1);

  return;
}

void lowercase(char *filename)
{
  FILE *nomi1, *nomi2;
  int c;

  nomi1=fopen(filename,"r+");
  nomi2=fopen(filename,"r");

  while((c=fgetc(nomi2))!= EOF) fputc(tolower(c),nomi1);

  return;
}
