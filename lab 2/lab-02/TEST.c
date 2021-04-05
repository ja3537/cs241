#include <stdio.h>


void main(void)
{
  char c;
  int new_line=1;
  int lc=0;

  printf("%d.", lc);
  
  while ((c=getchar())!=EOF)
    {
      if (c=='\n')
	{
	  putchar(c);
	  new_line=1;
	}
      else if (new_line==1)
	{
	  new_line=0;
	  ++lc;
	  printf("%d.", lc);
	  putchar(c);
	}
      else putchar(c);
      

    }
}
      
