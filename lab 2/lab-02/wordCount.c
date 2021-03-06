/*************************
 * Joseph Adams
 *
 * This program reads a text file from the standard input stream and outputs
 * the number of characters, words, and lines of the input file. It also keeps
 * track of and reports which line has the fewest words, and separately which
 * line has the most characters.
 *
 *************************/



#include <stdio.h>

#define YES 1 /* YES and NO will be used to toggle booleans to mark when we
 are in a new line and in a word*/
#define NO 0

char c; /*This variable will be used to receive characters from input stream.*/

int line_number=0, line_characterCount=0, line_wordCount=0;
/*These are incremented in each line and character count and word count are/
reset to zero when a newline is encountered.*/
int global_characterCount=0, global_wordCount=0;
/*self-explanatory. These are always incremented when c is a new character.*/
int fewest_words=0, most_characters=0;
/*program will compare words and characters in a line to these variables to/
determine which line has the fewest words and most characters*/
int fewestWordsLineNumber, mostCharactersLineNumber;
/*these keep track of line number with fewest_words and most_characters.*/
int new_line=YES, in_word=NO; /*new_line will be toggles when '\n' is found*/
/* in_word will toggle when c enters or exits a word */


int main(void)
{
  while ((c=getchar())!= EOF)
    {
      if (c=='\n')
	{
	  if (in_word == YES)
	    {
	      in_word = NO;
	    }
	  new_line = YES;
	  if (line_wordCount <= fewest_words || fewest_words == 0)
	    {
	      fewest_words = line_wordCount;
	      fewestWordsLineNumber = line_number;
	    }
	  if (line_characterCount >= most_characters)
	    {
	      most_characters = line_characterCount;
	      mostCharactersLineNumber = line_number;
	    }
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
	  ++global_characterCount;
	  ++line_characterCount;
	}
      else
	{
	  if (in_word == NO)
	    {
	      in_word = YES;
	      ++global_wordCount;
	      ++line_wordCount;
	    }
	    
	  if (new_line == YES)
	    {
	      ++line_number;
	      printf("%d. ", line_number);
	      new_line = NO;
	    }
	  putchar(c);
	  ++global_characterCount;
	  ++line_characterCount;
	}
    }
  printf("There are %d lines, %d words, and %d characters.\n",
	 line_number, global_wordCount, global_characterCount);
  printf("Line %d has the fewest words with %d\n",
	 fewestWordsLineNumber, fewest_words);
  printf("Line %d has the most characters with %d\n\n",
	 mostCharactersLineNumber, most_characters);
  return 0;
}
  
	  
	  
	  
      
