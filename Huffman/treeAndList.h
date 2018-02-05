#ifndef TREE_H
#define TREE_H

struct TreeNode
{
	unsigned long frequency;
	unsigned char letter;
	struct TreeNode *left, *right, *next;
};
typedef struct TreeNode TreeNode;

struct ListNode
{
	char* code;
	unsigned char letter;
	int codeLength;
	struct ListNode* next;
};
typedef struct ListNode ListNode;

/* malloc a new node with given data. */
struct TreeNode* createNode(unsigned long frequency, unsigned char letter);

/* Grab right most leaf of parent*/
unsigned char grabRightMostLeaf(TreeNode* head);

/* Create temporary list to sort and start branching*/
TreeNode* createSortedList(TreeNode* head, TreeNode* parent);

/*creates nodes for list*/
ListNode* createListNode(unsigned char letter);

/*recursively build tree based off of weight*/
TreeNode* buildTree(TreeNode* head, long stackSize);

/* Remove and return data from head of non-empty list, changing head.
 * Memory for removed node should be freed. */
TreeNode* popList(TreeNode** headRef);

/* Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */
void printTree(TreeNode* root);

/* Print list data on single line, separated with spaces and ending
 * with newline. */
void printTreeList(TreeNode* head);

/* Free memory used by the tree. */
void freeTree(TreeNode* root);

/* Searches tree of letter to print out the code/path*/
void getCode(TreeNode* root, char arr[], int current, 
	unsigned char letter, ListNode* head);

#endif