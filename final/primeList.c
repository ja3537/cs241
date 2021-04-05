/*******************************************************************************
 * Joseph Adams
 *
 * primeList.c is a program designed to build a singly linked list containing
 * all primes from 2 to NMAX. It then prints each prime on a new line.
 *
 * Feel free to change NMAX. NMAX should be more than 2 and small enough to
 * be in the range of int type.
********************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#define NMAX 200

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
      printf("%d\n", node->data);
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

struct ListNode* check_and_add_prime(struct ListNode* head, int n)
{
  if(head == NULL)
    {
      head = createNode(n);
      return head;
    }
  else if(n % head->data == 0) return head;
  else head->next = check_and_add_prime(head->next, n);
  return head;
}

int main(void)
{
  /*
   * i is used simply as an index for a for loop. head is a pointer to
   * a listnode which will point to the head of our list. 
   */
  int i;
  struct ListNode* head = NULL;

  /*
   * The following for loop is very simple. It iterates over all
   * integers from 2 to NMAX, passing them as a parameter in
   * check_and_add_prime(). If the integer is prime, it will be placed
   * in the list. If not, the list will remain the same.
   */
  
  for(i=2; i <= NMAX; i++) head = check_and_add_prime(head, i);

  /*
   * The list is then printed.
   */
  
  printList(head);

  /*
   * Finally, the list is freed.
   */
  
  freeList(head);

  return 0;
}

