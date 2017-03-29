/* Process.h
 * stores process data
 * Jack Kaloger Project 1 COMP30023 2017
 */

typedef struct process_t *Process;

struct process_t {
	int timeCreated;
	int id;
	int memSize;
	int jobTime;
};