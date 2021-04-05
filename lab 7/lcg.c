/*******************************************************************************
 * Joseph Adams
 *
 * lcg.c is a header file to be used to implement the function prototypes
 * in lcg.h
 *
 * lcg.c defines functions used to manipulate Linear Congruential Generators
 * such as makeLCG(), which makes a LCG from the given m and c,
 * uniqueprimes(), which is used to find the unique prime factors of m, and
 * getNextRandomValue(), which is used to obtain the next x value of the
 * lcg struct.
*******************************************************************************/



#include "lcg.h"
#include <stdlib.h>


/*******************************************************************************
 * uniqueprimes() is used to find the unique primes of m, called p. It has
 * several local variables: primes_size is the current size of the *primes
 * array. The *primes array is used to store the primes found thus far.
 * primes_found is used as an index of sorts for the *primes array.
 * last_checked is either the last number to be tested to see if it is prime
 * or is the number currently being tested, depending on which part of the
 * function we are in. i is simply used as an index for loops. Of course,
 * p is also a local variable to store the prime factors found so far.
 *
 * uniqueprimes() begins by adding 2 and 3 to *primes as the first two primes.
 * It then checks if m is divisible by either, and if they are, p is
 * multiplied by the appropriate prime. If m = 1 after this step, p is
 * returned.
 *
 * If m is not 1 after this, the program goes about finding primes one by one
 * and testing to see if m is divisible by this newly found prime number.
 * Of course, only odd numbers are tested for primality and they are tested
 * by dividing by every prime already in *prime. If it is prime, it is added
 * to the array. If the *primes array runs out of space, realloc() is used
 * to add 1000 new slots everytime this happens. *temp is used to hold this
 * data first in case there is an error.
 *
 * uniqueprimes() will know to stop either when m is 1, or when the numbers
 * it is testing for primality are as large or larger than the square root
 * of m, in which case what is left of m must be a prime number. It will then
 * multiply p by m and return p.
*******************************************************************************/


unsigned long uniqueprimes(unsigned long m)
{
  unsigned long primes_size = 1000;
  unsigned long primes_found = 2;
  unsigned long p = 1;
  unsigned long i;
  unsigned long last_checked = 3;
  unsigned long *primes = malloc(1000*sizeof(unsigned long));
  primes[0] = 2;
  primes[1] = 3;
  for(i=0; i< primes_found; i++)
    {
      if(m % primes[i] == 0)
        {
          p *= primes[i];
          while(m % primes[i] == 0) m /= primes[i];
        }
    }
  while(m > 1)
    {
      last_checked += 2;
      while(last_checked != primes[primes_found - 1])
        {
          int factor = 0;
          for(i = 0; i < primes_found; i++)
            {
              if(last_checked % primes[i] == 0)
                {
                  factor = 1;
                  break;
                }
            }
          if(factor == 0)
            {
              primes[primes_found] = last_checked;
              primes_found++;
              if(primes_found > primes_size)
                {
                  unsigned long *temp;
                  primes_size += 1000;
                  temp = realloc(primes, primes_size*sizeof(unsigned long));
                  if(temp != NULL) primes = temp;
                }
              if(m % last_checked == 0)
                {
                  p *= last_checked;
                  while(m % last_checked == 0) m /= last_checked;
                }
            }
          if((last_checked + 2)*(last_checked + 2) > m)
            {
              p *= m;
              free(primes);
              return p;
            }
          last_checked += 2;
        }
    }
  free(primes);
  return p;
}

/*******************************************************************************
 * makeLCG() makes an instance of LinearCongruentialGenerator, as the name
 * implies. It does this using m and c. It uses uniqueprimes() to find the
 * unique prime factors of m called p. It then uses p to determine a, which
 * depends on whether m is divisible by 4.
 *
 * makeLCG() also checks for some errors. m must be greater than 0, c must
 * not be negative, and a must be smaller than m. If any of these rules are
 * broken, makeLCG() will return an lcg with all members equal to 0.
 * Otherwise, it will return an appropriate lcg with initial x equal to c.
*******************************************************************************/

struct LinearCongruentialGenerator makeLCG(unsigned long m, unsigned long c)
{
  unsigned long a;
  unsigned long p;
  struct LinearCongruentialGenerator lcg = {0, 0, 0, 0};
  if(m <= 0) return lcg;
  if(c < 0) return lcg;

  p = uniqueprimes(m);
  a = (m%4 == 0) ? 1 + 2*p: 1 + p;
  if (a >= m) return lcg;
  else
    {
      lcg.m = m;
      lcg.a = a;
      lcg.c = c;
      lcg.x = c;
      return lcg;
    }
}

/*******************************************************************************
 * getNextRandomValue() will return the current x value of an lcg whose
 * pointer is passed to it, while iterating x according to the LCG sequence.
 * Since it returns the current value and iterates to the next value of x,
 * a local variable unsigned long x is used to store the current value of x
 * while x is iterated. Then the local variable x is returned.
*******************************************************************************/


unsigned long getNextRandomValue(struct LinearCongruentialGenerator* lcg)
{
  unsigned long x = lcg->x;
  lcg->x = ((lcg->a)*(lcg->x)+(lcg->c))%(lcg->m);
  return x;
}

