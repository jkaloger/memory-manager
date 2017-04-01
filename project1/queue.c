/* Jack Kaloger 758278
 * queue.c
 * Queue functionality
 * COMP30023 Project 1 2017
 */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void *dequeue(Queue *q)
{
    return pop(q);
}

void enqueue(Queue *q, void *data)
{
    // temporary list to iterate through
    Queue temp = *q;
    // create new node in list
    Queue new = malloc(sizeof(struct list_t));
    new->data = data;
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

void *poll(Queue q)
{
    return q->data;
}
