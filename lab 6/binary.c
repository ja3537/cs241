/*******************************************************************************
 * Joseph Adams
 *
 * binary.c is a program designed to accept command-line arguments and convert
 * input in the form of integers of varying sizes, and convert that integer
 * either from decimal to binary or binary to decimal and print the result.
 *
 * Proper commands for this program are as follows:
 * usage:
 * binary OPTION SIZE NUMBER
 * OPTION:
 * -b2d NUMBER is binary and output will be in decimal.
 * -d2b NUMBER is decimal and output will be in binary.
 * SIZE:
 * -8 input is an unsigned 8-bit integer.
 * -16 input is an unsigned 16-bit integer.
 * -32 input is an unsigned 32-bit integer.
 * -64 input is an unsigned 64-bit integer.
 * NUMBER:
 * number to be converted.
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int error = 1;
/* 
 * error is a variable used in the process of error detection. It is
 * multiplied by a unique prime number, depending on the error, in the
 * function error_check(). It then is read by print_errors() to
 * print the appropriate error messages.
 */
char ** global_argv;
/*
 * global_argv is used to hold the argv pointer from main() so it can be
 * referenced as a global variable inside functions.
 */
long global_argc;
/*
 * global_argc is used to hold the argc variable from main() so it can be
 * referenced as a global variable inside functions.
 */

/*******************************************************************************
 * error_check() is a function that checks for errors, as the name implies.
 * error_check() does not return any values, but alters the global variable
 * error as it finds errors. It is possible for it to find multiple errors
 * for printing with the exception of having the incorrect number of arguments
 * in argc.
 *
 * The local variables temp 1, 2, 3, & 4 are just to aid in splitting up long
 * relations for if statements.
 *
 * The function strcmp() from library string.h is used extensively. strcmp()
 * accepts two strings as arguments and will return 0 if the strings are
 * identical and a nonzero number otherwise.
 *
 * The first error it looks for is if argc is not 4. If this error is found,
 * error is multiplied by 2 and the function returns.
 *
 * The next error is incorrect usage of the conversion slot. Only -b2d or -d2b
 * are allowed. If neither of these are used, error is multiplied by 3.
 *
 * The next error is incorrect bit size. Only -8 -16 -32 or -64 are allowed.
 * If none are used, error is multiplied by 5.
 *
 * If the conversion is -b2d, then the input must be in binary. So error_check
 * makes sure of this. If the conversion is -b2d, but non-binary input is
 * given, error will be mulitplied by 7.
 *
 * If the conversion is -d2b, then the input must be in decimal. So
 * error_check makes sure of this. If the conversion is -d2b, but non-decimal
 * input is given, error will be multiplied by 11.
*******************************************************************************/
void error_check()
{
  int temp1;
  int temp2;
  int temp3;
  int temp4;
  
  if(global_argc != 4)
    {
      error *= 2;
      return;
    }
  
  temp1 = strcmp("-b2d", global_argv[1]);
  temp2 = strcmp("-d2b", global_argv[1]);
  
  if(temp1 && temp2)
    {
      error *= 3;
    }
  temp1 = strcmp(global_argv[2], "-8");
  temp2 = strcmp(global_argv[2], "-16");
  temp3 = strcmp(global_argv[2], "-32");
  temp4 = strcmp(global_argv[2], "-64");
  
  if(temp1 && temp2 && temp3 && temp4) error *= 5;

  if(!strcmp("-b2d", global_argv[1]))
    {
      int i;
      for(i = 0; i < strlen(global_argv[3]); i++)
        {
	  temp1 = strncmp(global_argv[3] + i, "1", 1);
	  temp2 = strncmp(global_argv[3] + i, "0", 1);
	  
	  if(temp1 && temp2)
	    {
	      error *= 7;
	      break;
	    }
        }
    }

  if(!strcmp("-d2b", global_argv[1]))
    {
      int i;
      for(i = 0; i < strlen(global_argv[3]); i++)
	{
	  temp1 = (global_argv[3][i] < '0');
	  temp2 = (global_argv[3][i] > '9');

	  if(temp1 || temp2)
	    {
	      error *= 11;
	      break;
	    }
	}
    }
}

/*******************************************************************************
 * print_errors() is a relatively simple function. It's job is to print error
 * messages if errors are found by error_check(). It determines if errors were
 * found by checking if the global variable error is divisible by the
 * appropriate prime number. If so, it will print appropriate error messages,
 * followed by information on proper program usage. The return is void.
 *******************************************************************************/

void print_errors()
{
  if(error % 2 == 0)
    {
      printf("ERROR: incorrect number of arguments\n");
    }
  if(error % 3 == 0)
    {
      printf("ERROR: argument 1 must be -b2d | -d2b\n");
    }
  if(error % 5 == 0)
    {
      printf("ERROR: argument 2 must be: -8 | -16 | -32 | -64\n");
    }
  if(error % 7 == 0)
    {
      printf("ERROR: argument 3 is not a binary integer\n");
    }
  if(error % 11 == 0)
    {
      printf("ERROR: argument 3 is not a decimal integer\n");
    }

  printf("usage:\n");
  printf("binary OPTION SIZE NUMBER\n");
  printf("  OPTION:\n");
  printf("    -b2d  NUMBER is binary and output will be in decimal.\n");
  printf("    -d2b  NUMBER is decimal and output will be in binary.\n\n");
  printf("  SIZE:\n");
  printf("    -8    input is an unsigned 8-bit integer.\n");
  printf("    -16   input is an unsigned 16-bit integer.\n");
  printf("    -32   input is an unsigned 32-bit integer.\n");
  printf("    -64   input is an unsigned 64-bit integer.\n\n");
  printf("  NUMBER:\n");
  printf("    number to be converted.\n\n");
}

/*******************************************************************************
 * myExp is a very simple exponent function similar to pow() of the math
 * library, except it returns a long int. The parameters are int base, which is
 * the base of the exponent, and int power, which is the power of base. The
 * function returns base^power as a long.
 *
 * The local variable answer is used to store the answer. The local variable i
 * is used as an index in the for loop.
 *******************************************************************************/

long myExp(int base, int power)
{
  long answer = 1;
  if(power == 0) return 1;
  else
    {
      int i;
      for(i = 0; i < power; i++) answer *= (long) base;
      return answer;
    }
}

/*******************************************************************************
 * The purpose of long_to_str() is to take in two parameters, long num and
 * char str[], and convert num to a string and place this data in str.
 *
 * The function works by first placing the data backwards into the array temp.
 * The slot variable is used to keep track of which slot of temp it is placing
 * the data. The variable k is used just to store the information in num. i
 * is used as the index of a for loop. The purpose of the for loop is to 
 * place the data in temp into str in reverse order.
 *
 * long_to_str does not return anything, but alters the string that is passed
 * as a parameter. 
 ******************************************************************************/


void long_to_str(long num, char str[])
{
  int slot = 0;
  char temp[100];
  long k = num;
  int i;
  do
    {
      temp[slot] = k%10 + 48;
      slot++;
    }
  while(k/=10);
  temp[slot] = '\0';
  str[slot] = '\0';
  for(i = 0; i <= slot; i++)
    {
      str[i] = temp[slot -1 - i];
    }
}

/*******************************************************************************
 * answer_length() is a very small function that exists to avoid having a 
 * complex closed expression elsewhere in the program. It simply stores the
 * number of characters needed for the program to print with various bit
 * inputs. For example, if the number of bits is -16, (2^16-1)= 65535. So we
 * need 5 digits, plus one comma to make 65,535. So answer_length returns 6.
 *
 * answer_length returns an int and takes as a parameter int bits, which is
 * the number of bits the user has input.
*******************************************************************************/

int answer_length(int bits)
{
  int n = bits;
  if(n == 8) return 3;
  else if(n == 16) return 6;
  else if(n == 32) return 13;
  else if(n == 64) return 26;
  else return 0;
}

/*******************************************************************************
 * print_answer() is used to print the answer found by convert() in the
 * proper format. This includes adding commas where appropriate for a decimal
 * answer, and spaces where appropriate for a binary answer. It also adds
 * the correct number of leading zeros for the case when bits = 64.
 *
 * The function does not return anything, and takes as parameters int bits,
 * which is the number of bits the user has input, and the string answer,
 * which is the answer found by convert().
 *
 * The function is split into which situation we are in: -b2d or -d2b. It
 * uses the function strcmp() to determine which we are in.
 *
 * The local variable i is just used as a for loop index. The local variable
 * int n is used to break up a long relation.
*******************************************************************************/
void print_answer(int bits, char* answer)
{
  if(!strcmp(global_argv[1], "-b2d"))
    {
      int i;
      int j;
      if(strlen(answer) + (strlen(answer)-1)/3 < answer_length(bits))
	{
	  int i;
	  int n = answer_length(bits) - (strlen(answer)-1)/3 - strlen(answer);
	  for(i = 0; i < n; i++) printf(" ");
	}
      for(i = 0; i < strlen(answer); i++)
	{
	  printf("%c", answer[i]);
	  j = strlen(answer) - 1 - i;
	  if((j%3 == 0) && (j != 0)) printf(",");
	}
    }
  else
    {
      int i;
      if(bits == 64)
	{
	  for(i = 0; i < 8; i++) printf("0000 ");
	}
      for(i = 0; i < strlen(answer); i++)
	{
	  printf("%c", answer[i]);
	  if(((i + 1) % 4 == 0) && i != strlen(answer) - 1) printf(" ");
	}
    }
      
  printf("\n");
}

/*******************************************************************************
 * convert() does the heavy lifting of this program. It's goal is to make the
 * appropriate conversions given user input, either from decimal to binary or
 * binary to decimal. It stores the answer in local variables that are passed
 * to other functions.
 *
 * convert() does not return anything, and does not have any parameters, but
 * does use the global variables global_argv and global_argc.
 *
 * The first thing convert() does is determine the number of bits input by
 * the user. It does this using the strcmp() function. It then stores this in
 * the local variable int bits.
 *
 * The local variables answer_str[] and long answer are used to store the
 * answer found by the function, and are used differently depending on which
 * situation we are in. The local variable int num_length is the length of
 * the number input by the user.
 *
 * The function is split into two parts, depending if we are in the d2b or
 * b2d situation. It uses strcmp to determine which we are in.
 *
 * b2d situation: The function iterates over the user input number using the
 * index i. i is initialized differently depending on whether num_length is
 * bigger or smaller than bits. As the function iterates over the input
 * number, the function adds the appropriate power of two to the local 
 * variable answer using the local variable power and the function myExp().
 *
 * Once answer is found, it is converted to answer_str using long_to_str().
 * Then answer_str is printed using print_answer().
 *
 * d2b situation: The first thing d2b must do is deal with the problem of
 * having an input number that is too large. To do this, it masks only the
 * appropriate number of bits from the user input. This mask uses the local
 * variable int shift, which is equal to bits except for the special
 * situation where bits is 64. In this case, shift is 32 because ansi C
 * cannot deal with a shift of 64.
 *
 * The user input is stored in answer, and is converted from a string using
 * the standard library function strtoul(), which takes answer_str, into
 * which the user input string has been stored, as well as a pointer *ptr and
 * answer ans parameters. It converts the string answer_str and stores it 
 * into answer as a decimal. Then the number in string is masked with shift.
 *
 * The function then converts answer to a binary string in answer_str. It
 * does this by systematically determining if answer is larger than the
 * appropriate power of two, if it is, a 1 is stored and this power of two
 * is subtracted from answer. If not, a 0 is stored. i and j are used as
 * indexes. long temp is used during the masking of a long int.
 *
 * Once answer_str is found and is binary, it is passed to print_answer()
 * for printing in the appropriate format.
*******************************************************************************/


void convert()
{
  char answer_str[100];
  long answer = 0;
  int num_length = strlen(global_argv[3]);
  int bits;
  if(!strcmp(global_argv[2], "-8")) bits = 8;
  else if(!strcmp(global_argv[2], "-16")) bits = 16;
  else if(!strcmp(global_argv[2], "-32")) bits = 32;
  else if(!strcmp(global_argv[2], "-64")) bits = 64;

  if(!strcmp(global_argv[1], "-b2d"))
    {
      int i = (num_length > bits) ? num_length - bits : 0;
      for(; i < num_length; i++)
	{
	  int power = num_length-1-i;
	  if(strncmp(global_argv[3] + i, "0", 1))
	    {
	      if(answer == 0) answer = myExp(2, power);
	      else answer += myExp(2, power);
	    }
	}

      long_to_str(answer, answer_str);
      print_answer(bits, answer_str);
    }
  else if(!strcmp(global_argv[1], "-d2b"))
    {
      int i;
      int j = 0;
      int shift = (bits == 64) ? 32 : bits;
      char *ptr;
      long temp = 0;
      for(i=0; i < strlen(global_argv[3]) +1; i++)
	{
	  answer_str[i] = (global_argv[3][i]);
	}
      answer = strtoul(answer_str, &ptr, 10);
      answer = answer & ~(~temp << shift);
      for(i = shift - 1; i >= 0; i--, j++)
	{
	  if(myExp(2, i) <= answer)
	    {
	      answer_str[j] = '1';
	      answer -= myExp(2, i);
	    }
	  else answer_str[j] = '0';
	  answer_str[bits] = '\0';
	}

      print_answer(bits, answer_str);
    }
}

/*******************************************************************************
 * main() is easy to understand because it calls these previously defined
 * functions in a logical order.
 *
 * main() returns the int 0, and takes int argc and array argv[] as parameters.
 * 
 * The first thing main() does is copy argc and argv into the corresponding
 * global variables for other functions to use.
 *
 * It then runs error_check to check for errors, and if any are found, it
 * runs print_errors. If none are found, it will run convert(), which will
 * perform all necessary operations and function calls for our program.
*******************************************************************************/
  
int main(int argc, char *argv[])
{
  global_argc = argc;
  global_argv = argv;
  error_check();
  if(error != 1) print_errors();
  else convert();
  
  return 0;
}

