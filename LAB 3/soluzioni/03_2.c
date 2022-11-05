//ESERCIZIO:
//Scrivere un programma che crea una directory, si sposta nella
//directory e crea un'altra directory e cosi' via..


# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
#include <stdlib.h>

int main(void)
{

  int a=0;
  
  while(1){          //loop
    if(a)  
      chdir("loop");

    if(mkdir("loop",S_IRWXU) == -1)
      {
	printf("\n dir max = %d\n",a);
        for(;a>=0;a--) {
           chdir("..");
           rmdir("loop");
           }
	break;
      }
    a++;
  }
  exit(0);
} 


