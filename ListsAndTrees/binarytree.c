/* ************************************
* Kevin Cox
*
* implementation of binary tree 
************************************ */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "binarytree.h"

/* Alloc a new node with given data. */
struct TreeNode* createNode(int data)
{
	struct TreeNode* node = malloc(sizeof(struct TreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/* Insert data at appropriate place in BST, return new tree root. */
struct TreeNode* insertBST(struct TreeNode* root, int data)
{
	if (root == NULL) root = createNode(data);
	else if (data < root->data)
	{
		root->left = insertBST(root->left, data);
	}
	else root->right = insertBST(root->right, data);
	return root;
}

/* Return maximum value in non-empty binary search tree. */
int maxValueBST(struct TreeNode* root)
{
	if (root == NULL) return -1;
	else if (root->right == NULL) return root->data;
	else return maxValueBST(root->right);
}

/* Remove data from BST pointed to by rootRef, changing root if necessary.
 * For simplicity's sake, always choose node's in-order
 *   predecessor in the two-child case.
 * Memory for removed node should be freed.
 * Return 1 if data was present, 0 if not found. */
int removeBST(struct TreeNode** rootRef, int data)
{
	struct TreeNode* node;

	if (*rootRef == NULL) return 0;
	else if (data < (*rootRef)->data)
	{
		return removeBST(&((*rootRef)->left), data);
	}
	else if(data > (*rootRef)->data)
	{
		return removeBST(&((*rootRef)->right), data);
	}
	else
	{
		if ((*rootRef)->left == NULL)
		{
			node = *rootRef;
			*rootRef = (*rootRef)->right;
			free(node);
		}
		else if ((*rootRef)->right == NULL)
		{
			node = *rootRef;
			*rootRef = (*rootRef)->left;
			free(node);
		}
		else
		{
			(*rootRef)->data = maxValueBST((*rootRef)->left);
			return removeBST(&((*rootRef)->left), (*rootRef)->data);
		}
		return 1;
	}
}

/* Return maximum depth of tree. Empty tree has depth 0. */
int maxDepth(struct TreeNode* root)
{
	if(root == NULL) return 0;
	else
	{
		int leftDepth = maxDepth(root->left);
		int rightDepth = maxDepth(root->right);
		if (leftDepth > rightDepth) return 1+leftDepth;
		else return 1+rightDepth;
	}
}

/* A tree is balanced if both subtrees are balanced and
 * the difference in height between the subtrees is no more than 1.
 * Return 1 if tree is balanced, 0 if not. */
int isBalanced(struct TreeNode* root)
{
	int balanceFactor = 0;
	if (root == NULL) return 1;
	else
	{
		balanceFactor = maxDepth(root->left)-maxDepth(root->right);
		if (-1 <= balanceFactor && balanceFactor <= 1
			&& isBalanced(root->left) && isBalanced(root->right))
		{
			return 1;
		}
		else return 0;
	}
}

/*
* helper method taken from 
* http://www.geeksforgeeks.org/a-program-to-check-if-a-
*	binary-tree-is-bst-or-not/
*/
int isBSTUtil(struct TreeNode* node, int min, int max)
{ 
  /* an empty tree is BST */
	if (node==NULL) return 1;

  /* false if this node violates the min/max constraint */ 
	else if (node->data < min) return 0;
	else if (node->data > max) return 0;

  /* otherwise check the subtrees recursively, 
   tightening the min or max constraint */
	else return
		isBSTUtil(node->left, min, node->data) && 
		isBSTUtil(node->right, node->data, max);  
} 

/* Return 1 if tree is a binary search tree, 0 if not. */
int isBST(struct TreeNode* root)
{
	return(isBSTUtil(root, INT_MIN, INT_MAX));
}

/* use to help print the entire tree*/
void printTreeHelper(struct TreeNode* root)
{
	if (root != NULL)
	{
		printTreeHelper(root->left);
		printf("%d ", root->data);
		printTreeHelper(root->right);
	}
}

/* Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */
void printTree(struct TreeNode* root)
{
	printTreeHelper(root);
	printf("\n");
}

/* use to help print all leaves*/
void printLeavesHelper(struct TreeNode* root)
{
	if (root != NULL)
	{
		printLeavesHelper(root->left);
		printLeavesHelper(root->right);
		if (root->left == NULL && root->right == NULL)
		{
			printf("%d ", root->data);
		}
	}
}

/* Print data for leaves on single line,
 * separated with spaces, ending with newline.*/
void printLeaves(struct TreeNode* root)
{
	printLeavesHelper(root);
	printf("\n");
}

/* Free memory used by the tree. */
void freeTree(struct TreeNode* root)
{
	if(root != NULL)
	{
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}
