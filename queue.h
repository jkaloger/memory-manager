/*  Jack Kaloger 758278
 *  queue.h
 *  provides queue data structure
 *  COMP30023 Project 1 2017
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"
#include "process.h"

typedef List Queue; // a queue is an implementation of list

/* add data to back of queue */
void enqueue(Queue *q, void *data);
/* remove and return front of queue */
void *dequeue(Queue *q);
/* return front of queue */
void *poll(Queue q);

#endif
