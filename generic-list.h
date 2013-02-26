/************************************************************************
 * 
 * File name:		generic-list.h
 * Description:		Singly List's API
 * Author:		dennis_fan(dennis_fan@outlook.com), 2013/2/25
 * Version:		1.0
 * Reference:		http://users.cis.fiu.edu/~weiss/dsaa_c2e
 *************************************************************************/

#ifndef _LIST_H
#define _LIST_H

typedef void *ElementAddr;

struct Node;
typedef struct Node *PtrToNode;

struct Node
{
	ElementAddr	elemaddr;
	PtrToNode	next;
};
typedef PtrToNode Position;

typedef int (*PfCbCmp)(ElementAddr, ElementAddr);
typedef void (*PfCbFree)(ElementAddr);

typedef struct ListRecord {
	PtrToNode	head;
	int		elemsize;
	PfCbFree	freefn;
} *List;


/* Create a singly list with dummy head node */
List list_create(int elemsize, PfCbFree freefn);

/* Make the given list empty */
void list_make_empty(List list);

/* Dispose the list */
void list_dispose(List list);

/* Retrun true if List list is emtpy */
int list_is_empty(List list);

/* Return true if pos is last position in List list */
int list_is_last(List list, Position pos);

/* Return the postion of x in List list; NULL if not found */
Position list_find(List list, ElementAddr x, PfCbCmp cmp);

/* Return the prevoius position of x; the next field is NULL when
 * x is not in List list 
 */
Position list_find_previous(List list, ElementAddr x, PfCbCmp cmp);

/* Insert an element with given position pos in the List list */
void list_insert(List list, Position pos, ElementAddr x);

/* Delete the first node in List list when x is found */
int list_delete(List list, ElementAddr x, PfCbCmp cmp, ElementAddr elemaddr);

/* Get List list header position */
Position list_get_header(List list);

/* Supporting iteration mechanism Following */
Position list_get_first(List list);
Position list_next(Position pos);
int list_is_end(Position pos);
ElementAddr list_retrieve(Position pos);


#endif /* THE END */

