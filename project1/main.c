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
#include "process.h"
#include "memory.h"
#include "swap.h"
#include "schedule.h"

#define DEBUG 1
#define TABLECOLS 4
#define INF -1

extern  int     optind;
extern  char    *optarg;

/* loads processes from specified file and adds them to the list */
int parse(char *file, List *l);
/* prints the status of memory at time t */
void printStats(int time, int loaded, int numprocs, int numholes, int memusage);
/* prints the usage options, then exits the program */
void printUsage(char *prog);

/* Drives our memory manager */
int main(int argc, char **argv)
{
    /* user input variables */
    char *filename;
    int memSize = 0;
    int quantum = 0;
    Method alg = &firstFit; // first fit as default
    char input;

    /* get user specified options */
    while ((input = getopt(argc, argv, "f:a:m:q:")) != -1)
    {
        switch ( input )
        {
            case 'f': // file name specified
                filename = optarg;
                break;
           
            case 'a': // algorithm specified
                // set the value of size (int value) based on optarg
                if(strcmp(optarg, "first") == 0)  {
                    alg = &firstFit;
                } else if(strcmp(optarg, "best") == 0) {
                    alg = &bestFit;
                } else if(strcmp(optarg, "worst") == 0){
                    alg = &worstFit;   
                } else {
                    // exit if optarg unknown
                    printUsage(argv[0]);
                }
                break;

            case 'm': // memory size specified
                // set the value of size (int value) based on optarg
                memSize = atoi(optarg);
                break;

            case 'q': // quantum specified
                // set the value of size (int value) based on optarg
                quantum = atoi(optarg);
                break;

            default: // nothing specified. error
                // usage message
                printUsage(argv[0]);
                break;
        } 
    }

    // check values are valid, otherwise print usage message
    if(filename == NULL || memSize == 0 || quantum == 0) {
        printUsage(argv[0]);
    }

    /* Structures */
    List processes = NULL; // our initial list of processes from input file
    Queue disk = NULL; // processes on our disk
    Memory mainMemory = memInit(memSize); // main memory unit
    Queue *roundRobin = &(mainMemory->roundRobin);; // round robin queue
    

    /* Counting variables */
    // load the processes from specified input, store the number of processes
    int n = parse(filename, &processes);
    int time = 0;
    int eventTimer = 0;
    int dqStat = 0; // if 1, scheduler will not dequeue Round Robin queue

    // loop until RR queue empty
    while(processes != NULL || listLen(*roundRobin) > 0) { 
        if(n > 0) {
            // load new processes to disk as they come in
            while(processes != NULL && ((Process)peek(processes))->mod == time){
                Process newProc = pop(&processes); // our process
                insertSorted(&compareModId, &disk, newProc); // add it to disk
                n--; // continue doing this until all processes have been added
            }
        }

        // remove terminated processes from memory before swapping next process
        if(((Process)peek(*roundRobin)) != NULL
        && ((Process)peek(*roundRobin))->timeRemaining == 0) {
            // process executing must be at the head of the RR queue
            Process proc = dequeue(roundRobin);
            removeItem(&mainMemory->processes, proc); // remove it from memory
            
            // add a hole to memory
            createHole(&(mainMemory->holes), proc->memLoc,
                       proc->memLoc + proc->size - 1); 
            mergeHoles(&mainMemory); // merge

            eventTimer = 0; // something happned!
            dqStat = 1; // tell scheduler not to dequeue RR again
        }

        // when an event occurs
        if(eventTimer == 0) {
            int loaded = -1; // id of the loaded process (-1 if none)
            if(dqStat == 0) // check for other dequeue stats
                // load oldest process on disk into memory (if any)
                dqStat = swap(alg, &disk, &mainMemory, time, &loaded); 
            else // scheduler already told not to dequeue
                // load oldest process on disk into memory (if any)
                swap(alg, &disk, &mainMemory, time, &loaded); 
            if(loaded > INF) // when we load something, print its status
                printStats(time, loaded, listLen(mainMemory->processes),
                           listLen(mainMemory->holes), memUsage(mainMemory));

            eventTimer = schedule(roundRobin, quantum, dqStat); // schedule RR
            
            dqStat = 0; // reset dequeue status
        }

        // event timer is set to -1 when the last process in RR terminates
        if(eventTimer < 0) {
            if(processes == NULL) { // all processes completed
                fprintf(stdout, "time %d, simulation finished.\n", time);
                return 0;
            } else {
                // still have more processes
                time++;
                eventTimer = 0;
                continue;
            }
        }

        /* TIME STATS */
        ((Process)peek(*roundRobin))->timeRemaining--; // RR head is executing
        time++; // the flow of time continues
        eventTimer--; // count down to next event
    }
    // done :)
    return 0;
}

/* loads processes from specified file and adds them to the list */
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

/* prints the status of memory at time t */
void printStats(int time, int loaded, int numprocs, int numholes, int memusage)
{
    printf("time %d, %d loaded, numprocesses=%d, numholes=%d, memusage=%d%%\n", 
            time,
            loaded,
            numprocs,
            numholes,
            memusage);
}

/* prints the usage options, then exits the program */
void printUsage(char *prog) {
    // print usage instructions
    fprintf(stderr,
        "Usage: %s [-f filename] [-a algorithm] [-m memorySize] [-q quantum]\n",
        prog);

    // and exit
    exit(EXIT_FAILURE);
}
