/* Jack Kaloger 758278
 * Linked Lists
 * COMP30023 Project 1 2017
 */
#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "memory.h"

/* Insert data into list in a sorted way using specified method */
void insertSorted(int (*compareFunction)(void *, void *), List *l, void *data)
{
    // temporary list to iterate through
    List temp = *l;
    // create a new node to be inserted
    List new = malloc(sizeof(struct list_t)); // allocate struct size
    new->data = data;
    new->next = NULL;

    if(!*l) { // list is empty; new becomes list
        *l = new; 
    } else if(compareFunction(data, (*l)->data) <= 0) { // insert at head
        new->next = *l;
        *l = new;
    } else {
        while(temp->next != NULL) {
            if(compareFunction(data, (temp->next)->data) <= 0) {
                break; // stop searching when we've found something <= our data
            }
            temp = temp->next; // iterate through list
        }

        // insert into list
        new->next = temp->next; 
        temp->next = new;
    }
}

/* adds data to head of the list */
void push(List *l, void *data)
{
    // create our new node with data
	List new;
    new = malloc(sizeof(struct list_t));
	new->data = data;

    // new is the head of the list, so the old list is next
	new->next = *l;
    *l = new;
}

/* removes and returns the head of the list */
void *pop(List *l)
{
    // list is empty
	if(!*l)
		return NULL;

    // we'll want to free our first node once we remove it
	List toFree = *l;
    // get the node data
	void *data = (*l)->data;
    // set the head of the list to the next node
    (*l) = (*l)->next;
    // free the node
	free(toFree);

	return data;
}

/* returns the head of the list */
void *peek(List l)
{
    if(!l)
        return NULL;
    return l->data;
}

/* returns the tail of the list */
void *getTail(List l)
{
    // list is empty
    if(!l)
        return NULL;
    // list has 1 item
    if(!l->next)
        return l->data;

    // temporary list for iteration
    List temp = l;
    // loop to the end of the list
    while(temp->next != NULL) {
        temp = temp->next;
    }

    return temp->data;
}

/* removes the specified item from the list */
void removeItem(List *l, void *data)
{
    // the item was at the head of the list
    if((*l)->data == data) {
        *l = (*l)->next;
        return;
    }

    // iterator
    List temp = *l;
    while(temp->next != NULL) { // loop until end of list
        if((temp->next)->data == data) {
            // found our item
            temp->next = (temp->next)->next;
            return;
        }
        temp = temp->next;
    }

    // if we get to here, the item cannot be in the list
    fprintf(stderr, "couldnt find process in list!\n");
}

/* prints the list of data pointers */
void printList(List l)
{
    if(l) {
        fprintf(stderr, "%p\n", l->data);
        printList(l->next); // go to next item
    }
}

/* returns the length of the list */
int listLen(List l)
{
    List temp = l; // iterator
    int len = 0;
    if(temp != NULL)
        len++; // count the head of the list
    else
        return len; // list is empty

    while(temp->next != NULL) {
        len++;
        temp = temp->next; // go to next item
    }
    return len;
}


