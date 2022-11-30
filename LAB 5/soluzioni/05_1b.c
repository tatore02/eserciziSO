#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int test_vocale(char c);
void err_sys(char *mesg);

int main(int argc, char *argv[])
{

int in, out, semc, semv;
pid_t pid_c, pid_v;
char c;
ssize_t s;

umask(0);
if(argc != 3)  {
   printf("Numero errato di argomenti!\n");
   exit(1);
}

if((in=open(argv[1],O_RDONLY))<0) 
   err_sys("Errore nell'apertura del file input");

if((out=open(argv[2],O_RDWR | O_CREAT | O_TRUNC, 0666))<0)
   err_sys("Errore nell'apertura del file output");

if((semc=open("C",O_RDWR | O_CREAT, 0666))<0)
   err_sys("Errore nell'apertura di SEMC");
close(semc);

if((pid_c=fork())<0)
   err_sys("Errore nella prima fork");

if(pid_c > 0)
   if((pid_v=fork())<0)
      err_sys("Errore nella seconda fork");

if(pid_v == 0)  {
 for(;;)  {
   while(semv=(open("V",O_RDONLY))<0) ; 
   do {
      s=read(in, &c, 1);
      if(test_vocale(c) && s)
         write(out,&c, 1);
      else if(s) {
         lseek(in, -1, SEEK_CUR);
         remove("V");
         open("C", O_RDONLY | O_CREAT, 0666);
         s=0;
      }
      else if(s == 0)  {
         remove("V");
         open("C", O_RDONLY | O_CREAT, 0666);
         exit(0);
      }
   } while (s > 0);
  }
}

else if(pid_c == 0) {
 for(;;)  {
   while(semc=(open("C",O_RDONLY))<0) ; 
   do {
      s=read(in, &c, 1);
      if(!test_vocale(c) && s)
         write(out,&c, 1);
      else if(s){
         lseek(in, -1, SEEK_CUR);
         remove("C");
         open("V", O_RDONLY | O_CREAT, 0666);
         s=0;
      }
      else if(s == 0)  {
         remove("C");
         open("V", O_RDONLY | O_CREAT, 0666);
         exit(0);
      }
   } while (s > 0);
  }
  exit(0);
}

else  {
wait(NULL);
wait(NULL);
remove("C");
remove("V");
exit(0);
}
}



int test_vocale(char ch) {
if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || 
   ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' ||
   ch == 'y' || ch == 'Y')
      return(1);
else return(0);
}

void err_sys(char *mesg) {
  printf("%s\n",mesg);
  exit(2);
}

