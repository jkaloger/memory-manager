/*  Jack Kaloger 758278
 *  queue.h
 *  provides queue data structure
 *  COMP30023 Project 1 2017
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"
#include "process.h"

typedef List Queue;

void enqueue(Queue *q, void *data);
void *dequeue(Queue *q);
void *poll(Queue q);

#endif
