


void my_setbuf(FILE *myfp, char *buf)
{
  
  if (buf == NULL)
      setvbuf(myfp,buf,_IONBF,0);
  else if (myfp == stderr)
      setvbuf(myfp,buf,_IONBF,0);
  else if ((myfp == stdin) || (myfp == stdout)) 
      setvbuf(myfp,NULL,_IOLBF,0);
  else 
      setvbuf(myfp,NULL,_IOFBF,0);

  return;
}

