/* Jack Kaloger 758278
 * Memory Management program
 * Project 1 COMP30023 2017
 * Algorithms are fun
 * C is Fun
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"
#include "queue.h"
#include "swap.h"
#include "schedule.h"
#include "process.h"
#include "memory.h"

#define DEBUG 1
#define TABLECOLS 4
#define INF -1

extern  int     optind;
extern  char    *optarg;

int parse(char *file, List *l);
void printStats(int time, int loaded, int numprocs, int numholes, int memusage);

/* Drives our memory manager
 */
int main(int argc, char **argv)
{
    char *filename;
    int memSize = 0;
    int quantum = 0;
    void (*alg)(Memory *memory, Process p, Queue *disk, int time) = &firstFit;
    char input;

    while ((input = getopt(argc, argv, "f:a:m:q:")) != -1)
    {
        switch ( input )
        {
            case 'f':
                filename = optarg;
                break;
           
            case 'a':
                // set the value of size (int value) based on optarg
                if(strcmp(optarg, "first") == 0)  {
                    alg = &firstFit;
                } else if(strcmp(optarg, "best") == 0) {
                    alg = &bestFit;
                } else if(strcmp(optarg, "worst") == 0){
                    alg = &worstFit;   
                } else {
                    // exit if optarg unknown
                    fprintf(stderr, "Usage: %s [-f filename] [-a algorithm] [-m memorySize] [-q quantum]\n",
                        argv[0]);
                    exit(EXIT_FAILURE);
                }
                break;

            case 'm':
                // set the value of size (int value) based on optarg
                memSize = atoi(optarg);
                break;

            case 'q':
                // set the value of size (int value) based on optarg
                quantum = atoi(optarg);
                break;

            default:
                // usage message
                fprintf(stderr, "Usage: %s [-f filename] [-a algorithm] [-m memorySize] [-q quantum]\n",
                        argv[0]);
                    exit(EXIT_FAILURE);
                break;
        } 
    }

    if(filename == NULL || memSize == 0 || quantum == 0) {
        fprintf(stderr, "Usage: %s [-f filename] [-a algorithm] [-m memorySize] [-q quantum]\n",
                        argv[0]);
                    exit(EXIT_FAILURE);
    }

    /* Structures */
    List processes = NULL; // our initial list of processes from input file
    Queue *roundRobin = NULL; // round robin queue, a pointer to the memory queue
    Queue disk = NULL; // processes on our disk
    Memory mainMemory = memInit(memSize);
    roundRobin = &(mainMemory->roundRobin);

    /* Counting variables */
    // we keep an array of the processes input
    int n = parse(filename, &processes);
    int time = 0;
    int eventTimer = 0;
    int processesLoaded = 0;
    int dqStat = 0;

    /* loop until RR queue empty */
    while(time == 0 || listLen(*roundRobin) > 0) { 
        // load new processes to disk as they come in
        if(n > 0) {
            while(processes != NULL && ((Process)peek(processes))->mod == time) {
                Process newProc = pop(&processes); // our process
                insertSorted(&compareModId, &disk, newProc); // add it to disk
                n--; // continue doing this until all processes have been added
            }
        }

        // terminated processes should be removed from memory before swapping the next process
        if(((Process)peek(*roundRobin)) != NULL
           && ((Process)peek(*roundRobin))->timeRemaining == 0) { // The process finished executing
            Process proc = dequeue(roundRobin);
            removeItem(&mainMemory->processes, proc); // remove from memory
            createHole(&(mainMemory->holes), proc->memLoc, proc->memLoc + proc->size - 1); // add hole
            mergeHoles(&mainMemory); // merge holes
            eventTimer = 0;
            dqStat = 1;
        }

        if(eventTimer == 0) {
            int loaded = 0;
            if(dqStat == 0)
                dqStat = swap(alg, &disk, &mainMemory, time, &loaded); // load oldest process on disk into memory (if any)
            else
                swap(alg, &disk, &mainMemory, time, &loaded); // load oldest process on disk into memory (if any)
            if(loaded > INF)
                printStats(time, loaded, listLen(mainMemory->processes),
                           listLen(mainMemory->holes), memUsage(mainMemory));
            eventTimer = schedule(roundRobin, quantum, dqStat); // schedule using RR
            dqStat = 0;
        }

        if(eventTimer < 0) {
            fprintf(stdout, "time %d, simulation finished.\n", time);
            return 0;
        }

        /* TIME STATS */
        ((Process)peek(*roundRobin))->timeRemaining--; // front of RR queue is executing
        time++; // the flow of time continues
        eventTimer--; // count down to next event
    }

    fprintf(stdout, "time %d, simulation finished.\n", time);
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

