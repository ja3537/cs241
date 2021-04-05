/*******************************************************************************
 * Joseph Adams
 *
 * binarytree.c is a source file implementing the functions found in
 * binarytree.h.
 * These functions are used to create and manipulate binary tree structures.
 *******************************************************************************/


#include "binarytree.h"
#include <stdio.h>
#include <stdlib.h>


/*******************************************************************************
 * createNode() is a very simple function which takes an integer as a
 * parameter, referred to as data. createNode() will use malloc to allocate
 * memory on the heap to create a new TreeNode struct. It will then set the
 * data in this TreeNode equal to data, set left and right pointer nodes to
 * NULL, and return a pointer to this new TreeNode.
*******************************************************************************/

struct TreeNode* createNode(int data)
{
  struct TreeNode* node = malloc(sizeof(struct TreeNode));
  node->left = NULL;
  node->right = NULL;
  node->data = data;
  return node;
}


/*******************************************************************************
 * insertBST() will use given data to create a new node and insert this
 * node into a BST in the appropriate place.
 *
 * insertBST() takes as parameters a pointer to the root of the tree, and an
 * integer representing the data of the node we wish to create and insert.
 * insertBST() returns a pointer to the root, which will be new if the tree
 * was empty when the function was called. So the proper usage is something
 * like root = insertBST(root, data); where root is a pointer to a node.
 *
 * If the pointer passed to the function is NULL, then this must be where
 * the new node goes, and the function creates a node and places it here.
 * 
 * The function recursively calls itself. Assuming the current node is not
 * NULL, then the input data is compared to the data of the current node. If
 * it is less, the function will call itself with the left node of the
 * current node. If it is more, it will use the right node. Obviously, the 
 * recursion will continue until it finds a node which is NULL, and it will
 * be the correct place for the new node.
*******************************************************************************/

struct TreeNode* insertBST(struct TreeNode* root, int data)
{
  if(root == NULL)
    {
      root = createNode(data);
      return root;
    }
  else if(data < root->data) root->left = insertBST(root->left, data);
  else if(data > root->data) root->right = insertBST(root->right, data);
  return root;
}

/*******************************************************************************
 * connect() is a helper function used by removeBST() to alter the BST after
 * the node to be removed is found. It takes as a parameter the  pointer to
 * the pointer to the node to be removed. It is not connect's job to find or
 * remove this node, but to alter the rest of the graph to connect correctly.
 *
 * TreeNode pointers right and left point to the right and left nodes of the
 * node to be removed. The reason for declaring the local variables is so
 * when a replacement for our node is found, they can be connected to it.
 *
 * replacement and ancestor are TreeNode pointers which will point to the
 * replacement for our removed node, and its parent. If the tree is 
 * complete enough, the replacement will be the node with the next highest
 * value in the right subtree. This is found by locating the leftmost node
 * of that subtree. A while loop is used to move down the tree to the left
 * until we find a node where node-> left is NULL. This is the replacement.
 *
 * If the replacement has a right child node, then this child node is put in
 * the place of replacement as ancestor's left child node. Otherwise,
 * ancestor's left child node will be NULL. The node to be removed is then
 * replaced by replacement and right and left are connected.
 *
 * If there is no right subtree for our removed node, it is replaced by the
 * first node of the left subtree. 
*******************************************************************************/

void connect(struct TreeNode** parentnext)
{
  struct TreeNode* right = (*parentnext)->right;
  struct TreeNode* left = (*parentnext)->left;
  struct TreeNode* ancestor;
  struct TreeNode* replacement;
  
  if(right == NULL)
    {
      *parentnext = left;
      return;
    }
  ancestor = right;
  if(ancestor->left != NULL)
    {
      replacement = ancestor->left;
      while(replacement->left != NULL)
        {
          ancestor = replacement;
          replacement = replacement->left;
        }
      if(replacement->right != NULL)
        {
          ancestor->left = replacement->right;
        }
      else ancestor->left = NULL;
      *parentnext = replacement;
      replacement->left = left;
      replacement->right = right;
      return;
    }
  else
    {
      *parentnext = right;
      right->left = left;
      return;
    }
}

/*******************************************************************************
 * removeBST() is used to remove a node with given data from a binary search
 * tree. If such a node is found, the node is removed and a 1 is returned. If
 * not, 0 is returned.
 *
 * removeBST() is relatively simple because of the connect() helper function.
 * removeBST() simply has the job of determining where the data is in the BST
 * if it exists. It does this by recursively calling itself on either the
 * left or right child node (left if data is smaller than data of the current
 * node, right if bigger).
 *
 * Once the node is found, the local treenode pointer delete will point to it.
 * Then connect() is invoked to create the new BST and memory for delete is
 * freed. Then 1 is returned.
 *
 * If a NULL child is found before the data, it must not be in the BST and
 * 0 is returned.
 *
 * The local variable result is used simply to propogate the returned value
 * of our function through the nested recursions.
*******************************************************************************/

int removeBST(struct TreeNode** rootRef, int data)
{
  struct TreeNode* delete;
  int result;

  delete = *rootRef;
  if(*rootRef == NULL) return 0;
  if(delete->data == data)
    {
      connect(rootRef);
      free(delete);
      return 1;
    }
  if(data < (*rootRef)->data) result = removeBST(&((*rootRef)->left), data);
  else result = removeBST(&((*rootRef)->right), data);
  return result;      
}

/*******************************************************************************
 * minValueBST() is a function designed to return the minimum value of a BST.
 * It takes a pointer to the root of the BST as a parameter.
 * 
 * The minimum value of a BST is the leftmost node. minValueBST() finds this
 * node by recursively calling itself on the left child until it finds a node
 * whose left child is NULL. It then returns the data of this node.
 *
 * The function should not be used on an empty tree, but if it is, it will
 * return 0.
*******************************************************************************/

int minValueBST(struct TreeNode* root)
{
  if(root == NULL) return 0;
  if(root->left == NULL) return root->data;
  else return minValueBST(root->left);
}

/*******************************************************************************
 * maxDepth() is a function designed to find the depth of a binary tree. It
 * takes a pointer to the root of the binary tree as a parameter.
 *
 * It makes its way through every node in the tree by recursively calling
 * itself on the children of each node. The depth of these children are
 * assigned to the local variables left and right. The larger of these two is
 * taken, one is added to it, and this number is assigned to the local
 * variable depth, as it is the depth of this node.
 *
 * The recursion is stopped when it is called on a node that is NULL, in
 * which case 0 is returned. So used on an empty tree, the depth returned is
 * 0. If used on tree of 1 node, depth is 1. If this node has children, 
 * depth is 2, etc.
*******************************************************************************/

int maxDepth(struct TreeNode* root)
{
  int left;
  int right;
  int depth;

  if(root == NULL) return 0;
  left = maxDepth(root->left);
  right = maxDepth(root->right);
  depth = (right > left) ? right + 1 : left + 1;
  return depth;

}

/*******************************************************************************
 * isBalanced_recursive() is a helper function for isBalanced(). Together,
 * they are designed to determine if a binary tree is balanced (ie, if the
 * difference in depth between adjacent subtrees is no more than 1).
 *
 * This function takes a pointer to a node as a parameter.
 *
 * isBalanced_recursive takes care of the recursive aspects of the process.
 * it returns an array *arr with two integer elements allocated by malloc. The
 * first element represents the depth of the node, and the second represents
 * whether it, and all of the nodes beneath it, are balanced.
 *
 * isBalanced_recursive works in a very similar way to maxDepth in that it
 * recursively calls itself on the children of any given node and keeps track
 * of the depth of each node. The difference is that it also compares the
 * depth of children to ensure their difference (local variable diff)
 * is not greater than 1. If it is, it must be an imbalanced tree.
 *
 * If any of the second elements of the arrays passed by the children of a
 * node are 0, then it must be an imbalanced subtree, and the second element
 * of *arr for our node is also set to 0.
 *
 * The local integer pointers left and right are just used to point to the
 * arrays returned by the left and right function calls. They are freed before
 * the function terminates. 
*******************************************************************************/

int* isBalanced_recursive(struct TreeNode* root)
{
  int *arr = malloc(2*sizeof(int));
  int *left;
  int *right;
  int diff;

  if(root == NULL)
    {
      arr[0] = 0;
      arr[1] = 1;
      return arr;
    }

  left = isBalanced_recursive(root->left);
  right = isBalanced_recursive(root->right);
  arr[0] = (right[0] > left[0]) ? right[0] + 1 : left[0] + 1;
  diff = right[0] - left[0];
  if((diff >= -1) && (diff <= 1)) diff = 1;
  else diff = 0;
  arr[1] = (left[1] && right[1] && diff);

  free(left);
  free(right);
  return arr;
}
  

/*******************************************************************************
 * isBalanced() and isBalanced_recursive() work together to determine if a
 * given binary tree is balanced. isBalanced is meant to receive a pointer to
 * the root of the tree as a parameter.
 * 
 * isBalanced() is a very simple function as isBalanced_recursive() does the
 * heavy lifting. *arr is a local pointer to an integer used to receive the
 * array returned from isBalanced_recursive. The second element of this array
 * shows whether the tree is balanced or not. The array is freed before
 * returning this value. It will return 1 if the tree is balanced and 0
 * if not.
*******************************************************************************/

int isBalanced(struct TreeNode* root)
{
  int balanced;
  int *arr = isBalanced_recursive(root);
  balanced = arr[1];
  free(arr);
  return balanced;
}

/*******************************************************************************
 * isBST_recursive() is a helper function for isBST(). Together they determine
 * if a given binary tree is a binary search tree. If so, isBST() returns 1.
 * 0 is returned if not.
 *
 * Essentially isBST_recursive returns a 3 element array (local variable arr),
 * where the first element is the smallest number found in the tree, the
 * second element is the largest, and the last element is whether the tree
 * is a BST.
 *
 * The function recursively calls itself on the children of our node to start
 * from the leaves of the tree. It assigns the local integer pointers left
 * and right to the arrays resulting from these function calls.
 *
 * Obviously, if the left child is missing, the node itself contains the
 * smallest number found. Similarly, if right child is missing, it is the
 * largest.
 *
 * The local variables leftcorrect and rightcorrect are used to determine if
 * our tree is a BST. leftcorrect checks to make sure the largest number
 * of the left subtree is less than the data of our node, and also checks
 * if the left subtree is a BST by looking at the third element of left.
 * Similarly, rightcorrect makes sure the smallest number of the right
 * subtree is still larger than the data of our node. If both rightcorrect
 * and leftcorrect are 1, then the third element of the returned array is
 * set to 1.
 *
 * the arrays pointed to by left and right are freed after the function is
 * done with them. 
 *
 * This function does not classify an empty tree as a BST.
*******************************************************************************/

int* isBST_recursive(struct TreeNode* root)
{
  int *arr = malloc(3*sizeof(int));
  int *left;
  int *right;
  int leftcorrect;
  int rightcorrect;
  
  if(root == NULL)
    {
      printf("root is null\n");
      arr[0] = 0;
      arr[1] = 0;
      arr[2] = 0;
      return arr;
    }
  
  if(root->left != NULL)
    {
      left = isBST_recursive(root->left);
      arr[0] = left[0];
      leftcorrect = (left[1] < root->data) && left[2];
      free(left);
    }
  else
    {
      arr[0] = root->data;
      leftcorrect = 1;
    }
  if(root->right != NULL)
    {
      right = isBST_recursive(root->right);
      arr[1] = right[1];
      rightcorrect = (right[0] > root->data) && right[2];
      free(right);
    }
  else
    {
      arr[1] = root->data;
      rightcorrect = 1;
    }
  arr[2] = leftcorrect && rightcorrect;
  return arr;
}

/*******************************************************************************
 * isBST() and isBST_recursive() work together to determine if a tree is a
 * binary tree or not. isBST() returns a 1 if it is and a 0 if not. isBST()
 * should take a pointer to the tree root as a parameter.
 *
 * isBST() is a very simple function because isBST_recursive() does the heavy
 * lifting. The local pointer to an integer *arr points to the array returned
 * by isBST_recursive(). The local integer isBST is set to the third element
 * of this array, and the array is freed. Then isBST is returned.
*******************************************************************************/

int isBST(struct TreeNode* root)
{
  int *arr;
  int isBST;
  arr = isBST_recursive(root);
  isBST = arr[2];
  free(arr);
  return isBST;
}

/*******************************************************************************
 * printTree_recursive() is a helper function for printTree(). Together they
 * print the nodes of any tree. These nodes will be printed in order if that
 * tree is a BST.
 *
 * printTree_recursive() does not return a value. It is a recursive function
 * which first calls itself with the left child of each node, then prints
 * the data in the current node, then calls itself with the right child. The
 * result is the data of the left child will be printed before the data of
 * the current node, and this data will be printed before the data of the
 * right node. The result is an in order printing of the nodes for a BST.
 *
 * This function takes a pointer to the node of a tree as a parameter.
*******************************************************************************/

void printTree_recursive(struct TreeNode* root)
{
  if(root == NULL) return;
  if(root->left != NULL) printTree_recursive(root->left);
  printf("%d ", root->data);
  if(root->right != NULL) printTree_recursive(root->right);
}

/*******************************************************************************
 * printTree() and printTree_recursive() work together to print the nodes of
 * any tree followed by a newline. These nodes are printed in order if the
 * tree is a BST.
 *
 * The only reason printTree() exists is to call printTree_recursive() and to
 * print a newline when printTree_recursive() is finished. It does not return
 * a value.
 *
 * This function takes a pointer to the node of a tree as a parameter.
*******************************************************************************/

void printTree(struct TreeNode* root)
{
  printTree_recursive(root);
  printf("\n");
}


/*******************************************************************************
 * printLeaves_recursive is a helper function for printLeaves. Together, they
 * print the leaves of a tree.
 *
 * printLeaves_recursive is a function that recursively calls itself using
 * pointers to the children of our node. This occurs until it reaches a leaf,
 * where it prints the data in the leaf.
 *
 * This function does not return anything and takes a pointer to a node as a
 * parameter.
*******************************************************************************/

void printLeaves_recursive(struct TreeNode* root)
{
  if(root->left == NULL && root->right == NULL) printf("%d ", root->data);
  if(root->left != NULL) printLeaves_recursive(root->left);
  if(root->right != NULL) printLeaves_recursive(root->right);
}

/*******************************************************************************
 * printLeaves() and printLeaves_recursive() work together to print the leaves of
 * a tree.
 *
 * printLeaves() is a simple function. Its only jobs are to call
 * printLeaves_recursive() and to print a newline afterward.
 *
 * This function does not return anything and takes a pointer to a node as a
 * parameter.
*******************************************************************************/

void printLeaves(struct TreeNode* root)
{
  printLeaves_recursive(root);
  printf("\n");
}

/*******************************************************************************
 * freeTree() is a function that, when passed a pointer to the root of a tree,
 * will free the entire tree. It frees from the bottom of the tree to the top.
 * In order to do this, it recursively calls itself using the children of our
 * node. After these calls, it frees the node itself.
*******************************************************************************/

void freeTree(struct TreeNode* root)
{
  if(root->left != NULL) freeTree(root->left);
  if(root->right != NULL) freeTree(root->right);
  free(root);
}

