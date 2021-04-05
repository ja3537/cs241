/*******************************************************************************
 * Joseph Adams
 *
 * linkedlist.c is a source file implementing the functions found in
 * linkedlist.h. These functions are used to create and manipulate linked
 * list structures.
 *******************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"


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
 * insertSorted() is used to create a node with parameter data, and insert it
 * into a sorted list at the appropriate place. A pointer to the head of our
 * sorted list is passed as a parameter, and a pointer to the head of the new
 * list is returned.
 *
 * The function has two local parameters and both are pointers to nodes.
 * new points to the node to be inserted. previous is used to find the node
 * that will ultimately precede our new node when it is inserted.
 *
 * One special circumstance is if the list is empty. In this case, the new
 * node is set as the head and returned.
 *
 * Another special case is if the data in the new node is smaller than the
 * head data. In this case, the next pointer of our new node is set to the
 * head and the new node is returned.
 *
 * Otherwise the appropriate place is found using a while loop. If the
 * appropriate place is the end of the list, the while loop will continue
 * until a node is reached where the next node is NULL. Then the new node is
 * placed as the next node. If the appropriate place is between two nodes,
 * then first the new node sets its next pointer to be equal to previous next
 * pointer. Then previous next pointer is set to our new node.
*******************************************************************************/
struct ListNode* insertSorted(struct ListNode* head, int data)
{
  struct ListNode* new = createNode(data);
  struct ListNode* previous = head;

  if(head == NULL)
    {
      head = new;
      return head;
    }
  else if(data < head->data)
    {
      new->next = head;
      return new;
    }
  while(1)
    {
      if(previous->next == NULL)
        {
          previous->next = new;
          return head;
        }
      else if(previous->data <= data && data <= previous->next->data)
        {
          new->next = previous->next;
          previous->next = new;
          return head;
        }
      else
        {
          previous = previous->next;
        }
    }
}

/*******************************************************************************
 * removeItem() takes a pointer to a pointer to the head of a linked list as
 * one parameter, and an integer data as the other. The functions job is to
 * search the linked list for a node containing data that matches ours
 * and remove it. If the data is found, the function returns 1. If not, it
 * returns 0.
 *
 * The function has two local variables: remove and parent, both of which are
 * pointers to nodes. The function makes its way down the list using the
 * remove pointer in a while loop, which terminates either when the data in
 * remove matches our input data, or the node is NULL. parent always points to
 * the previous node so that proper connections can be made once the remove
 * node is found.
 *
 * When the node is found, parent->next is set to the node after the node to 
 * be removed. At this point, the node to be removed is freed.
 *
 * Obviously the case where the head contains the data must be a special case
 * where there is no previous node and no new connections need to be made.
 * Here the pointer to head needs to be adjusted to point to the next node.
*******************************************************************************/

int removeItem(struct ListNode** headRef, int data)
{
  struct ListNode* remove;
  struct ListNode* parent = *headRef;

  if(parent == NULL) return 0;
  if(parent->data == data)
    {
      *headRef = parent->next;
      free(parent);
      return 1;
    }
  while(parent->next != NULL)
    {
      if(parent->next->data == data)
        {
          remove = parent->next;
          parent->next = parent->next->next;
          free(remove);
          return 1;
        }
      else parent = parent->next;
    }
  return 0;
}

/*******************************************************************************
 * pushStack() is a function which takes a pointer to a node and an integer
 * data as parameters. Its job is to add another node to the stack pointed
 * to by the parameter head. Stacks work LIFO, so the new node added to the
 * stack is returned as the new head.
 *
 * This function is simple as it just uses createNode() to make the new node,
 * connects to the old head by making new->next point to the old head, and
 * finally returns the new node as the new head.
*******************************************************************************/

struct ListNode* pushStack(struct ListNode* head, int data)
{
  struct ListNode* new = createNode(data);
  new->next = head;
  return new;
}

/*******************************************************************************
 * popStack is a simple function which pops the most recent node off the stack
 * and returns the integer data in that node. This function takes a pointer
 * to a pointer which points to the head of the stack as a parameter.
 *
 * This function has two local variables: one is a pointer to a node called
 * pop, which points to the node to be popped off the stack (the original
 * head). The other is an int data, which is used to store the data in pop
 * when pop is freed.
 *
 * pop is assigned, data is assigned, the pointer pointing to the pointer of
 * the last head is reassigned to point to the next node, pop is freed, and
 * data is returned.
*******************************************************************************/

int popStack(struct ListNode** headRef)
{
  struct ListNode* pop = *headRef;
  int data = pop->data;
  *headRef = pop->next;
  free(pop);
  return data;
}

/*******************************************************************************
 * listLength() is a simple function which takes a pointer to the head node
 * of a list and returns the length of that list.
 *
 * It has two local variables. One is a pointer to a node called node, which
 * is used to point to nodes iteratively down the list. The other local
 * variables is count, which is an integer that iterates each time a non-NULL
 * node is found.
 *
 * The function uses a while loop that terminates when the next node is NULL.
 * When the next node is not null, the pointer node is made to point at
 * it and count is iterated. Once the next pointer is NULL, the end of the
 * list has been reached and count is returned.
*******************************************************************************/

int listLength(struct ListNode* head)
{
  struct ListNode* node = head;
  int count = 0;
  if(node == NULL) return count;
  else
    {
      count++;
      node = node->next;
    }
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
 * pointed to, the data in the node is printed. For every node other than
 * the head, a comma followed by a space is printed first. After node has
 * made its way down the list, a newline is printed. The function does not
 * return anything.
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
 * A while loop is used to make node point to head, then head point to the
 * next node, and free node. As long as head is not null, the loop continues
 * down the list, freeing the nodes one by one.
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
 * recursiveReverse() is a helper function for reverseList(). Together, they
 * reverse the order of a linked list.
 *
 * recursiveReverse() does most of the work and its job is to reverse the
 * list and return a pointer to the new head.
 *
 * This is a recursive function which calls itself on the next node as long
 * as the next node is not NULL. If it is NULL, then the current node must
 * be the new head, which is returned to the last call.
 *
 * As the new head is passed up the chain of function calls, each function
 * call will set the next pointer of the next node(next in terms of the
 * original ordering) to point to the current node. Then it will have the
 * next pointer of the current node point to NULL, which will be changed by
 * the next function call provided it is not the last call, in which case
 * the current node is the old head and should point to NULL since it is now
 * the end of the list.
 *
 * The function uses two local variables, both of which are pointers to nodes.
 * newHead is used to pass the newHead (the old end of the list) up the chain
 * of recursive function calls. The other is node which is simply used to
 * point to the current node.
*******************************************************************************/

struct ListNode* recursiveReverse(struct ListNode** headRef)
{
  
  struct ListNode* newHead;
  struct ListNode* node = *headRef;
  if(node == NULL) return NULL;
  if(node->next != NULL)
    {
      newHead = recursiveReverse(&(node->next));
      node->next->next = node;
      node->next = NULL;
    }
  else
    {
      newHead = node; 
    }
  return newHead;
  
}

/*******************************************************************************
 * reverseList() works together with the helper function recursiveReverse() to
 * reverse a list.
 *
 * reverseList has only one parameter which is a pointer to a pointer to the
 * head of the list to be reversed. Its only job is to call recursiveReverse()
 * and set the pointer pointing to the head of the list equal to the pointer
 * returned by recursiveReverse(), which is the new head of the reversed
 * list.
*******************************************************************************/

void reverseList(struct ListNode** headRef)
{
  *headRef = recursiveReverse(&*headRef);
}

