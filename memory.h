/* Jack Kaloger 758278
 * memory.h
 * COMP30023 Project 1 2017
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "list.h"
#include "queue.h"

typedef struct memory_t *Memory;
typedef struct hole_t *Hole;

struct memory_t {
    int size; // size (in MB) of memory
    List holes;
    Queue processes; // all processes in memory, queued by time entered
    Queue roundRobin; // our round robin queue
};

struct hole_t {
    int startAddress; // memory address of beginning of hole
    int size; // size of hole
};

/* initialises memory with size size */
Memory memInit(int size);
/* adds process p to memory in hole h */
void addProcess(Memory *memory, Hole *h, Process p);
/* removes the front of the RR queue into disk */
void removeProcess(Memory *memory, Queue *disk, int time);
/* creates a hole from memory address start to end */
void createHole(List *holes, int start, int end);
/* merges all adjacent holes in memory */
void mergeHoles(Memory *memory);
/* frees a hole by removing the oldest process in memory */
void freeHole(Memory *memory, Queue *disk, int time);
/* compares 2 hole addresses
 * returns 1 if addr1 > addr2, -1 if addr1 < addr2, 0 otherwise */
int compareHoleAddress(void *addr1, void *addr2);
/* calculates the memory usage */
int memUsage(Memory memory);
/* prints all holes in a list of holes */
void printHoles(List l);

#endif
