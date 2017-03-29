#include "process.h"

int compareId(Process p1, Process p2)
{

    return 0;
}

// returns 1 if p1 > p2
int compareTimeCreated(Process p1, Process p2)
{
    int a = p1->timeCreated;
    int b = p2->timeCreated;
    if(a > b)
        return 1;
    if(a < b)
        return -1;

    return 0;

}
