/*******************************************************************************
 * Joseph Adams
 *
 * tmSnow.c is a program that generates a Thue-Morse sequence with a certain
 * number of iterations. It also uses the bitmap() function in bitmap.c to
 * create a .bmp file containing a Koch snowflake from this tm sequence.
 * This .bmp file will be saved as snow.bmp.
 *
 * In the main() function, the variable int interations can be altered to
 * change the number of iterations in the sequence, and thus the size of the
 * snowflake. 
*******************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

/*******************************************************************************
 * iterate_tm is used to iterate the TM sequence in our array by 1. It takes
 * as parameters the unsigned char array containing the sequence, and an int 
 * size, which is the current size of our sequence. It does not return 
 * anything, but simply alters the array passed to it.
 *
 * It is a very simple function. It has a for loop that iterates over every
 * element of our input sequence. For each element, if it is '0' it will put
 * a '1' at the end of our sequence, otherwise it will place a '0' at the end.
*******************************************************************************/

void iterate_tm(unsigned char* tm, unsigned long size)
{
  unsigned long i;

  for(i = 0; i < size; i++)
    {
      tm[size + i] = (tm[i] == '0') ? '1' : '0';
    }
}

/*******************************************************************************
 * generate_tm() is used, along with iterate_tm as a helper function, to
 * generate a TM sequence in an array. It takes two parameters: one is the
 * array in which to generate the TM sequence. This array must be an unsigned
 * char array large enough to hold the sequence.
 * This function's second parameter is an int representing the number
 * of iterations desired. The function does not return anything, but alters
 * the array passed to it.
 *
 * The function begins by declaring initial parameters int i, which is just
 * used as in index in a for loop, and unsigned long currentLength, which is
 * set to 1 and should always represent the length of our sequence. Then the
 * first element of our array is set to '0', and the for loop is entered.
 *
 * The for loop is simple. It calls iterate_tm(), passing the array and
 * currentLength to iterate the tm sequence. It then multiplies currentLength
 * by two because iterating our sequence doubles its length. The for loop
 * executes (iterations-1) times since the first '0' is the first iteration
 * of the sequence and we only need (iterations-1) more.
 *
 * The function finishes by tacking a null character onto the end of our
 * array. This is so strlen() can be used later to determing the length of
 * our sequence.  
*******************************************************************************/

void generate_tm(unsigned char* tm, int iterations)
{
  int i;
  unsigned long currentLength = 1;

  
  tm[0] = '0';
  for(i = 0; i < iterations - 1; i++)
    {
      iterate_tm(tm, currentLength);
      currentLength *= 2;
    }
  tm[currentLength] = '\0';

}


/*******************************************************************************
 * main() has four local variables: int i, used as an index for a for loop,
 * int iterations, which represents the number of iterations we want our TM
 * sequence to have, unsigned long size, representing the size a TM sequence
 * with iterations iterations will be, and an unsigned char pointer tm, used
 * to point to the array holding the sequence.
 *
 * The first thing main does it figure out how large our sequence will be.
 * Each iteration of our sequence doubles the size of the sequence, so it
 * multiplies size, which starts at 1, by 2 exactly (iterations-1) times. It
 * then uses malloc to create an appropriately sized space of memory and has
 * tm point to this memory.
 *
 * main() then calls generate_tm(), passing our pointer to our array along
 * with the desired number of iterations. This will generate our sequence.
 *
 * Instructions are then printed to the user with information about iterations
 * and stating the number of iterations currently along with the resulting
 * length of the sequence.
 *
 * Then a for loop is used to print each character of our generated TM
 * sequence, separated by spaces.
 *
 * Then bitmap() is called, passing the pointer to our array, which will
 * use this array to generate a .bmp file of a Koch snowflake.
 *
 * Finally, our array is freed.
*******************************************************************************/

int main(void)
{
  int i;
  int iterations = 15;
  unsigned long size = 1;
  unsigned char* tm;
  
  
  for(i = iterations; i > 1; i--)
    {
      size *= 2;
    }
  
  tm = malloc((size + 1)*sizeof(char));

  generate_tm(tm, iterations);

  printf("Feel free to set iterations in main() to whatever you like. It is");
  printf("currently %d, resulting in a sequence of length %lu\n",
         iterations, strlen((char*)tm));
  
  for(i=0;i < size; i++) printf("%c ", tm[i]);
  printf("\n");
  

  bitmap(tm);

  free(tm);
  
  
  return 0;
  
  
}

