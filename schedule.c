/* JK
 * COMP30023
 */

#include <stdio.h>
#include <stdlib.h>

#include "schedule.h" 
#include "process.h"

/* schedule process using round robin queue */
int schedule(Queue *roundRobin, int quantum, int dqStat)
{
    // get our process
    Process proc = peek(*roundRobin);
    if(!proc) {
        return -1; // no processes left
    }

    if(dqStat == 0) { // our process hasn't finished
        enqueue(roundRobin, dequeue(roundRobin)); // back of the line
    }

    // schedule the next process to use cpu
    proc = peek(*roundRobin); 
    int eventTimer = quantum; // count down...

    return eventTimer;
}
