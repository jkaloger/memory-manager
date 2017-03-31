/* Memory Management program
 * Project 1 COMP30023
 * Jack Kaloger 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "list.h"
#include "queue.h"
#include "swap.h"
#include "process.h"

#define DEBUG 0

int parse(char *file, List *l);

/* Drives our memory manager
 */
int main(int argc, char **argv)
{
    List processes = NULL; // our initial list of processes from input file
    Queue q = NULL; // round robin queue, these are pointers to processes, which could be in DISK OR MEMORY!!
    List disk = NULL; // processes on our disk, if a process isnt here, its in memory
    List freeMemory = NULL; // list of holes in memory

    // we keep an array of the processes input
    int n = parse(argv[1], &processes);
    int time = 0;
    int event = 0;
    while(n > 0) {
        // add new processes to the round robin queue AND TO DISK FIRST
        if(time >= ((Process)(processes->data))->timeCreated) {
            push(&disk, processes->data);
            enqueue(&q, pop(&processes)); 

            n--; // continue doing this until we're out of processes

            if(DEBUG == 1) {
                printf("time: %d\n", time);
                printList(q);
            }
        }
        if(event == 1) {
            swap(firstFit, &disk, &freeMemory, &processes);
        }
        time++; // the flow of time continues
    }
    if(DEBUG == 1)
        printList(disk);
    return 0;
}

int parse(char *file, List *l)
{
    // Read in file
    FILE *f;
    f = fopen(file, "r");
    if(f == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }

    // some counting/temp variables
    int i = 0,
        a = 0,
        b = 0,
        c = 0,
        d = 0;

    // loop thrugh every line and store the process in struct
    while(fscanf(f, "%d %d %d %d", &a,&b,&c,&d) == 4) {
        Process proc;
        proc = malloc(sizeof(Process));
        proc->timeCreated = a;
        proc->id = b;
        proc->memSize = c;
        proc->jobTime = d;
        insertSorted(&compareTimeCreated, l, proc); //add our new struct into the linked list
        i++;
    }
    
    // return the number of processes
    return i;
}
