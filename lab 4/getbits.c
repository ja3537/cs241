/*************************
 * Joseph Adams
 * CS241 Section 5 
 *
 * getbits.c is a program that reads ; delimited records from the standard
 * input stream and passes the data to the getbits function described in
 * section 2.9 of Kernighan and Ritchie. The values of getbits are then
 * printed. If any of the input numbers are out of functional ranges, an error
 * message will be printed for each one. If multiple values are improper, 
 * multiple error messages will be printed in an arbitrary order.
 *
 * The values of getbits are found by essentially taking a variable x and
 * masking the next n digits from the position p of x's binary representation.
 * The result is the decimal representation of this mask.
 *************************/

/*
Assumptions:
1. No number passed through input stream has leading zeros. For example,
"000123" is not expected.
2. No number passed through input stream will have more than 99 decimal digits.

violating either of these assumptions will cause abberant behavior
from the program.
*/


#include <stdio.h>
#include <stdlib.h>


char s1[100];
/*
s1 is an array used to store input before it is passed to 
variable x, p, or n using atoi() of the standard library.
*/
char c; /*c is used to get characters from the input stream.*/
unsigned x; /*x is the first parameter of getbits function*/
int p; /*p is the second parameter of getbits.*/
int n; /*n is the third parameter of getbits.*/
int counter = 0;
/*
counter keeps track of which variable (x, p, or n) 
to pass s1 to.
*/
int i = 0; /*i is used simply as the index for s1.*/
int error = 1;
/*
error is used to keep track of which rules for parameters have been violated.
For each possible error, this variable is multiplied by a unique prime number
by the function pass_var(), which is then used by getbits to determine which
error statements to print.
*/


/**************************************************
 * pass_var() does not take parameters or return values, but is used to
 * alter global variables: counter, error i, x, n, and p. If a
 * semi-colon or newline is encountered, it then caps s1 with a '\0' and uses
 * atoi() to pass s1 to the appropriate variable, which it keeps track of
 * using counter. pass_var() also checks for variables that are out of
 * an appropriate range to be passed to getbits. For each error, the 
 * variable error is multiplied by a prime number (2, 3, 5, or 7) to
 * keep track of which errors occurred.
 **************************************************/

void pass_var()
{
  s1[i] = '\0';
  if (counter == 0)
    {
      if (i >= 11) error *= 2;
      else if ((i == 10)&&((s1[i-1] - 48)!=(unsigned)atoi(s1)%10)) error *= 2;
      else x = (unsigned)atoi(s1);
    }
  if (counter == 1)
    {
      if ((i > 2) || atoi(s1) >= 32) error *= 3;
      p = atoi(s1);
    }
  if (counter == 2)
    {
      if ((i > 2) || atoi(s1) >= 32) error *= 5;
      n = atoi(s1);
      if (n > p + 1) error *= 7;
    }
  i = 0;
  counter = (counter + 1)%3;
}

/**************************************************
 * getbits takes an unsigned x, int p, and int n as input variables.
 * getbits begins by checking for errors found by pass_var(). If there
 * are any, it will print an appropriate error statement. If no errors
 * were found, it will print the result found by the getbits function
 * of 2.9 of Kernighan and Ritchie. The function basically takes the
 * variable x, and masks the next n digits from the p position of the
 * binary representation of x. It then returns this value as a decimal.
 * My getbits function does not return this value, but instead prints
 * it in the appropriate format.
 * It also resets error to 1 at the end of its operation.
 **************************************************/
void getbits(unsigned x, int p, int n)
{
  if (error%2 == 0) printf("Error: value out of range\n");
  if (error%3 == 0) printf("Error: position out of range\n");
  if (error%5 == 0) printf("Error: number of bits out of range\n");
  if (error%7 == 0) printf("Error: too many bits requested from position\n");
  if (error == 1)
    {
      int k = (x >> (p + 1 - n)) & ~(~0 << n);
      printf("getbits(x=%u, p=%d, n=%d) = %d\n", x, p, n, k);
    }
  error = 1;
} 

int main(void)
{
  while ((c = getchar()) != EOF)
    {
      if (c == ';') pass_var();
      else if (c == '\n')
	{
	  pass_var();
	  getbits(x, p, n);
	}
      else s1[i++] = c;
    }

  if ((c == EOF) && (counter == 2))
    {
      pass_var();
      getbits(x, p, n);
    }

  return 0;
}

  
