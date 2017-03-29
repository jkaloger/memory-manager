/* Memory Management program
 * Project 1 COMP30023
 * Jack Kaloger 2017
 */

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "queue.h"
#include "swap.h"
#include "process.h"

int parse(char *file, List *l);

int main(int argc, char **argv)
{
    Queue q = NULL;
    List processes = NULL;

    // we keep an array of the processes input
    int n = parse(argv[1], &processes);
    int time = 0;
    while(n > 0) {
        if(time >= (processes->process)->timeCreated) {
            enqueue(&q, pop(&processes)); 
            n--;
        }
        time++;
    }
    printList(q);
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
        insertSorted(l, proc);
        i++;
    }

    return i;
}
