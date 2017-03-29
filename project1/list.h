/* Linked Lists
 * Jack Kaloger 2017
 * for Project 1 COMP30023
 */

typedef struct list_t *List;

struct list_t {
	void *data;
	List next;
};

void push(List l, void *data);
void *pop();
void deleteAtIndex(List l, int index);
