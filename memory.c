/* Jack Kaloger 758278
 * memory.c
 * Project 1 COMP30023 2017
 */

#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

/* initialises memory with size size */
Memory memInit(int size)
{
    Memory memory = malloc(sizeof(struct memory_t));
    memory->size = size;

    // memory starts off empty, with 1 hole, same size as memory
    Hole h = malloc(sizeof(struct hole_t));
    h->startAddress = 0;
    h->size = size;

    // add our hole to the memory
    List holes = malloc(sizeof(struct list_t));
    holes->data = h;
    holes->next = NULL;
    memory->holes = holes;

    memory->processes = NULL;
    memory->roundRobin = NULL;

    return memory;
}

/* adds process p to memory in hole h, in the upper address space of hole */
void addProcess(Memory *memory, Hole *h, Process p)
{
    // get the hole details
    int staddr = (*h)->startAddress; // start address
    int holeSize = (*h)->size;
    int enaddr = staddr + holeSize; // end address
    // calculate location of process
    p->memLoc = enaddr - p->size;
    // add process to round robin queue and process pool
    enqueue(&((*memory)->roundRobin), p);
    enqueue(&((*memory)->processes), p);
    // remove or reduce hole
    if(holeSize == p->size) {
        // remove the hole
        removeItem(&((*memory)->holes), *h);
    } else if(holeSize > p->size) {
        // modify our current hole size
        (*h)->size -= p->size; // the proc is taking up this much space
    } 
}

/* removes the front of the RR queue into disk */
void removeProcess(Memory *memory, Queue *disk, int time)
{
    // remove from memory
    Process proc = dequeue(&(*memory)->processes);
    removeItem(&(*memory)->roundRobin, proc);

    // set time modified
    proc->mod = time;

    // add to disk
    insertSorted(&compareModId, disk, proc);

    // create a hole at the old location
    createHole(&(*memory)->holes, proc->memLoc, proc->memLoc + proc->size - 1);
}

/* creates a hole from memory address start to end */
void createHole(List *holes, int start, int end)
{
    Hole h = malloc(sizeof(struct hole_t));
    h->startAddress = start;
    h->size = (end-start) + 1;

    // insert by descending memory address
    insertSorted(&compareHoleAddress, holes, h);
}

/* merges all adjacent holes in memory */
void mergeHoles(Memory *memory)
{
    List temp = (*memory)->holes;
    while(temp->next != NULL) { // iterate through all hole
        int currentStart = ((Hole)(temp->data))->startAddress;
        int nextEnd = ((Hole)((temp->next))->data)->startAddress
                      + ((Hole)((temp->next))->data)->size;
        if(currentStart == nextEnd) { // holes are adjacent
            ((Hole)(temp->data))->size += ((Hole)((temp->next)->data))->size;
            ((Hole)(temp->data))->startAddress = 
                                     ((Hole)((temp->next)->data))->startAddress;
            temp->next = (temp->next)->next; // remove the old hole
        } else {
            temp = temp->next; // iterate
        }
    }

}

/* frees a hole by removing the oldest process in memory */
void freeHole(Memory *memory, Queue *disk, int time)
{
    // remove the top of the RR queue
    removeProcess(memory, disk, time);
    // merge all adjacent holes
    mergeHoles(memory);
    
}

/* compares 2 hole addresses
 * returns 1 if addr1 > addr2, -1 if addr1 < addr2, 0 otherwise */
int compareHoleAddress(void *hole1, void *hole2)
{
    int a = ((Hole)hole1)->startAddress; // inserting address
    int b = ((Hole)hole2)->startAddress; // comparing address
    if(a < b) // insert later
        return 1;
    if(a > b) // insert now
        return -1;

    return 0; // insert now
}

/* calculates the memory usage */
int memUsage(Memory memory)
{
    float usage = 0;
    float total = (float)(memory->size);
    List temp = memory->processes;
    while(temp != NULL) {
        usage += ((Process)(temp->data))->size; // count size of all processes
        temp = temp->next;
    }

    int final = 1 + ((usage - 1) / total) * 100; // round up
    return final;
}

/* prints all holes in a list of holes */
void printHoles(List l)
{
    if(l) {
        printf("%d->%d\n",
            ((Hole)(l->data))->startAddress,((Hole)(l->data))->startAddress
            + ((Hole)(l->data))->size - 1);
        printHoles(l->next);
    }
}

