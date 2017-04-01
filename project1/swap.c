/* Jack Kaloger 758278
 * Swap.c
 * Swap functions for COMP30023 Project 1 2017
 */

#include <stdio.h>

#include "swap.h"
#include "list.h"

void swap(void (*method)(Memory *memory, Process p), List *disk, Memory *memory){

    Process proc = pop(disk); // process sitting on disk for longest
    if(proc != NULL) {
        // find our free spot and add our process
        method(memory, proc);
    }
}

void firstFit(Memory *memory, Process p){
    List *temp = &((*memory)->holes);
    int success = 0;
    while( *temp != NULL ) {
        int size = ( (Hole)((*temp)->data))->size;
        if(size > p->size) {
            success = 1;
            addProcess(memory, ((Hole)((*temp)->data))->startAddress, p);
        }

    }

    if(success == 0) {
        int addr = freeHole(memory, p->size);
        addProcess(memory, addr, p);
    }
}
void bestFit(){}
void worstFit(){}

