/* Jack Kaloger 758278
 * Swap functions
 * COMP30023 Project 1 2017
 */

#ifndef SWAP_H
#define SWAP_H

#include "memory.h"
#include "list.h"
#include "queue.h"

void swap(void (*)(Memory *memory, Process p, Queue *disk), Queue *disk, Memory *memory);
void firstFit(Memory *memory, Process p, Queue *disk);
void bestFit(Memory *memory, Process p, Queue *disk);
void worstFit(Memory *memory, Process p, Queue *disk);

#endif
