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
    int size;
    List holes;
    Queue processes;
    Queue roundRobin;
};

struct hole_t {
    int startAddress;
    int size;
};

Memory memInit(int size);
void addProcess(Memory *mem, Hole *h, Process p);
void removeProcess(Memory *mem, Queue *disk, int time);
void createHole(List *holes, int start, int end);
void mergeHoles(Memory *mem);
void freeHole(Memory *mem, Queue *disk, int time);
int compareHoleAddress(void *addr1, void *addr2);
int memUsage(Memory memory);
void printHoles(List l);

#endif
