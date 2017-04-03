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

void insertSorted(int (*)(void *a, void *b),List *l, void *d);
void push(List *l, void *data);
void *pop(List *l);
void *peek(List l);
void *getTail(List l);
void removeItem(List *l, void *data);
void printList(List l);
int listLen(List l);

#endif
