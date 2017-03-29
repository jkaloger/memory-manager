/* Linked Lists
 */
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

void insertSorted(List *l, Process p)
{
    // temporary list to iterate through
    List temp = *l;

    // create new node in list
    List new = malloc(sizeof(struct list_t));
    new->process = p;
    new->next = NULL;
    if(!*l) {
        *l = new;
    } else {
        while(temp->next != NULL) {
            if(compareTimeCreated(temp->process, p) == 0)
                break;
            temp = temp->next;
        }
        temp->next = new;
    }
}

void push(List *l, Process p)
{
    // create our new node with process p
	List new;
    new = malloc(sizeof(struct list_t));
	new->process = p;
	new->next = *l;
    *l = new;
}

void *pop(List *l)
{
	if(!*l)
		return NULL;

	List toFree = *l;

	Process process = (*l)->process;
    (*l) = (*l)->next;

	free(toFree);

	return process;
}

void printList(List l)
{
    if(l) {
        printf("%d\n", (l->process)->timeCreated);
        printList(l->next);
    }
}

