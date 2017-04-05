/* Jack Kaloger 758278
 * Swap functions
 * COMP30023 Project 1 2017
 */

#ifndef SWAP_H
#define SWAP_H

#include "memory.h"
#include "list.h"
#include "queue.h"

int swap(void (*method)(Memory *memory, Process p, Queue *disk, int time), Queue *disk, Memory *memory, int time, int *loaded);
void firstFit(Memory *memory, Process p, Queue *disk, int time);
void bestFit(Memory *memory, Process p, Queue *disk, int time);
void worstFit(Memory *memory, Process p, Queue *disk, int time);

#endif
