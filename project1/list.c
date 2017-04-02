/* Jack Kaloger 758278
 * Linked Lists
 * COMP30023 Project 1 2017
 */
#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "memory.h"

void insertSorted(int (*compareFunction)(void *a, void *b), List *l, void *data)
{
    // temporary list to iterate through
    List temp = *l;
    // create new node in list
    List new = malloc(sizeof(struct list_t)); // allocate struct size NOT POINTER SIZE
    new->data = data;
    new->next = NULL;
    if(!*l) {
        *l = new;
    } else if(temp->next == NULL) {
        new->next = temp;
        *l = new;
    } else {
        while(temp->next != NULL) {
            if(compareFunction(data, (temp->next)->data) <= 0) {
                break;
            }
            temp = temp->next;
        }
        new->next = temp->next;
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

void *peek(List l)
{
    return l->data;
}

void removeItem(List *l, void *data)
{
    List *temp = l;
    while((*temp) == (*temp)->next) {
        if(((*temp)->next)->data == data) {
            // found our item
            (*temp)->next = ((*temp)->next)->next;
        }
    }
    fprintf(stderr, "couldnt find process on disk!\n");
}

void printList(List l)
{
    if(l) {
        //Process p = l->data;
        printf("%d->%d\n", ((Hole)(l->data))->startAddress,((Hole)(l->data))->startAddress + ((Hole)(l->data))->size - 1);
        //fprintf(stderr, "%d\n", p->timeCreated);
        printList(l->next);
    }
}


