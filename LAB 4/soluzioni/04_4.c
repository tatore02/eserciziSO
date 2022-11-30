#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Restituisce la posizione del record successivo in ordine alfabetico
long succ(FILE *fp, char *Cognome, char *Nome);

//Inserisce il record nella posizione pos
void inserisci(FILE *fp, char *Cognome, char *Nome, long pos);

//Sposta i record dalla posizione "pos" a "pos+offset"
void sposta(FILE *fp, long pos, long offset);


int main(void){
    char Cognome[50], Nome[50];
    FILE *elenco, *ordinato;
    long pos;
    char c;

    elenco=fopen("ELENCO.TXT","r");
    ordinato=fopen("ORDINATO.TXT","w+");

    while(fscanf(elenco,"%s\t%s\n",Cognome,Nome) != EOF)
       {
        pos=succ(ordinato,Cognome,Nome);
        inserisci(ordinato,Cognome,Nome,pos);
       }
    exit(0);
}



long succ(FILE *fp, char *Cognome, char *Nome)
{
char Cognome2[50], Nome2[50];
long pos;
int comp;

fseek(fp,0,SEEK_SET);
pos=ftell(fp);

while (fscanf(fp,"%s %s",Cognome2,Nome2) != EOF)
  {
   if ((comp=strcmp(Cognome2,Cognome)) > 0)
      break;
   else if (comp == 0)
      if ((comp=strcmp(Nome2,Nome)) > 0)
         break;
      else if (comp == 0)
         break;
   pos=ftell(fp)+1;
  }
return(pos);
}

void inserisci(FILE *fp, char *Cognome, char *Nome, long pos)
{

long pos_end;
int offset;

fseek(fp,0,SEEK_END);
pos_end=ftell(fp);

if (pos == pos_end)
  {
   fprintf(fp,"%s\t%s\n",Cognome,Nome);
   fflush(fp);
   return;
  }

offset=strlen(Cognome)+strlen(Nome)+2;
sposta(fp,pos,offset);
fseek(fp,pos,SEEK_SET);
fprintf(fp,"%s\t%s\n",Cognome,Nome);
fflush(fp);
return;
}


void sposta(FILE *fp, long pos, long offset)
{
long pos_end;
int c;

fseek(fp,-1,SEEK_END);
pos_end=ftell(fp)+1;

while(pos_end>=pos)
  {
   c=getc(fp);
   fseek(fp,pos_end+offset,SEEK_SET);
   putc(c,fp);
   fseek(fp,--pos_end,SEEK_SET);
  }
return;
}
