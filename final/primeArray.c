/*******************************************************************************
 * Joseph Adams
 *
 * primeArray.c is a program designed to find all primes up to and including
 * NMAX (must be within bounds of int type), store them in an array, and print 
 * them each on a new line. 
 *
 * Feel free to change NMAX. NMAX should be more than 2 and small enough to
 * be in the range of int type. The array is also not dynamically allocated,
 * so space may become an issue with very large NMAX.
*******************************************************************************/

#define NMAX 200
#include <stdio.h>

int main(void)
{
  /*
   * primes[] is the array made to hold all the primes. It starts by holding
   * all numbers from 2 to NMAX, then all non primes are set to 0. It needs
   * to be of size NMAX - 1 because the array starts from 2.
   *
   * i and j are just indexes used in for loops.
   */
  int primes[NMAX - 1];
  int i;
  int j;

  /*
   * This for loop places the numbers 2,3,...,NMAX in the array primes[].
   */
  for(i = 0;i < NMAX - 1; i++)
    {
      primes[i] = i + 2;
    }
  /*
   * These for loops are used to replace all non primes with 0 in 
   * primes[]. The outer loop's index is j, and it iterates over all 
   * elements starting with primes[1] = 3.
   *
   * The inner for loop is controlled by index i, which starts at 0 and
   * is always less than j. For every element j, the mod of j with
   * respect to each element i<j is checked. If it is 0, then i|j, and
   * thus j is not prime. The if statement checks to see if this is
   * true, with the added condition that i must not be 0 before the
   * modulus is checked. Dividing by 0 is a bad thing to try to do,
   * in general.
   *
   * If the ith element is not 0 and the modulus is 0, then the jth
   * element is replaced with 0.
   *
   * The end result is primes[] will contain only prime numbers and 0's.
   */
  
  for(j = 1; j< NMAX - 1; j++)
    {
      for(i = 0; i < j; i++)
        {
          if(primes[i] != 0 && primes[j] % primes[i] == 0)
            {
              primes[j] = 0;
              break;
            }
        }
    }
  
  /*
   * The following for loop simply prints each prime on a new
   * line. It skips all the 0's in primes[].
   */

  for(i=0;i < NMAX - 1; i++)
    {
    if(primes[i] != 0) printf("%d\n", primes[i]);
    }
    
  return 0;
}
