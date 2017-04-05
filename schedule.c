/* JK
 * COMP30023
 */

#include <stdio.h>
#include <stdlib.h>

#include "schedule.h" 
#include "process.h"

int schedule(Queue *roundRobin, int quantum, int dqStat)
{
    Process proc = peek(*roundRobin);
    if(!proc) {
        return -1;
    }

    if(dqStat == 0) {// our process hasn't finished
        enqueue(roundRobin, dequeue(roundRobin)); // send it back to the end of the queue
    }
    // schedule the next process to use cpu
    proc = peek(*roundRobin);
    int timeRemaining = proc->timeRemaining;
    //fprintf(stderr, "proc %d timeremaining: %d\n", proc->id, timeRemaining);
    int eventTimer = quantum;
    //fprintf(stderr, "running %d, tr: %d\n", proc->id, timeRemaining);
    return eventTimer;
}
