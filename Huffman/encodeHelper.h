#include <stdio.h>
#include "huffman.h"
#include <stdlib.h>
#include "tree.h"

unsigned long frequencyArray[255];

struct TreeNode* createNode(unsigned long frequency, unsigned char letter)
{
	TreeNode* node = malloc(sizeof(TreeNode));
	node->frequency = frequency;
	node->letter = letter;
	node->left = NULL;
	node->right = NULL;
	return node;
}

struct TreeNode* createSortedList(TreeNode* head, unsigned long frequency, 
	unsigned char letter)
{
	struct TreeNode* new;
	if (head == NULL || frequency > head->frequency)
	{
		new = createNode(frequency, letter);
		new->right = head;		/*update head of list*/
		return new;
	}
	else
	{
		head->right = createSortedList(head->right, frequency, letter);
		return head;
	}
}

/* Insert data at head of list, return new list head. */
struct TreeNode* pushStack(TreeNode* head, unsigned long frequency, 
	unsigned char letter)
{
	struct TreeNode* newHead = createNode(frequency, letter);
	newHead->right = head;
	return newHead;
}

/* use to help print the entire tree*/
void printTreeHelper(TreeNode* root)
{
	if (root != NULL)
	{
		printTreeHelper(root->left);
		printf("%d %c ", root->frequency, root->letter);
		printTreeHelper(root->right);
	}
}

/* Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */
void printTree(TreeNode* root)
{
	printTreeHelper(root);
	printf("\n");
}

/* Print list data on single line, separated with spaces and ending
 * with newline. */
void printList(TreeNode* head)
{
	struct TreeNode* current = head;

	while(current != NULL)
	{
		printf("%d ", current->frequency);
		current = current->right;
	}
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

void asciiHelper(int c)
{
	if ((c  < 33) || (c > 126)) printf("=%d\t", c);
	else printf("%c\t", c);
}

void getCode()
{
	printf("0\n");
}

void printHelper()
{
	int i;
	printf("Symbol\tFreq\tCode\n");

	for (i = 0; i < 255; ++i)
	{
		if (frequencyArray[i] != 0)
		{	
			asciiHelper(i); 			  	   	/*Symbol*/
			printf("%lu\t", frequencyArray[i]); /*Frequency*/
			getCode(i, frequencyArray[i]);		/*Code*/	
		}
	}
}