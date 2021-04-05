/*******************************************************************************
 * Joseph Adams
 * 
 * sudoku.c is a program for solving sudoku puzzles. It takes input puzzles
 * from the standard input stream. These puzzles are sequences of characters
 * from '1' to '9' and using '.' as blank entries (with no spaces between
 * entries). Each sudoku puzzle should be separated by exactly one newline
 * character in the input stream. If illegal input is provided by any of: using
 * illegal characters, providing too many characters, providing too few
 * characters, or by providing characters that have been placed in illegal 
 * locations in the puzzle, the program will echo the input along with an 
 * error message. Also, if the sudoku has no solution, program will echo input
 * along with a no solution message. Otherwise, the program will solve the
 * puzzles and echo the input along with the solutions for each one.
 *
*******************************************************************************/

/*******************************************************************************
 * ASSUMPTIONS:
 * 1. This program is not designed to detect or deal with too many newline
 * characters. Providing input with multiple newline characters between
 * puzzles is not expected.
 *
 * 2. This program is not designed to detect puzzles which have multiple
 * solutions. It has been shown that it is impossible to have a sudoku with
 * one unique solution that has 16 or fewer hints. In this case, this program
 * will return an error. For all other cases where there are multiple
 * solutions, this program will simply find one.
 *
*******************************************************************************/

#include <stdio.h>

#define YES 1
#define NO 0

int error = NO;
/*error is a toggle to note when the program has found an error in the input.*/
int no_solution = NO;
/*
no_solution is a toggle used by no_solution_check() to note when the program
has no solution.
*/
char c;
/*c is the arbitrary character used to retrieve input characters.*/
char load[150];
/*load is an array used to hold input before the creation of sudoku[].*/
char sudoku[9][9];
/*sudoku[] is used to hold the actual puzzle itself as it is being solved.*/

/*******************************************************************************
 * possible() is a function used to determine if an entry n is a possible
 * solution for the entry at the position i,j. It does this by checking to see
 * if n exists in the row, column, or square block of our entry. If it finds n
 * at any of these locations, it returns NO so show that n would be an illegal
 * entry. If it searches and does not find n, it returns YES to show it would
 * be legal.
 *
 * Other than the iteration variable k, possible() has the local variables 
 * i0 and j0. These are used to iterate over the square block of our entry. 
 * They will be the index for the top left entry of the square block we are in. 
*******************************************************************************/

int possible(int i, int j, char n)
{
  int i0 = (i/3)*3;
  int j0 = (j/3)*3;
  int k;
  for(k = 0; k < 9; k++)
    {
      if (k == j) continue;
      if (sudoku[i][k] == n) return NO;
    }
  for(k = 0; k < 9; k++)
    {
      if (k == i) continue;
      if (sudoku[k][j] == n) return NO;
    }
  for(k = 0; k < 3; k++)
    {
      int m;
      for(m = 0; m < 3; m++)
        {
          if (i0 + k == i && j0 + m == j) continue;
          if (sudoku[i0 + k][j0 + m] == n) return NO;
        }
    }
  return YES;
}

/*******************************************************************************
 * no_solution_check() is a preliminary check used to make sure that every
 * entry in our puzzle has at least one solution. It iterates through the
 * puzzle using the iteration variables a and b as indexes for sudoku[].
 * It then uses the iteration variable char d to iterate through all possible
 * characters. Using the function possible(), it determines if each d is
 * possible at position a,b. If there is such a d possible, it will toggle
 * the local variable solution to YES. If the loop makes it through all
 * possible d's and solution is still NO, it will toggle global variable
 * no_solution to YES since it has found an entry with no solution. 
*******************************************************************************/

void no_solution_check()
{
  int a;
  for (a = 0; a < 9; a++)
    {
      int b;
      for (b = 0; b < 9; b++)
        {
          int solution = NO;
          char d;
          for (d = '1'; d <= '9'; d++)
            {
              if (possible(a, b, d))
                {
                  solution = YES;
                  break;
                }
            }
          if (solution == NO)
            {
              no_solution = YES;
              return;
            }
        }
    }
}

/*******************************************************************************
 * load_check() is used to receive input using the global variable char c. It
 * will copy c into the array load[] as long as the max character count is not
 * exceeded. It will also check for illegal characters while doing this. If it
 * finds any, it will toggle the global variable error to yes. It will also
 * use the local variable hint_count to count the number of hints as they are
 * passed to load[]. Once 81 characters have been passed to load[], it will
 * be capped. If the number of characters exceeds 81, load_check() will stop
 * inserting characters into load and will toggle error to yes. If there are
 * too few characters, it will also toggle error to yes. If there are fewer
 * than 17 hints, error will also be toggled to YES since it cannot have a
 * unique solution. The input is always echoed to the output by using
 * putchar(c).
*******************************************************************************/

void load_check()
{
  int i = 0;
  int hint_count = 0;
  
  while((c != '\n') && (c != EOF))
    {
      if(((c >= '1') && (c <= '9')) || c == '.')
        {
          if(c != '.') hint_count++;
          putchar(c);
        }
      else
        {
          putchar(c);
          error = YES;
        }
      if(i < 81) load[i] = c;
      c = getchar();
      i++;
    }

  load[i] = '\0';
  if (hint_count < 17) error = YES;
  if (i != 81) error = YES;
  printf("\n");
}

/*******************************************************************************
 * solved_check() is used to check if a legal puzzle is solved. It is very
 * simple. It iterates through sudoku, using the iteration variables i and j.
 * If it finds a '.' in any position, it will return NO. If it makes it through
 * all the entries without finding a '.' it will return YES.
*******************************************************************************/

int solved_check()
{
  int i;
  for(i=0; i<9; i++)
    {
      int j;
      for(j=0; j<9; j++)
        {
          if(sudoku[i][j] == '.') return NO;
        }
    }
  return YES;
}

/*******************************************************************************
 * solve() is a recursive function that solves the puzzle once all preliminary
 * checks are complete. First, it iterates through sudoku with the iteration
 * variables i and j. It tests all possible characters for each blank entry
 * using the possible() function. If an entry is possible, it increases the
 * local variable counter. The purpose of this part of the function is to
 * find the entry with the fewest legal possibilities before it makeas a guess.
 * As it works through all the entries, it stores the index of the one with 
 * fewest possibilities in the local variables min_i and min_j, and it also
 * stores the number of possibilites for that entry in globalmin.
 *
 * Once the function has found the minimum entry, it selects the first
 * possibility and inserts it into the entry. Then it recursively calls itself,
 * starting the process all over again. In the process of finding the minimum
 * entry, if solve() ever finds an entry with no possible solutions, it will
 * return because that implies a higher guess was faulty. When an inner nest
 * of solve() returns, flow of control is returned to the next innermost
 * solve(). When this happens, that solve first checks if the puzzle was
 * solved using solved_check(). It does this because solve() will also return
 * if it finds no blank entries to test. If solved_check() fails, then the
 * previous guess may have been a bad one, so the entry is made blank
 * again before trying a different possibility. If solve() runs out of
 * possibilities for that entry, then it will return, giving control to an
 * even higher invocation of solve(). If this happens for the base invocation,
 * then solve() has tried every legal combination without finding a solution.
 * In this case, it will return the puzzle to its original form, and we know
 * there can be no solution.
*******************************************************************************/

void solve()
{
  int globalmin = 0;
  int min_i;
  int min_j;
  int i;
  char m;
  for(i = 0; i < 9; i++)
    {
      int j;
      for(j = 0; j < 9; j++)
        {
          if (sudoku[i][j] == '.')
            {
              int counter = 0;
              char n;
              for(n = '1'; n <= '9'; n++)
                {
                  if(possible(i, j, n)) counter++;
                }
              if(counter == 0) return;
              else if(globalmin == 0 || counter < globalmin)
                {
                  globalmin = counter;
                  min_i = i;
                  min_j = j;
                }
            }
        }
    }
  if(globalmin == 0) return;
  for(m = '1'; m <= '9'; m++)
    {
      if(possible(min_i, min_j, m))
        {
          sudoku[min_i][min_j] = m;
          solve();
          if(!solved_check())
            {
              sudoku[min_i][min_j] = '.';
            }
        }
    }
  return;
}

/*******************************************************************************
 * load_sudoku() creates our puzzle by loading the entries of load[] into 
 * sudoku[] using the iteration variable i. It then uses the possible()
 * function to check if the entries given are, in fact, in legal positions.
 * It does this by using the iteration variables i and j to iterate all
 * entries, and if it is not blank, load_sudoku() will use possible() to check
 * if this non-blank entry is legal. If it isn't, it will toggle the global
 * variable error to YES.
*******************************************************************************/

void load_sudoku()
{
  int i;
  for(i = 0; i <= 80; i++)
    {
      sudoku[i/9][i%9] = load[i];
    }
  sudoku[9][0] = '\0';
  for(i = 0; i < 9; i++)
    {
      int j;
      for(j = 0; j < 9; j++)
        {
          if(sudoku[i][j]!='.')
            {
              if(!possible(i, j, sudoku[i][j]))
                {
                  error = YES;
                }
            }
        }
    }
}
    
/*******************************************************************************
 * main() is pretty easy to understand because it calls these functions in a
 * sensible order. It begins with c = getchar() because load_check() needs c to
 * already be the first entry to work properly. load_check() is the first line 
 * of defence against errors, and if it finds any, the if statements will cause
 * no other functions to be executed and an error statement to be printed.
 *
 * If no errors were found, load_sudoku() is executed and performs its checks.
 * If no errors were found by load_sudoku(), no_solution check() is executed
 * as yet another preliminary test. If this does not toggle no_solution to YES,
 * then the program checks if we were handed an already solved sudoku with the
 * solved_check() function. If we were, that sudoku is printed as the solution.
 *
 * If all these preliminary tests are passed and the sudoku isn't solved,
 * solve() is invoked. After the outermost solve() passes control back to
 * main(), solved_check() is used to see if it solved the puzzle. If it did,
 * the solution is printed. If not, there is no solution and such a statement
 * is printed.
 *
 * main() finishes by resetting error and no_solution before loading the next
 * puzzle using the while loop.
 *******************************************************************************/

int main(void)
{
  while ((c = getchar()) != EOF)
    {
      load_check();
      if (error == NO)
        {
          load_sudoku();
          if (error == NO) no_solution_check();
        }
      if (error == YES) printf("Error\n\n");
      else if (no_solution == NO && solved_check()) printf("%s\n\n", sudoku[0]);
      else if (error == NO && no_solution == NO)
        {
          solve();
          if(solved_check()) printf("%s\n\n", sudoku[0]);
          else printf("No solution\n\n");
        }
      else printf("No solution\n\n");
      error = NO;
      no_solution = NO;
    }
  return 0;
}

      
