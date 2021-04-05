/*******************************************************************************
 * Joseph Adams 
 *
 * primesTable.c is a program designed to print a table comparing the 
 * amount of memory needed for an array holding primes from 2 to 200 as is
 * done in primeArray.c, versus the memory needed for a linked list holding
 * primes from 2 to 200, as implemented in primeList.c.
 *
 * This program works essentially as primeList.c does, except that a table
 * is printed in main(). It contains all the same functions as primeList.c
 * with the same comments for each function.
 *
 * The answer to part d) is also printed underneath the table. I have placed
 * it here because I thought it would be better to have the table to
 * reference.
 *
 * It does not have the added functionality of being able to change NMAX, 
 * because the table requested was specific.
*******************************************************************************/


#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
  int data;
  struct ListNode* next;
};

/*******************************************************************************
 * createNode() takes an integer as a parameter, and uses malloc to allocate
 * memory on the heap to create a new ListNode with this data. The next
 * pointer is set to NULL and a pointer to the new node is returned.
*******************************************************************************/

struct ListNode* createNode(int data)
{
  struct ListNode* new = malloc(sizeof(struct ListNode));
  new->data = data;
  new->next = NULL;
  return new;
}

/*******************************************************************************
 * listLength() is a simple function which takes a pointer to the head node
 * of a list and returns the length of that list as an int.
 *
 * It has two local variables. One is a pointer to a node called node, which
 * is used to point to nodes iteratively down the list. The other local
 * variable is count, which is an integer that iterates each time a non-NULL
 * node is found.
 *
 * The function uses a while loop that terminates when the current node is
 * NULL. While the current node is not NULL, count is iterated and node
 * is made to point at node->next. After the while loop is exited (if the
 * list was an empty list, it would have never been entered), count is
 * returned.
*******************************************************************************/

int listLength(struct ListNode* head)
{
  struct ListNode* node = head;
  int count = 0;
  while(node != NULL)
    {
      count++;
      node = node->next;
    }
  return count;
}

/*******************************************************************************
 * printList() is a simple function which takes a pointer to the head of a
 * list as a parameter and prints the data in all nodes in the order of the
 * list.
 *
 * It has one local variable, node, which is a pointer to a list node. A while
 * loop is used to make node point iteratively down the list. For each node
 * pointed to, the data in the node is printed followed by a newline.
 *
 * The function uses a while loop to iterate node down the list. The
 * while loop is entered so long as node is not NULL. If the while loop is
 * entered, the data is printed and node is made to point at the next node.
 *
 * After node has made its way down the list, a newline is printed. The
 * function does not return anything.
*******************************************************************************/

void printList(struct ListNode* head)
{
  struct ListNode* node = head;
  while(node != NULL)
    {
      if(node != head) printf(", ");
      printf("%d", node->data);
      node = node->next;
    }
  printf("\n");
}

/*******************************************************************************
 * freeList is a simple function which takes a pointer to the head node of a
 * list and frees the whole list.
 *
 * It has one local parameter, node, which is a pointer to a node of the list.
 * A while loop is used to make node point to head, then to make head point to
 * the next node, and finally to free node. As long as head is not null, the
 * loop continues down the list, freeing the nodes one by one.
*******************************************************************************/

void freeList(struct ListNode* head)
{
  while(head != NULL)
    {
      struct ListNode* node = head;
      head = head->next;
      free(node);
      node = NULL;
    }
}

/*******************************************************************************
 * check_and_add_prime() is a function designed to take a node to the end
 * of a linked list as long as the data in that node is not divisible by the
 * data of any of the nodes already in the list.
 *
 * This function takes a pointer to a listnode and an integer n as parameters.
 * It returns a pointer to a listnode.
 *
 * First, if the node passed is NULL, then the function simply creates the
 * new node with data n using createNode() and returns a pointer to it.
 *
 * Otherwise, it will check to see if n is divisible by the data in the node
 * passed to it. If it is, it will simply return the node passed and proceed
 * no further.
 *
 * If n is not divisible by data, then the function recursively calls itself
 * by setting the next node equal to a function call with the next node
 * passed as a parameter. It does this in order to make its way down the list.
 *
 * The effect of this is if n is divisible by any data in the list, the
 * recursion will stop, the function calls will collapse, and the list will
 * remain unchanged. If not, it will eventually make its way to the last
 * pointer to NULL, and the new node with data n will be placed there.
 *
 * Of course, if we were to incrementally pass the integers 2,3,...,NMAX into
 * this function, the result would be a linked list containing only primes.
*******************************************************************************/

struct ListNode* check_and_add_prime(struct ListNode* root, int n)
{
  if(root == NULL)
    {
      root = createNode(n);
      return root;
    }
  else if(n % root->data == 0) return root;
  else root->next = check_and_add_prime(root->next, n);
  return root;
}

int main(void)
{
  /*
   * i is used simply as an index for a for loop. head is a pointer to
   * head is a listnode which will point to the head of our list.
   */
  int i;
  struct ListNode* head = NULL;

  /*
   * Just some comments before the table is printed.
   */
  printf("\n\n");
  printf("Below is a table to compare the memory used by an array of ");
  printf("integers and a linked list of integers when holding all primes ");
  printf("below a certain Nmax. Integers have been used to store ");
  printf("our primes, and sizes below are in bytes.\n\n");
  

  /*
   * Here the headers for the table are printed.
   */
  printf("%s\t%s\t%s\t%s\n","Nmax","# of Primes","array size", "list size");

  /*
   * This for loop iterates over all integers from 2 to 200, passing
   * them as parameters in check_and_add_prime(). This creates our list
   * of primes one integer at a time.
   *
   * Below this, we have an if statement that executes every 5 integers.
   * Inside the if statement, the data for that row if the table is
   * printed. The purpose of the variables primes, asize, and lsize is
   * only to reduce the length of the print statement.
   *
   * Obviously at any point, the number of integers at or below i
   * will be the length of our list, as it contains only primes.
   * The size of the array will be (i-1)*sizeof(int), since it is a
   * collection if i-1 ints. The size of our list is the list length
   * mulitplied by the size of a listnode.
   */
  for(i=2; i <= 200; i++)
    {
      head = check_and_add_prime(head, i);
      if(i % 5 == 0)
        {
          int primes = listLength(head);
          long asize = (i-1)*sizeof(int);
          long lsize = listLength(head)*sizeof(struct ListNode);
          printf("%4d\t%11d\t%10ld\t%9ld\n", i, primes, asize, lsize);
          
        }
    }

  /*
   * Here I have printed a small caveat followed by the answer to
   * part d).
   */
  printf("\n\n");
  printf("Please note that this is completely dependent on the data type ");
  printf("used to store our primes, with smaller data types giving ");
  printf("more of an advantage to the array since the list must have ");
  printf("space for a pointer, which always takes 8 bytes on a");
  printf(" 64-bit machine.\n\n");

  printf("To answer part d), as we can see in the table above, the");
  printf(" array takes slightly less memory than the list if NMAX=100.");
  printf(" If NMAX=200, we can see that the list takes less memory.");
  printf(" We can also see that the crossover point is somewhere");
  printf(" between 120 and 125. I happen to know that below NMAX=122");
  printf(" the array takes less memory, above this the list takes");
  printf(" less memory, and at NMAX=122 they take exactly the same");
  printf(" amount of memory\n\n");
  
  /*
   * Finally, we must free the list.
   */
  
  freeList(head);

  return 0;
}
