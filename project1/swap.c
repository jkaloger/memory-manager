/* Jack Kaloger 758278
 * Swap.c
 * Swap functions for COMP30023 Project 1 2017
 */

#include <stdio.h>

#include "swap.h"

int swap(Method method, Queue *disk, Memory *memory, int time, int *loaded)
{
    Process proc = dequeue(disk); // process sitting on disk for longest
    if(proc != NULL) {
        Process prev = peek((*memory)->roundRobin); // get the head of RR
        // find our free spot and add our process
        method(memory, proc, disk, time); // apply our algorithm
        *loaded = proc->id; // set the id of loaded process
        if(prev != peek((*memory)->roundRobin))
            return 1; // tell scheduler not to dequeue
    } else {
        *loaded = -1; // no process was loaded...
    }
    return 0; // scheduler still needs to dequeue RR
}

void firstFit(Memory *memory, Process p, Queue *disk, int time)
{
    List temp = (*memory)->holes;
    int success = 0;
    // keep going until we've searched all the holes, or found a good hole
    while(success == 0 && temp != NULL ) { 
        int size = ( (Hole)(temp->data))->size;
        if(size >= p->size) {
            success = 1; // hole is viable
            addProcess(memory, (Hole *)&(temp->data), p); // add process to hole
            return; // we're done here
        }
        temp = temp->next;
    }

    // no viable holes were found
    if(success == 0) {
        freeHole(memory, disk, time); // create a new hole
        firstFit(memory, p, disk, time); // and try again
    }
}
void bestFit(Memory *memory, Process p, Queue *disk, int time)
{
    List temp = (*memory)->holes;
    Hole h = NULL;
    // keep going until we're out of holes
    while(temp != NULL) {
        int size = ( (Hole)(temp->data))->size;
        if(size >= p->size) {
            // hole can fit our process...
            if(h == NULL) {
                // something is better than nothing. use it
                h = temp->data;
            } else if(h->size > size) {
                // this hole is smaller!
                h = temp->data;
            }
        }
        temp = temp->next;
    }

    
    if(h != NULL) { // we found a hole
        addProcess(memory, &h, p); // add the process to it
    } else {
        // no viable holes exist
        freeHole(memory, disk, time); // create a new hole
        bestFit(memory, p, disk, time); // and try again
    }

}
void worstFit(Memory *memory, Process p, Queue *disk, int time){
    List temp = (*memory)->holes;
    Hole h = NULL;
    // keep going until we're out of holes
    while(temp != NULL) {
        int size = ( (Hole)(temp->data))->size;
        if(size >= p->size) {
            // hole can fit our process...
            if(h == NULL) {
                // something is better than nothing. use it
                h = temp->data;
            } else if(h->size < size) {
                // this hole is larger!
                h = temp->data;
            }
        }
        temp = temp->next;
    }

    if(h != NULL) { // we found a hole
        addProcess(memory, &h, p); // add the process to it
    } else {
        // no viable holes exist
        freeHole(memory, disk, time); // create a new hole
        worstFit(memory, p, disk, time); // and try again
    }
}

