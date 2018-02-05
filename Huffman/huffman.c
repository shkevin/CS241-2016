/* ************************************
* Kevin Cox
* 20161124 
* Common functions needed to compress
* or decompress files.
************************************ */

#include <stdio.h>
#include "huffman.h"
#include <stdlib.h>
#include "treeAndList.h"
#include <string.h>

#define DEBUG 0

unsigned long frequencyArray[256]; /*stores letters at ascii code value*/
long totalCodesSize = 0;

/* ************************************************
* PARAMETERS: int/char value.
* FUNCTION: determines if int is within ascii range
* RETURNS: None.
************************************************* */
void asciiHelper(int c)
{
	if ((c  < 33) || (c > 126)) printf("=%d ", c);
	else printf("%c ", c);
}

/* **************************************************
* PARAMETERS: frequency of char, letter associated
* FUNCTION: creates new node for list view and tree
* RETURNS newely created node.
*************************************************** */
TreeNode* createNode(unsigned long frequency, unsigned char letter)
{
	TreeNode* node = malloc(sizeof(TreeNode));
	node->frequency = frequency;
	node->letter = letter;
	node->next = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/* **************************************************
* PARAMETERS: parent node to traverse
* FUNCTION: simply grabs right most leaf of parent
* RETURNS right most leaf letter
*************************************************** */
unsigned char grabRightMostLeaf(TreeNode* head)
{
	if (head->right == NULL) return head->letter;
	else return grabRightMostLeaf(head->right);
}

/* **************************************************
* PARAMETERS: head node/list, frequency of node,
* 			  letter of associated node.
* FUNCTION: insertion sort for list view.
* RETURNS: new head of list.
*************************************************** */
TreeNode* createSortedTree(TreeNode* head, TreeNode* parent)
{
	TreeNode* current = head; /*temp head to traverse list/tree*/
	/*if frequency of parent is out of order*/
	if (head == NULL || parent->frequency <= head->frequency)
	{
		parent->next = head;
		head = parent;
		return head;
	}
	else
	{
		/*grabs the node before parent's placement (frequency weighted)*/
		while(current->next &&
			current->next->frequency < parent->frequency)
		{
			current = current->next;
		}
		/*grabs the node before parent's placement (letter weighted)*/
		while(current->next &&
			current->next->frequency == parent->frequency &&
			grabRightMostLeaf(current->next) > grabRightMostLeaf(parent))
		{
			current = current->next;
		}
		/*insert parent node in correct position*/
		parent->next = current->next;
		current->next = parent;
		return head;
	}
}

ListNode* createListNode(unsigned char letter)
{
	ListNode* node = malloc(sizeof(ListNode));
	node->letter = letter;
	node->code = 0;
	node->next = NULL;
	node->codeLength = 0;
	return node;
}

ListNode* insertNode(ListNode* node, unsigned char letter)
{
	ListNode* new;
	if (node == NULL)
	{
		new = createListNode(letter);
		new->next = node;
		return new;
	}
	else
	{
		node->next = insertNode(node->next, letter);
		return node;
	}
}

/* ************************************************
* PARAMETERS: head of list, size of list.
* FUNCTION: recursively build tree, readds parent
* 			to the list and continues building
* 			until list size is 1.
* RETURNS: current head of tree.
************************************************* */
TreeNode* buildTree(TreeNode* head, long listSize)
{
	TreeNode* parent = NULL; /*parent node to first, second*/
	TreeNode* first = NULL; /*first to be popped off*/
	TreeNode* second = NULL; /*second to be popped*/
	long combinedFrequency = 0; 
	if (listSize <= 1) return head; /*if built up to final root*/
	else
	{
		first = head;
		second = popList(&head);
		combinedFrequency = (first->frequency) + 
		(second->frequency);
		parent = createNode(combinedFrequency, 00);
		if (DEBUG)
		{
			printf("parent: %lu ", parent->frequency);
			printf("combined: %lu letter ", first->frequency);
			asciiHelper(grabRightMostLeaf(first));
			printf("and %lu letter ", second->frequency);
			asciiHelper(grabRightMostLeaf(second));
			printf("\n");
		}
		parent->right = second; /*setting children nodes here*/
		parent->left = first;
		head = createSortedTree(head, parent); /*re-sort nodes of tree*/
		head = popList(&head); /*pop second off*/
		if(DEBUG) printTreeList(head);
		listSize--;
		return buildTree(head, listSize);
		free(parent);
	}
}

/* ************************************************
* PARAMETERS: head of list.
* FUNCTION: pops head of list off, updates new head
* RETURNS: new head of list.
************************************************* */
TreeNode* popList(TreeNode** headRef)
{
	TreeNode* updatedNode = *headRef;
	if (updatedNode->next != NULL)
	{
		*headRef = updatedNode->next;
	}
	updatedNode = NULL;
	free(updatedNode);
	return *headRef;
}

/* ************************************************
* PARAMETERS: root node/head.
* FUNCTION: helper to recursively print tree.
* RETURNS: None.
************************************************* */
void printTreeHelper(TreeNode* root)
{
	if (root != NULL)
	{
		printTreeHelper(root->left);
		/*if node is not a parent, the print letter*/
		if (root->letter != 00) asciiHelper(root->letter);
		/*otherwise print frequency for debugging*/
		else printf("%lu ", root->frequency);
		printTreeHelper(root->right);
	}
}

/* ************************************************
* PARAMETERS: root node/head.
* FUNCTION: Print data for inorder tree traversal 
* 			on single line, separated with spaces, 
* 			ending with newline.
* RETURNS: None.
************************************************* */
void printTree(TreeNode* root)
{
	printTreeHelper(root);
	printf("\n");
}

/* ************************************************
* PARAMETERS: head of list.
* FUNCTION: Print list data on single line, 
* 			separated with spaces and ending with 
* 			newline. 
* RETURNS: None.
************************************************* */
void printTreeList(TreeNode* head)
{
	struct TreeNode* current = head;
	while(current != NULL)
	{
		/*if node is not a parent node*/
		if (current->letter != 00) asciiHelper(current->letter);
		else
		{
			printf("[");
			asciiHelper(grabRightMostLeaf(current));
			printf("]");
			printf("%lu ", current->frequency);
		}
		current = current->next;
	}
	printf("\n");
}

/* ************************************************
* PARAMETERS: root node/head.
* FUNCTION: free the memory used by the tree.
* RETURNS: None.
************************************************* */
void freeTree(struct TreeNode* root)
{
	if(root != NULL)
	{
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

/* ************************************************
* PARAMETERS: root, temp array, current position,
*			  letter searching for.
* FUNCTION: searches tree for code of leaf
* RETURNS: None.
************************************************* */
void getCode(TreeNode* root, char arr[], int current, 
	unsigned char letter, ListNode* head)
{
	int i;
	char* temp;
    if (root->left) /*if root's left node != null*/
	{
		arr[current] = 0;
		getCode(root->left, arr, current + 1, letter, head);
	}
    if (root->right) /*if root's right node != null*/
	{
		arr[current] = 1;
		getCode(root->right, arr, current + 1, letter, head);
	}
	if (!root->left && !root->right && 
    	root->letter == letter) /*if we found the letter*/
	{
		totalCodesSize += (current * root->frequency);
		temp = malloc((current)*sizeof(char));
		for (i = 0; i < current; i++)
		{
        	printf("%d", arr[i]); /*print built up code*/ 
        	temp[i] = arr[i];
		}
		for (i = current; i < 256; ++i)
		{
			arr[i] = '\0';
		}
		head->codeLength = current;
		head->code = temp;
	}
}

void printByte(unsigned char b)
{
	int i = 0x80;
	for(; i > 0; i >>= 1 ) putchar(b & i ? '1' : '0');
		putchar('\n');
}

/* ************************************************
* PARAMETERS: running code, file out
* FUNCTION: writes binary to out.
* RETURNS: None. 
************************************************* */
void writeBinary(char* builtUpCode, FILE* out)
{
	long i;
	unsigned char byte = 0;
	for (i = 0; i < totalCodesSize; i++)
	{
		char bit = builtUpCode[i];
		if ((i % 8) == 0 && i > 0)
		{
			fputc(byte, out);
			byte = 0;
		}
		if (bit == 1) byte |= (1 << (7 - (i % 8)));
	}
	fputc(byte, out);
}

/* ************************************************
* PARAMETERS: None.
* FUNCTION: iterates through frequencyArray to 
* 			print symbol and frequency of letter.
* RETURNS: None. 
************************************************* */
void printHelper(TreeNode* root, ListNode* head, FILE* out)
{
	int i;
	char arr[256] = {0}; 	/*storage for single code*/
	printf("Symbol\tFreq\tCode\n");
	for (i = 0; i < 256; i++)
	{
		if (frequencyArray[i] != 0)
		{	
			fputc(i, out);
			fwrite(&frequencyArray[i], sizeof(unsigned long), 1, out);
			asciiHelper(i); 			  	   	  /*Symbol*/
			printf("\t%lu\t", frequencyArray[i]); /*Frequency*/
			getCode(root, arr, 0, i, head);	 	  /*Code*/	
			head = head->next;
			printf("\n");
		}
	}
}

ListNode* getCodeFromList(ListNode* head, unsigned char letter)
{
	if (head->letter == letter) return head;
	if (head->next == NULL) return NULL;
	return getCodeFromList(head->next, letter);
}

void writeToFile(unsigned char* buffer, ListNode* head, long fileSize, 
	FILE* out)
{
	int i, j;
	char* code;
	unsigned char letter;
	ListNode* current;
	char* builtUpCode = malloc(totalCodesSize*sizeof(char));
	long index = 0;

	for (i = 0; i < fileSize; i++)
	{
		letter = buffer[i];
		current = getCodeFromList(head, letter);
		code = current->code;
		if(DEBUG) printf("%c: ", current->letter);
		for (j = 0; j < current->codeLength; ++j)
		{
			builtUpCode[index] = code[j];
			if(DEBUG) printf("%d", builtUpCode[index]);
			index++;
		}
		if(DEBUG) printf("\n");
	}
	writeBinary(builtUpCode, out);
	free(builtUpCode);
}

/* Free memory used by the list. */
void freeList(struct ListNode* head)
{
	struct ListNode* current = head;
	if (current != NULL)
	{
		freeList(current->next);
		free(current);
	}
}

/* ************************************************
* PARAMETERS: pointer to in and out file
* FUNCTION: compresses the read in message from
* 			the in file and writes to out file. 
* RETURNS: None.
************************************************* */
void encodeFile(FILE* in, FILE* out)
{
	int c;
	int i;
	long index = 0;
	unsigned long fileSize = 0;
	unsigned short listSize = 0;
	unsigned char* buffer;		/*copy of in file text*/

	TreeNode* head = NULL; 		/*head of list/root*/
	TreeNode* parent = NULL;	/*node created from freq array*/
	ListNode* listHead = NULL;  /*head of list for all codes*/

	fseek(in, 0, SEEK_END);
	fileSize = ftell(in);
	buffer = malloc((fileSize+1)*sizeof(buffer));
	rewind(in);
	
	while((c = fgetc(in)) != EOF)
	{
		buffer[index] = c;
		frequencyArray[c]++;
		index++;
	}

	for (i = 0; i < 256; i++)
	{ 
		if (frequencyArray[i] != 0)
		{
			listSize++;
			parent = createNode(frequencyArray[i], i);
			head = createSortedTree(head, parent);
			listHead = insertNode(listHead, i);
		}
	}
	head = buildTree(head, listSize); /*build tree and update head*/
	if(DEBUG) printTree(head);

	fwrite(&listSize, 1, 1, out);
	printHelper(head, listHead, out);
	if (DEBUG)
	{
		ListNode* temp = listHead;
		while(temp)
		{
			printf("letter: %c length: %d code: ", temp->letter, 
				temp->codeLength);
			for (i = 0; i < temp->codeLength; i++)
			{
				printf("%d", temp->code[i]);
			}
			printf("\n");
			temp = temp->next;
		}
	}
	fwrite(&fileSize, sizeof(fileSize), 1, out);
	printf("Total chars = %ld\n", fileSize);
	writeToFile(buffer, listHead, fileSize, out);
	free(buffer);
	freeTree(head);
	freeList(listHead);
}

/* ************************************************
* PARAMETERS: pointer to in and out file.
* FUNCTION: decodes encoded file
* RETURNS: none.
************************************************* */
void decodeFile(FILE* in, FILE* out)
{
	unsigned long temp = 0;
	unsigned char letter = 0;
	unsigned long frequency = 0;
	unsigned long totalChars = 0;
	unsigned long listSize = 0;
	int i =  0;
	int c = 0;
	TreeNode* head = NULL;
	TreeNode* parent = NULL;
	TreeNode* current = NULL;
	char bit;
  	int mask = 128;

	fread(&temp, sizeof(unsigned char), 1, in);
	listSize = temp;

	while(temp != 0)
	{
		letter = fgetc(in);
		fread(&frequency, sizeof(unsigned long), 1, in);
		frequencyArray[letter] = frequency;
		temp--;
	}
	fread(&totalChars, sizeof(unsigned long), 1, in);

	for (i = 0; i < 256; ++i)
	{
		if (frequencyArray[i] != 0)
		{
			parent = createNode(frequencyArray[i], i);
			head = createSortedTree(head, parent);
		}
	}
	head  = buildTree(head, listSize);
	current = head;

	while ((c = fgetc(in)) != EOF)
	{
		for (i = 0; i < 8; i++)
		{
			bit = ((c << i) & mask) >> 7;
			if (bit == 0)
			{
				current = current->left;
				if (current->left == NULL && current->right == NULL)
				{
					letter = current->letter;
					fputc(letter, out);
					current = head;
				}
			}
			else
			{
				current = current->right;
				if (current->left == NULL && current->right == NULL)
				{
					letter = current->letter;
					fputc(letter, out);
					current = head;
				}
			}
		}
	}
	freeTree(head);
}