/* Jack Kaloger 758278
 * Process.h
 * stores process data
 * Project 1 COMP30023 2017
 */

#ifndef PROCESS_H
#define PROCESS_H

typedef struct process_t *Process;

struct process_t {
	int timeCreated;
	int id;
	int size;
	int timeRemaining;
};

int compareId(Process p1, Process p2);
int compareTimeCreated(void *p1, void *p2);
int schedule();

#endif
