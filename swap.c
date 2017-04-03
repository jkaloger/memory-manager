/* Jack Kaloger 758278
 * Swap.c
 * Swap functions for COMP30023 Project 1 2017
 */

#include <stdio.h>

#include "process.h"
#include "swap.h"
#include "list.h"

int swap(void (*method)(Memory *memory, Process p, Queue *disk, int time), Queue *disk, Memory *memory, int time, int *loaded)
{
    Process proc = dequeue(disk); // process sitting on disk for longest
    if(proc != NULL) {
        Process prev = peek((*memory)->roundRobin);
        // find our free spot and add our process
        method(memory, proc, disk, time);
        *loaded = proc->id;
        if(prev != peek((*memory)->roundRobin))
            return 1;
    } else {
        *loaded = -1;    
    }
    return 0;
}

void firstFit(Memory *memory, Process p, Queue *disk, int time){
    List temp = (*memory)->holes;
    int success = 0;
    while(success == 0 && temp != NULL ) {
        int size = ( (Hole)(temp->data))->size;
        if(size >= p->size) {
            success = 1;
            addProcess(memory, (Hole *)&(temp->data), p);
            break;
        }
        temp = temp->next;
    }
    if(success == 0) {
        freeHole(memory, disk, time);
        firstFit(memory, p, disk, time);
    }
}
void bestFit(Memory *memory, Process p, Queue *disk, int time){
    List temp = (*memory)->holes;
    Hole h = NULL;
    while(temp != NULL) {
        int size = ( (Hole)(temp->data))->size;
        if(size >= p->size) {
            if(h == NULL) {
                h = temp->data;
            } else if(h->size < size) {
                h = temp->data;
            }
        }
        temp = temp->next;
    }

    if(h != NULL) {
        addProcess(memory, &h, p);
    } else {
        freeHole(memory, disk, time);
        bestFit(memory, p, disk, time);
    }

}
void worstFit(Memory *memory, Process p, Queue *disk, int time){
    List temp = (*memory)->holes;
    Hole h = NULL;
    while(temp != NULL) {
        int size = ( (Hole)(temp->data))->size;
        if(size >= p->size) {
            if(h == NULL) {
                h = temp->data;
            } else if(h->size > size) {
                h = temp->data;
            }
        }
        temp = temp->next;
    }

    if(h != NULL) {
        addProcess(memory, &h, p);
    } else {
        freeHole(memory, disk, time);
        worstFit(memory, p, disk, time);
    }
}

void addToDisk(Queue *disk, Process proc)
{
    insertSorted(&compareModId, proc, disk);
}