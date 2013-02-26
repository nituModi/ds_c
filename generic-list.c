/************************************************************************
 * 
 * File name:		generic-list.c
 * Description:		Singly List's Implementation(Dummy Node, Null Tail)
 * Author:		dennis_fan(dennis_fan@outlook.com), 2013/2/25
 * Version:		1.0
 *************************************************************************/

#include "generic-list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Create a singly list with dummy head node */
List 
list_create(int elemsize, PfCbFree freefn)
{
	List list;

	if ( (list = malloc(sizeof(struct ListRecord))) == NULL ) {
		fprintf(stderr, "Out of memory!\n");
		exit(1);
	}
	
	if ( (list->head = malloc(sizeof(struct Node))) == NULL ) {
		fprintf(stderr, "Out of memory!\n");
		exit(1);
	}

	list->head->next = NULL;
	list->freefn = freefn;
	list->elemsize = elemsize;
}

/* Make the given list empty */
void 
list_make_empty(List list)
{
	PtrToNode first;
	if ( list == NULL ) {
		fprintf(stderr, "Must use list_create first\n");
	} else {
		while ( !list_is_empty(list) ) {
			first = list->head->next;
			list->head->next = first->next;
			if ( list->freefn )
				list->freefn(first->elemaddr);
			free(first->elemaddr);
			free(first);
		}
	}
}

/* Dispose the list */
void 
list_dispose(List list)
{
	list_make_empty(list);
	free(list->head);
	free(list);
}

/* Return true if List list is empty */
int 
list_is_empty(List list)
{
	return list->head->next == NULL;
}

/* Return true if pos is last position in List list */
int 
list_is_last(List list, Position pos)
{
	return pos->next == NULL;
}

/* Return the postion of x in List list; NULL if not found */
Position 
list_find(List list, ElementAddr x, PfCbCmp cmp)
{
	Position pos;

	for ( pos = list->head->next; 
	      pos != NULL && !cmp(pos->elemaddr, x); 
              pos = pos->next
	);

	return pos;
}

/* Return the prevoius position of x; the next field is NULL when
 * x is not in List list 
 */
Position 
list_find_previous(List list, ElementAddr x, PfCbCmp cmp)
{
	Position pos;
	
	for ( pos = list->head; 
	      pos->next != NULL && !cmp(pos->next->elemaddr, x);
	      pos = pos->next
	);

	return pos;
}

/* Insert an element with given position pos in the List list */
void 
list_insert(List list, Position pos, ElementAddr x)
{
	PtrToNode node;
	ElementAddr elemaddr;	

	if ( (elemaddr = malloc(list->elemsize)) == NULL ) {
		fprintf(stderr, "Out of memory");
		exit(1);
	} 
	memcpy(elemaddr, x, list->elemsize);

	if ( (node = malloc(sizeof(struct Node))) == NULL ) {
		fprintf(stderr, "Out of memory!\n");
		exit(1);
	}
	
	node->elemaddr = elemaddr;
	node->next = pos->next;
	pos->next = node;
}

/* Delete the first node in List list when x is found;
 * Do nothing if not found 
 */
int 
list_delete(List list, ElementAddr x, PfCbCmp cmp, ElementAddr elemaddr)
{
	Position pos, tmp;
	int is_found = 0;
		
	pos = list_find_previous(list, x, cmp);
	
	if ( !list_is_last(list, pos) ) {
		tmp = pos->next;
		pos->next = tmp->next;
		memcpy(elemaddr, tmp->elemaddr, sizeof(list->elemsize));
		free(tmp->elemaddr);
		free(tmp);
		is_found = 1;
	}
	return is_found;
}

/* Get List list header position */
Position 
list_get_header(List list)
{
	return list->head;
}


/* Supporting iteration mechanism Following */

Position 
list_get_first(List list)
{
	return list->head->next;
}

Position 
list_next(Position pos)
{
	return pos->next;
}

int 
list_is_end(Position pos)
{
	return pos == NULL;
}

ElementAddr 
list_retrieve(Position pos)
{
	return pos->elemaddr;
}

