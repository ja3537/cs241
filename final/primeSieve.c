/*******************************************************************************
 * Joseph Adams
 *
 * primeSieve.c is a program designed to find all primes up to and including
 * NMAX, store them in an array, and print them each on a new line.
 *
 * The method used to find these primes is based on the sieve of Eratosthenes.
 * This method is to basically start with 2, and remove all higher integers
 * that are multiples of 2. Then the next number above 2 will be prime. Then
 * continue with 3, 5, 7, etc.
 *
 * Feel free to change NMAX. NMAX should be more than 2 and small enough to
 * be in the range of int type. The array is also not dynamically allocated,
 * so space may become an issue with very large NMAX.
*******************************************************************************/


#include <stdio.h>

#define NMAX 200

int main(void)
{
  /*
   * primes[] is the array made to hold all the primes. It starts by holding
   * all numbers from 2 to NMAX, then all non primes are set to 0. It needs
   * to be of size NMAX - 1 because the array starts from 2.
   *
   * i is an index used in for loops. multiple is used to store the
   * multiples of our primes.  
   */
  int primes[NMAX - 1];
  int i;
  int multiple;

  /*
   * This for loop places the numbers 2,,...,NMAX in the array primes[].
   */
  
  for(i = 0;i < NMAX - 1; i++)
    {
      primes[i] = i + 2;
    }

  /*
   * The following for loop iterates over all elements of primes[].
   *
   * The if statement following the for loop exists so the sieve will
   * skip all integers that have already been found to be non prime. Also,
   * if we did not have this if statement, the while would execute forever
   * because all multiples of 0 are 0 and thus are always less than NMAX.
   *
   * The algorithm starts with multiple being 2*primes[i]. The while loop
   * is entered as long as multiple is less than NMAX. Inside the while
   * loop, the integer in primes[] equivalent to multiple will be set
   * to 0 because it cannot be prime. Then multiple is iterated by
   * primes[i] to get the next multiple of that element, and the while
   * loop is entered again. So 2*primes[i] is removed, then 3*primes[i],
   * etc, for all i.
   *
   * The result is primes[] only contains prime numbers and 0's.
   */
  
  for(i = 0; i < NMAX - 1; i++)
    {
      if(primes[i] != 0)
        {
          multiple = primes[i]*2;
          while(multiple <= NMAX)
            {
              primes[multiple - 2] = 0;
              multiple += primes[i];
            }
        }
    }
  
  /*
   * The following for loop simply prints each prime on a new
   * line. It skips all the 0's in primes[].
   */
  
  for(i=0; i < NMAX - 1; i++)
    {
      if(primes[i] != 0) printf("%d\n", primes[i]);
    }

  return 0;
}
