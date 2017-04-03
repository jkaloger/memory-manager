/* Jack Kaloger 758278
 * Swap.c
 * Swap functions for COMP30023 Project 1 2017
 */

#include <stdio.h>

#include "process.h"
#include "swap.h"
#include "list.h"

int swap(void (*method)(Memory *memory, Process p, Queue *disk, int time), Queue *disk, Memory *memory, int time)
{
    Process proc = dequeue(disk); // process sitting on disk for longest
    if(proc != NULL) {
        // find our free spot and add our process
        method(memory, proc, disk, time);
        return proc->id;
    }
    return -1;
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
void bestFit(Memory *memory, Process p, Queue *disk, int time){}
void worstFit(Memory *memory, Process p, Queue *disk, int time){}

void addToDisk(Queue *disk, Process proc)
{
    insertSorted(&compareModId, proc, disk);
}