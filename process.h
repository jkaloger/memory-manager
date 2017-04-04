/* Jack Kaloger 758278
 * Process.h
 * stores process data
 * Project 1 COMP30023 2017
 */

#ifndef PROCESS_H
#define PROCESS_H

typedef struct process_t *Process;

struct process_t {
	int mod;
	int id;
	int size;
	int timeRemaining;
	int memLoc;
};

int compareId(void *p1, void *p2);
int compareTimeCreated(void *p1, void *p2);
int compareModId(void *p1, void *p2);

#endif