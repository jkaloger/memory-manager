/* Linked Lists
 */
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

void insertSorted(int (*compareFunction)(void *a, void *b), List *l, void *p)
{
    // temporary list to iterate through
    List temp = *l;

    // create new node in list
    List new = malloc(sizeof(struct list_t));
    new->data = p;
    new->next = NULL;
    if(!*l) {
        *l = new;
    } else {
        while(temp->next != NULL) {
            if(compareFunction(&(temp->data), &p) == 0)
                break;
            temp = temp->next;
        }
        temp->next = new;
    }
}

void push(List *l, void *data)
{
    // create our new node with process p
	List new;
    new = malloc(sizeof(struct list_t));
	new->data = data;
	new->next = *l;
    *l = new;
}

void *pop(List *l)
{
	if(!*l)
		return NULL;

	List toFree = *l;

	void *data = (*l)->data;
    (*l) = (*l)->next;

	free(toFree);

	return data;
}

void removeProcess(List *l, Process p)
{
    List *temp = l;
    while((*temp) == (*temp)->next) {
        if(((*temp)->next)->data == p) {
            // found our item
            (*temp)->next = ((*temp)->next)->next;
        }
    }
    fprintf(stderr, "couldnt find process on disk!\n");
}

void printList(List l)
{
    if(l) {
        printf("%p\n", &((Process)(l->data))->timeCreated);
        printList(l->next);
    }
}

