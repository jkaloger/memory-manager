/* Jack Kaloger 758278
 * Linked Lists
 * Project 1 COMP30023 2017
 */

#ifndef LIST_H
#define LIST_H

#include "process.h"

typedef struct list_t *List;

struct list_t {
	void *data;
	List next;
};

/* Insert data into list in a sorted way using specified method */
void insertSorted(int (*method)(void *, void *),List *l, void *d);
/* adds data to head of the list */
void push(List *l, void *data);
/* removes and returns the head of the list */
void *pop(List *l);
/* returns the head of the list */
void *peek(List l);
/* returns the tail of the list */
void *getTail(List l);
/* removes the specified item from the list */
void removeItem(List *l, void *data);
/* frees the list */
void freeList(List l);
/* prints the list of data pointers */
void printList(List l);
/* returns the length of the list */
int listLen(List l);

#endif
