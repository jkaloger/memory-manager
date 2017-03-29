/* Memory Management program
 * Project 1 COMP30023
 * Jack Kaloger 2017
 */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "swap.h"
#include "process.h"

int parse(char *file, Process **p);

int main(int argc, char **argv)
{
    List q = (List)malloc(sizeof(List));
    // we keep an array of the processes input
    Process *p = malloc(sizeof(Process *));
    int n = parse(argv[1], &p);
    for(int i = 0 ; i < n ; i++)
        printf("%d\n", p[i]->id);
    return 0;
}

int parse(char *file, Process **p)
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
        (*p) = realloc((*p), sizeof(Process *) * i+1);
        (*p)[i] = malloc(sizeof(Process));
        (*p)[i]->timeCreated = a;
        (*p)[i]->id = b;
        (*p)[i]->memSize = c;
        (*p)[i]->jobTime = d;
        i++;
    }

    return i;
}
