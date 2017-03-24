/* Memory Management program
 * Project 1 COMP30023
 * Jack Kaloger 2017
 */

#include <stdio.h>
#include <stdlib.h>

#include "swap.h"

void parse(char *file, int ***A);

int main(int argc, char **argv)
{
    int **table;
    table = malloc(sizeof(int *) * 4);
    parse(argv[1], &table);
    
    return 0;
}

void parse(char *file, int ***A)
{
    // Read file
    FILE *f;
    f = fopen(file, "r");
    if(f == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }

    // initialise
    for(int j = 0 ; j < 4 ; j++)
        (*A)[j] = malloc(sizeof(int));
    int i = 0;
    while(fscanf(f, "%d %d %d %d", &(*A)[0][i], &(*A)[1][i], &(*A)[2][i], &(*A)[3][i]) == 4) {
        i++;
        for(int j = 0 ; j < 4 ; j++) {
            (*A)[j] = realloc((*A)[j], sizeof(int) * i+1);
        }
    }
}
