/* Jack Kaloger 758278
 * COMP30023 Proj 1 2017
 */

#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "queue.h"
#include "process.h"

/* schedule process using roundrobin queue */
int schedule(Queue *roundRobin, int quantum, int dqStat);

#endif
