/* Jack Kaloger 758278
 * memory.c
 * Project 1 COMP30023 2017
 */

#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

Memory memInit(int size)
{
    // init memory
    Memory memory = malloc(sizeof(struct memory_t));
    memory->size = size;

    // memory starts off empty
    Hole h = malloc(sizeof(struct hole_t));
    h->startAddress = 0;
    h->size = size; // 0-indexed

    List holes = malloc(sizeof(struct list_t));
    holes->data = h;
    holes->next = NULL;
    memory->holes = holes;
    memory->processes = NULL;
    memory->roundRobin = NULL;
    return memory;
}

void addProcess(Memory *m, Hole *h, Process p)
{
    int staddr = (*h)->startAddress;
    int holeSize = (*h)->size;
    int enaddr = staddr + holeSize;
    p->memLoc = enaddr - p->size;
    // add process to round robin queue and process pool
    enqueue(&((*m)->roundRobin), p);
    enqueue(&((*m)->processes), p);
    // remove or reduce hole
    if(holeSize == p->size) {
        // remove the hole

        removeItem(&((*m)->holes), *h);
    } else if(holeSize > p->size) {
        // modify our current hole size
        (*h)->size -= p->size; // the proc is taking up this much space
    } 
}

void removeProcess(Memory *m, Queue *disk, int time)
{
    // move from mem->disk
    Process proc = dequeue(&(*m)->processes);
    removeItem(&(*m)->roundRobin, proc);
    proc->mod = time;
    insertSorted(&compareModId, disk, proc);
    createHole(&(*m)->holes, proc->memLoc, proc->memLoc + proc->size - 1);
}

void createHole(List *holes, int start, int end)
{
    Hole h = malloc(sizeof(struct hole_t));
    h->startAddress = start;
    h->size = (end-start) + 1;
    insertSorted(&compareHoleAddress, holes, h);
}

void freeHole(Memory *mem, Queue *disk, int time)
{
    removeProcess(mem, disk, time);
    mergeHoles(mem);
    
}

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

void mergeHoles(Memory *mem)
{
    List temp = (*mem)->holes;
    while(temp->next != NULL) {
        int currentStart = ((Hole)(temp->data))->startAddress;
        int nextEnd = ((Hole)((temp->next))->data)->startAddress + ((Hole)((temp->next))->data)->size;
        if(currentStart == nextEnd) { // merge the holes
            ((Hole)(temp->data))->size += ((Hole)((temp->next)->data))->size;
            ((Hole)(temp->data))->startAddress = ((Hole)((temp->next)->data))->startAddress;
            temp->next = (temp->next)->next;
        } else {
            temp = temp->next;
        }
    }

}

int memUsage(Memory memory)
{
    float usage = 0;
    float total = (float)(memory->size);
    List temp = memory->processes;
    while(temp != NULL) {
        usage += ((Process)(temp->data))->size;
        temp = temp->next;
    }

    int final = 1 + ((usage - 1) / total) * 100;
    return final;
}

void printHoles(List l)
{
    if(l) {
        printf("%d->%d\n", ((Hole)(l->data))->startAddress,((Hole)(l->data))->startAddress + ((Hole)(l->data))->size - 1);
        printHoles(l->next);
    }
}

