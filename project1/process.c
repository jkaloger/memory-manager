/* Jack Kaloger 758278
 * process.c
 * COMP30023 Project 1 2017
 */

#include "process.h"

// returns 1 if p1 > p2
int compareId(void *p1, void *p2)
{
	int a = ((Process)p1)->id;
    int b = ((Process)p2)->id;
    if(a > b)
        return 1;
    if(a < b)
        return -1;

    return 0;
}

// returns 1 if p1 > p2
int compareTimeCreated(void *p1, void *p2)
{
    int a = ((Process)p1)->mod;
    int b = ((Process)p2)->mod;
    if(a > b)
        return 1;
    if(a < b)
        return -1;

    return 0;

}

int compareModId(void *p1, void *p2)
{
	if(compareTimeCreated(p1, p2) == 0)
		return compareId(p1, p2);
	return 1;
}


