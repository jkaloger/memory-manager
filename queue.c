/* queue.c
 * Queue functionality
 * Jack Kaloger 2017
 * COMP30023 Project 1
 */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void *dequeue(List *q)
{
    return pop(q);
}

void enqueue(List *q, Process p)
{
    // temporary list to iterate through
    List temp = *q;

    // create new node in list
    List new = malloc(sizeof(struct list_t));
    new->process = p;
    new->next = NULL;
    if(!*q) {
        *q = new;
    } else {
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new;
    }
}
