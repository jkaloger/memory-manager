/* Jack Kaloger 758278
 * Swap functions
 * COMP30023 Project 1 2017
 */

#ifndef SWAP_H
#define SWAP_H

#include "process.h"
#include "memory.h"
#include "list.h"
#include "queue.h"

// algorithm function pointer
typedef void (*Method)(Memory *, Process, Queue *, int);

/* loads process from disk (if one exists) to memory
 * returns 1 if the top of the round robin queue was removed from memory
 * returns 0 otherwise */
int swap(Method method, Queue *disk, Memory *memory, int time, int *loaded);
/* inserts process into the first available hole */
void firstFit(Memory *memory, Process p, Queue *disk, int time);
/* inserts process into the smallest available hole */
void bestFit(Memory *memory, Process p, Queue *disk, int time);
/* inserts process into the largest available hole */
void worstFit(Memory *memory, Process p, Queue *disk, int time);

#endif
