/* ************************************
* Kevin Cox
*
* implementation of linked list
************************************ */

#include <stdio.h>
#include "linkedlist.h"
#include <stdlib.h>

struct ListNode* swap(struct ListNode** current, struct ListNode** next);

/* Alloc a new node with given data. */
struct ListNode* createNode(int data)
{
	struct ListNode* node = malloc(sizeof(struct ListNode));
	node -> data = data;
	node -> next = NULL;
	return node;
}

/* Insert data at appropriate place in a sorted list, return new list head. */
struct ListNode* insertSorted(struct ListNode* head, int data)
{
	struct ListNode* new;
	if (head == NULL || data < head->data)
	{
		new = createNode(data);
		new->next = head;			/*update head of list*/
		return new;
	}
	else
	{
		head->next = insertSorted(head->next, data);
		return head;
	}
}

/* Remove data from list pointed to by headRef, changing head if necessary.
 * Make no assumptions as to whether the list is sorted.
 * Memory for removed node should be freed.
 * Return 1 if data was present, 0 if not found. */
int removeItem(struct ListNode** headRef, int data)
{
	struct ListNode* node;
	if (*headRef == NULL)
	{
		return 0;
	}
	else if((*headRef)->data == data)
	{
		node = *headRef;
		*headRef = (*headRef)->next;
		free(node);
		return 1;
	}
	else
	{
		return removeItem(&((*headRef)->next), data);
	}
}

/* Insert data at head of list, return new list head. */
struct ListNode* pushStack(struct ListNode* head, int data)
{
	struct ListNode* newHead = createNode(data);
	newHead->next = head;
	return newHead;
}

/* Remove and return data from head of non-empty list, changing head.
 * Memory for removed node should be freed. */
int popStack(struct ListNode** headRef)
{
	struct ListNode* updatedNode = *headRef;
	int data = updatedNode->data;
	*headRef = updatedNode->next;
	free(updatedNode);
	return data;
}

/* Return length of the list. */
int listLength(struct ListNode* head)
{
	struct ListNode* current = head;
	int length = 0;

	while(current != NULL)
	{
		length++;
		current = current->next;
	}
	return length;
}

/* Print list data on single line, separated with spaces and ending
 * with newline. */
void printList(struct ListNode* head)
{
	struct ListNode* current = head;

	while(current != NULL)
	{
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
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

/* Reverse order of elements in the list */
void reverseList(struct ListNode** headRef)
{
	struct ListNode* current;
	struct ListNode* nextNode;
	if (*headRef != NULL)
	{
		current = *headRef;
		nextNode = current->next;
		if (nextNode != NULL)
		{
			reverseList(&nextNode);
			current->next->next = current;
			current->next = NULL;
			*headRef = nextNode;
		}
	}
}