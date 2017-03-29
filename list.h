/* Linked Lists
 * Jack Kaloger 2017
 * for Project 1 COMP30023
 */

#ifndef LIST_H
#define LIST_H

#include "process.h"

typedef struct list_t *List;

struct list_t {
	Process process;
	List next;
};

void insertSorted(List *l, Process p);
void push(List *l, Process p);
void *pop(List *l);
void printList(List l);

#endif
