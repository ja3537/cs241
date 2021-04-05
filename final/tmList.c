/*******************************************************************************
 * Joseph Adams
 *
 * tmList.c is a program designed to generate iterations of the Thue-Morse
 * sequence and store the bits in a linked list. The integer iterations in
 * main() controls how many iterations are stored and printed. Feel free to
 * change the value of iterations to suit your needs.
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
 * pointed to, the data in the node is printed followed by a space.
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
      printf("%d ", node->data);
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
 * insertNode() is used to insert a new node with the given data at the end
 * of a list.
 *
 * It takes as parameters a pointer to the head node of the list, and an
 * int of the data the new node should have. It returns a pointer to a
 * list node.
 *
 * If the head passed is NULL, this must be an empty list. So a new
 * node is created using createNode(), the head is assigned to point to it,
 * and the head is returned.
 *
 * If the node is not null and the next node is also not null, insertNode()
 * calls itself recursively with head->next as the passed pointer. head->next
 * is assigned to the pointer returned by this function call. This recursion
 * is what allows the function to make its way down the list.
 *
 * This recursion is terminated in the event that the next node is NULL,
 * handled by the else statement. In this event, the next node is assigned to
 * the new node, made with createNode() and the input data.
*******************************************************************************/


struct ListNode* insertNode(struct ListNode* head, int data)
{
  if(head == NULL) head = createNode(data);
  else if(head->next != NULL) head->next = insertNode(head->next, data);
  else head->next = createNode(data);

  return head;
     
}

/*******************************************************************************
 * iterateTM is a function used to iterate a list containing the Thue-Morse
 * sequence by 1. It takes the head node and the current list length as
 * parameters, and does not return anything.
 *
 * It is a pretty simple function. The local variable i is used as an
 * index in the for loop. The for loop is used to iterate down the list.
 * For each node, the function looks at the data in that node, and if it is
 * 1, the local variable data is assigned to 0, and otherwise it is assigned
 * to 1.
 *
 * A new node with this data is then added to the end of the list using
 * insertNode.
 *
 * The node is then made to point to the next node to keep iterating down the
 * list. The for loop stops after the last node of the input list has been
 * reached.
*******************************************************************************/

void iterateTM(struct ListNode* node, int length)
{
  int i;
  for(i = 0; i < length; i++)
    {
      int data = (node->data == 1) ? 0 : 1;
      insertNode(node, data);
      node = node->next;
    }
}

/*******************************************************************************
 * loadTM() is used along with iterateTM to generate a Thue-Morse sequence in
 * a list with the head already having data of 0. It takes as parameters a
 * pointer to this head node, along with an integer iterations indicating how
 * many iterations of the Thue-Morse sequence are desired. This function does
 * not return anything.
 *
 * It is a very simple function. It uses a for loop to call iterateTM
 * (iterations-1) times, passing the head node each time. When iterateTM() is
 * called, it iterates the sequence once. The reason it is called
 * (iterations-1) rather than iterations times is because the head node
 * passed to loadTM() already should contain 0, which is the first iteration.
*******************************************************************************/

void loadTM(struct ListNode* head, int iterations)
{
  for(; iterations > 1; iterations--)
    {
      iterateTM(head, listLength(head));
    }
}

/*******************************************************************************
 * The main() function is very simple. It has two local variables. The first
 * is iterations, which is an integer used to indicate how many iterations of
 * the TM sequence is desired. The other is a pointer to a list node head,
 * which is made to point at a newly created node with data 0.
 *
 * Then the TM sequence is generated using loadTM() and these local variables.
 * Then a print statment is made with instructions on the program, and
 * the TM sequence generated is printed using printList().
 *
 * finally, the list is freed using freeList().
*******************************************************************************/

int main(void)
{
  int iterations = 15;
  struct ListNode* head = createNode(0);

  loadTM(head, iterations);

  printf("Feel free to set iterations in main() to whatever you like. It is"); 
  printf(" currently %d, resulting in a sequence length of %d\n",
         iterations, listLength(head));

  printList(head);

  freeList(head);


  return 0;
}
