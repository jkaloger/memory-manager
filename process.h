/* Process.h
 * stores process data
 * Jack Kaloger Project 1 COMP30023 2017
 */

#ifndef PROCESS_H
#define PROCESS_H

typedef struct process_t *Process;

struct process_t {
	int timeCreated;
	int id;
	int memSize;
	int jobTime;
};

int compareId(Process p1, Process p2);
int compareTimeCreated(void *p1, void *p2);

#endif
