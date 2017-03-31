/* Swap functions
 * COMP30023 Project 1
 * Jack Kaloger 2017
 */

#ifndef SWAP_H
#define SWAP_H

#include "list.h"
#include "queue.h"

void swap(void (*)(List *disk, Process p), List *disk, List *memory, Queue *processes);
void firstFit(List *mem, Process p);
void bestFit(List *mem, Process p);
void worstFit(List *mem, Process p);

#endif
