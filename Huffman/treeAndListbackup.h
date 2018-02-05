#ifndef TREE_H
#define TREE_H

struct TreeNode
{
	unsigned long frequency;
	int parent;
	unsigned char letter;
	struct TreeNode *left, *right;
};
typedef struct TreeNode TreeNode;

struct ListNode
{
	struct ListNode* next;
	struct TreeNode* root;
};
typedef struct ListNode ListNode;

/* Alloc a new node with given data. */
struct TreeNode* createNode(unsigned long frequency, unsigned char letter);

/* Insert data at appropriate place in BST, return new tree root. */
struct TreeNode* insertBST(TreeNode* root, unsigned long frequency, 
	unsigned char letter);

/* Create temporary list to sort and start branching*/
struct TreeNode* createSortedList(TreeNode* head, unsigned long frequency, 
	unsigned char letter);

/*recursively build tree based off of weight*/
TreeNode* buildTree(TreeNode* head, long stackSize);

/* Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */
void printTree(TreeNode* root);

/* Print list data on single line, separated with spaces and ending
 * with newline. */
void printList(TreeNode* head);

/* Insert data at head of list, return new list head. */
struct TreeNode* pushStack(TreeNode* head, unsigned long frequency, 
	unsigned char letter);

/* Remove and return data from head of non-empty list, changing head.
 * Memory for removed node should be freed. */
TreeNode* popStack(TreeNode** headRef);

/* Free memory used by the tree. */
void freeTree(TreeNode* root);


#endif