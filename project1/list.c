/* Linked Lists
 */
#include <stdlib.h>

#include "list.h"

void push(List l, void *data)
{
	List new = malloc(sizeof(List));
	
	new->data = data;
	new->next = l;
}

void *pop(List l)
{
	if(!l)
		return NULL;

	List toFree = l;

	void *data = l->data;
	l = l->next;

	free(toFree);

	return data;
}

void deleteAtIndex(List l, int index)
{
}