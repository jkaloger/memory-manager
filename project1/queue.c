/* queue.c
 * Queue functionality
 * Jack Kaloger 2017
 * COMP30023 Project 1
 */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void *dequeue(List q)
{
    return pop(q);
}

void enqueue(List q, int data)
{
    List new = (List)malloc(sizeof(List));
    new->data = data;
    new->next = q;
    q = new;
}
