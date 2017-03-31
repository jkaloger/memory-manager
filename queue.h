/*  queue.h
 *  provides queue data structure
 *  Jack Kaloger
 *  COMP30023 Project 1
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"
#include "process.h"

typedef List Queue;

void enqueue(Queue *q, Process p);
void *dequeue(Queue *q);
void *poll(Queue q);

#endif
