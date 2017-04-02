/* Jack Kaloger 758278
 * Swap.c
 * Swap functions for COMP30023 Project 1 2017
 */

#include <stdio.h>

#include "swap.h"
#include "list.h"

void swap(void (*method)(Memory *memory, Process p, Queue *disk), Queue *disk, Memory *memory)
{
    Process proc = dequeue(disk); // process sitting on disk for longest
    if(proc != NULL) {
        // find our free spot and add our process
        method(memory, proc, disk);
    }   
}

void firstFit(Memory *memory, Process p, Queue *disk){
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
        freeHole(memory, disk);
        firstFit(memory, p, disk);
    }
}
void bestFit(Memory *memory, Process p, Queue *disk){}
void worstFit(Memory *memory, Process p, Queue *disk){}

