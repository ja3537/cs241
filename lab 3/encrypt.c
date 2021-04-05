/*************************
 * Joseph Adams
 *
 * This program reads a text file from the standard input stream and outputs
 * the number of characters and words of each line of the input file along with a
 * caesar cypher of the input text.
 *
 *************************/



#include <stdio.h>

#define SHIFT 7 /*Feel free to change this!*/
#define YES 1 /* YES and NO will be used to toggle booleans to mark when we
 are in a new line and in a word*/
#define NO 0
int effective_shift = (SHIFT < 0) ? (26 + (SHIFT % 26)) : SHIFT % 26;
/*effective shift will translate the shift into a positive integer <= 26 */
char c; /*This variable will be used to receive characters from input stream.*/

int line_number=0, line_characterCount=0, line_wordCount=0;
/*These are incremented in each line and character count and word count are/
reset to zero when a newline is encountered.*/
int new_line=YES, in_word=NO; /*new_line will be toggles when '\n' is found*/
/* in_word will toggle when c enters or exits a word */


int main(void)
{
  while ((c = getchar()) != EOF)
    {
      if (c=='\n')
	{
	  if (in_word == YES)
	    {
	      in_word = NO;
	    }
	  new_line = YES;
	  printf (" (%d,%d)", line_wordCount, line_characterCount);
	  line_wordCount = line_characterCount = 0;
	  putchar(c);
	}

      else if (c == ' ' || c == '\t')
	{
	  if (in_word == YES)
	    {
	      in_word = NO;
	    }
	  if (new_line == YES)
	    {
	      ++line_number;
	      printf("%d. ", line_number);
	      new_line = NO;
	    }
	  putchar(c);
	  ++line_characterCount;
	}
      else
	{
	  if (c >= 'a' && c <= 'z')
	    {
	      c = 'a' + ((c - 'a' + effective_shift)%26);
	    }

	  if (c >= 'A' && c <= 'Z')
	    {
	      c = 'A' + ((c - 'A' + effective_shift)%26);
	    }
	  
	  if (in_word == NO)
	    {
	      in_word = YES;
	      ++line_wordCount;
	    }
	    
	  if (new_line == YES)
	    {
	      ++line_number;
	      printf("%d. ", line_number);
	      new_line = NO;
	    }
	  putchar(c);
	  ++line_characterCount;
	}
    }
  printf(" (%d,%d)", line_wordCount, line_characterCount);
  return 0;
}
  
	  
	  
	  
      
