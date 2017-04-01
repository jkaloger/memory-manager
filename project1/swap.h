/* Jack Kaloger 758278
 * Swap functions
 * COMP30023 Project 1 2017
 */

#ifndef SWAP_H
#define SWAP_H

#include "memory.h"
#include "list.h"
#include "queue.h"

void swap(void (*)(Memory *mem, Process p), List *disk, Memory *memory);
void firstFit(Memory *mem, Process p);
void bestFit(Memory *mem, Process p);
void worstFit(Memory *mem, Process p);

#endif
