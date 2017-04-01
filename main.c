/* Jack Kaloger 758278
 * Memory Management program
 * Project 1 COMP30023 2017
 * Algorithms are fun
 * C is Fun
 */

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "queue.h"
#include "swap.h"
#include "process.h"
#include "memory.h"

#define DEBUG 1
#define QUANTUM 7
#define TABLECOLS 4
#define INF -1

int parse(char *file, List *l);

/* Drives our memory manager
 */
int main(int argc, char **argv)
{
    /* Structures */
    List processes = NULL; // our initial list of processes from input file
    Queue roundRobin = NULL; // round robin queue, these are pointers to processes, which could be in DISK OR MEMORY!!
    Queue disk = NULL; // processes on our disk
    Memory mainMemory = memInit(atoi(argv[2]));
    
    /* Counting variables */
    // we keep an array of the processes input
    int n = parse(argv[1], &processes);
    int time = 0;
    int eventTimer = 0;
    int q = QUANTUM;
    Process ready = NULL;
    while(1) { // loop until RR queue empty
        
        // add new processes to the disk and queue them for execution in the RR queue
        if(n > 0 && time == ((Process)peek(processes))->timeCreated) {
            Process newProc = pop(&processes); // our process
            enqueue(&disk, newProc); // add it to disk
            enqueue(&roundRobin, newProc); // add to RR queue
            n--; // continue doing this until all processes have been added
        }

        if(eventTimer == 0) { // AN EVENT OCCURED
            swap(firstFit, &disk, &mainMemory); // swap longest waiting process to main memory
            eventTimer = schedule(); // schedule using RR
        }
        time++; // the flow of time continues
    }
    
    // done :)
    return 0;
}

int parse(char *file, List *l)
{
    // Read in file
    FILE *f;
    f = fopen(file, "r");
    if(f == NULL) {
        fprintf(stderr, "Error opening file\n"); // woops
        exit(EXIT_FAILURE);
    }

    // some counting/temp variables
    int i = 0,
        a = 0,
        b = 0,
        c = 0,
        d = 0;

    // loop thrugh every line and store the process in struct
    while(fscanf(f, "%d %d %d %d", &a,&b,&c,&d) == TABLECOLS) {
        Process proc;
        proc = malloc(sizeof(Process));
        proc->timeCreated = a;
        proc->id = b;
        proc->size = c;
        proc->timeRemaining = d;
        insertSorted(&compareTimeCreated, l, proc); //add our new struct into the linked list
        i++;
    }
    
    // return the number of processes
    return i;
}

