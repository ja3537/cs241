/********************
 * Joseph Adams
 *
 * This program is designed to take input encrypted by encrypt.c
 * and decrypt it, preserving line numbers as well as word and 
 * character counts created by encrypt.c.
 *
 ********************/



#include <stdio.h>

#define SHIFT 7
/*Feel free to change SHIFT! Make sure it matches encrypt.c! */
int effective_shift = (SHIFT < 0) ? -(SHIFT % 26) : (26 - (SHIFT % 26));
/*effective shift will translate the shift into a positive integer <=26 */

int main(void)
{
  char c;

  while ((c = getchar()) != EOF)
    {
      if (c >= 'a' && c <= 'z')
	{
	  c = 'a' + ((c - 'a' + effective_shift)%26);
	}

      if (c >= 'A' && c <= 'Z')
	{
	  c = 'A' + ((c - 'A' + effective_shift)%26);
	}

      putchar(c);

    }
  
  return 0;
  
}
	
	    
