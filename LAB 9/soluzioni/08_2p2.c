#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>


int main()   {

int rnd;
FILE *out;
pid_t pid;

pid=getpid();
srand( time(NULL));
out=fopen("TEMP","w");

while(1)  {
   rnd=1+(int) (99.0 * rand()/(RAND_MAX));
   fprintf(out,"%d %d\n", rnd, pid);
   fflush(out);
   sleep(1);
   }
}
