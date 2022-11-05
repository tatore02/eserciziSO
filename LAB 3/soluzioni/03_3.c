/*
Riscrivere la funzione access.
Tale funzione
int my_access (const char *path, int mode);
avrà come primo parametro un file da testare e come secondo parametro
un numero ottale che indicherà i permessi da controllare (read, write,
execute o esistenza del file) per il real user.
*/


#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

int my_access(char *path,int modo)
{
   uid_t real_user;
   uid_t real_group;
   mode_t temp,a;
   struct stat buf;
   temp=0;


   real_user=getuid();
   real_group=getgid();


   if(stat(path,&buf)==0)
     {
        if (real_user==0)
          return(0);

	if(real_user==buf.st_uid)
	  {
	     temp=(S_IRWXU & buf.st_mode);
       modo = modo << 6;

           if( (temp & modo)== modo)
	       return(0);
	     else
	       return(-1);
	  }


	if(real_group==buf.st_gid)
	  {
	     temp=(S_IRWXG & buf.st_mode);
           modo = modo << 3;

           if( (temp & modo)== modo)
	       return(0);
	     else
	       return(-1);
	  }
	else
	  {
	     temp=(S_IRWXO & buf.st_mode);
           if( (temp & modo)== modo)
	       return(0);
	     else
	       return(-1);
	  }
     }
   else
     return(-1);
}

int main(void)
{
   char pathname[80];
   int modo;

   printf("\nInserisci il nome del file :");
   scanf("%s",pathname);
   printf("inserisci il modo di accesso :");
   scanf("%i",&modo);

   if(my_access(pathname,modo))
     printf("my_access test fallito\n");
   else
     printf("my_access test OK\n");

   if(access(pathname,modo))
     printf("access test fallito\n");
   else
     printf("access test OK\n");




   exit(0);
}
