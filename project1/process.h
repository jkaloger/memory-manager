/* Jack Kaloger 758278
 * Process.h
 * stores process data
 * Project 1 COMP30023 2017
 */

#ifndef PROCESS_H
#define PROCESS_H

/* Process is a pointer to process_t struct */
typedef struct process_t *Process;

struct process_t {
	int mod; // time last modified
	int id; // id of process. also the priority of the process
	int size; // size of process on disk/memory
	int timeRemaining; // time remaining until process complete
	int memLoc; // last location of process in memory (-1 if never)
};

/* compares the id of 2 processes
 * returns 1 is p1 > p2, -1 if p1 < p2, 0 otherwise
 */
int compareId(void *p1, void *p2);

/* compares the time created of 2 processes
 * returns 1 is p1 > p2, -1 if p1 < p2, 0 otherwise
 */
int compareTimeCreated(void *p1, void *p2);

/* compares the id of 2 processes modified at the same time
 * returns 1 is p1 > p2, -1 if p1 < p2, 0 otherwise
 */
int compareModId(void *p1, void *p2);

#endif
