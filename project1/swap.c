/* Swap.c
 * Swap functions for COMP30023 Project 1
 * Jack Kaloger 2017
 */

#include "swap.h"
#include "list.h"

void swap(void (*method)(List *memory, Process p), List *disk, List *memory, Queue *processes){

    // we want the top of our queue
    Process proc = pop(processes); 
    removeProcess(disk, proc); // remove it from the hdd

    // find our free spot and add our process
    method(memory, proc);
}

void firstFit(List *memory, Process p){
    
}
void bestFit(){}
void worstFit(){}
