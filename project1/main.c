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
void printStats(int time, int loaded, int numprocs, int numholes, int memusage);
void addToDisk(Queue *disk, Process proc);

/* Drives our memory manager
 */
int main(int argc, char **argv)
{
    /* Structures */
    List processes = NULL; // our initial list of processes from input file
    Queue *roundRobin = NULL; // round robin queue, a pointer to the memory queue
    Queue disk = NULL; // processes on our disk
    Memory mainMemory = memInit(1000);
    roundRobin = &(mainMemory->roundRobin);

    /* Counting variables */
    // we keep an array of the processes input
    int n = parse("../in/input.txt", &processes);
    int time = 0;
    int eventTimer = 0;
    int q = QUANTUM;
    int processesLoaded = 0;
    int dqStat = 0;

    /* loop until RR queue empty */
    while(time == 0 || listLen(*roundRobin) > 0) { 
        // load new processes to disk as they come in
        if(n > 0) {
            while(((Process)peek(processes))->mod == time) {
                Process newProc = pop(&processes); // our process
                insertSorted(&compareModId, &disk, newProc); // add it to disk
                n--; // continue doing this until all processes have been added
            }
        }

        if(((Process)peek(*roundRobin)) != NULL
        && ((Process)peek(*roundRobin))->timeRemaining == 0) { // AN EVENT OCCURED
            Process proc = dequeue(roundRobin);
            removeItem(&mainMemory->processes, proc); // remove from memory
            eventTimer = 0;
            dqStat = 1;
        }

        if(eventTimer == 0) {
            int memNum = listLen(mainMemory->processes);
            int loaded = swap(firstFit, &disk, &mainMemory, time); // load oldest process on disk into memory (if any)
            printStats(time, loaded, listLen(mainMemory->processes),
                       listLen(mainMemory->holes), memUsage(mainMemory));
            if(memNum > listLen(mainMemory->processes))
                dqStat = 1;
            schedule(roundRobin, QUANTUM, dqStat); // schedule using RR
            eventTimer = QUANTUM;
            dqStat = 0;
        }

        /* TIME STATS */
        ((Process)peek(*roundRobin))->timeRemaining--; // front of RR queue is executing
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
        proc->mod = a;
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

void printStats(int time, int loaded, int numprocs, int numholes, int memusage)
{

    fprintf(stdout, "time %d, %d loaded, numprocesses=%d, numholes=%d, memusage=%d%%\n", 
                   time,
                   loaded,
                   numprocs,
                   numholes,
                   memusage);
}

