/* Jack Kaloger 758278
 * process.c
 * COMP30023 Project 1 2017
 */

#include "process.h"

int compareId(Process p1, Process p2)
{

    return 0;
}

// returns 1 if p1 > p2
int compareTimeCreated(void *p1, void *p2)
{
    int a = ((Process)p1)->timeCreated;
    int b = ((Process)p2)->timeCreated;
    if(a > b)
        return 1;
    if(a < b)
        return -1;

    return 0;

}

int schedule()
{

    return -1;
}

