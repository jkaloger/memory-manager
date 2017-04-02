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
#include "schedule.h"
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
    Queue roundRobin = NULL; // round robin queue
    Queue disk = NULL; // processes on our disk
    Memory mainMemory = memInit(1000);
    roundRobin = (mainMemory->processes);

    /* Counting variables */
    // we keep an array of the processes input
    int n = parse("../in/input.txt", &processes);
    int time = 0;
    int eventTimer = 0;
    int q = QUANTUM;
    int processesLoaded = 0;

    /* loop until RR queue empty */
    while(time < 100) { 
        // add new processes to the disk and queue them for execution in the RR queue
        if(n > 0 && time == ((Process)peek(processes))->timeCreated) {
            Process newProc = pop(&processes); // our process
            enqueue(&disk, newProc); // add it to disk
            enqueue(&roundRobin, newProc); // add to RR queue
            n--; // continue doing this until all processes have been added
        }

        if(eventTimer == 0) { // AN EVENT OCCURED
            int loaded = ((Process)peek(disk))->id; // get the id of the process about to be loaded
            swap(firstFit, &disk, &mainMemory); // swap longest waiting process to main memory
            fprintf(stdout, "time %d, %d loaded, numprocesses=%d, numholes=%d, memusage=%d%%\n", 
                   time,
                   loaded,
                   listLen(mainMemory->processes), // number of processes in memory
                   listLen(mainMemory->holes), // number of holes
                   memUsage(mainMemory)); // per centage of memory usage
            eventTimer = schedule(&roundRobin, QUANTUM); // schedule using RR
        }
        ((Process)peek(roundRobin))->timeRemaining--; // front of RR queue is executing
        time++; // the flow of time continues
        eventTimer--;
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
        proc = malloc(sizeof(struct process_t));
        proc->timeCreated = a;
        proc->id = b;
        proc->size = c;
        proc->timeRemaining = d;
        proc->memLoc = INF;
        enqueue(l, proc); //add our new struct into the queue
        i++;
    }
    
    // return the number of processes
    return i;
}

