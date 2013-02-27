/************************************************************************
 * 
 * File name:		generic-queue.c
 * Description:		Generic Queue's Implementation
 * Author:		dennis_fan(dennis_fan@outlook.com), 2013/2/26
 * Version:		1.0
 *************************************************************************/

#include "generic-queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_QUEUE_SIZE (4)

/* Create a new queue with capacity */
Queue 
queue_create(int elemsize, int capacity, PfCbFree freefn)
{
	Queue que;

	que = malloc(sizeof(struct QueueRecord));
	if ( que == NULL ) {
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}
	
	que->elemsize = elemsize;
	que->capacity = capacity > MIN_QUEUE_SIZE ? capacity : MIN_QUEUE_SIZE;

	que->array = malloc(elemsize * que->capacity);
	if ( que->array == NULL ) {
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}
	que->front = 1;
	que->rear = 0;
	que->size = 0;
	que->freefn = freefn;

	return que;
}

/* Dispose the queue */
void 
queue_dispose(Queue que)
{
	if (que != NULL) {
		queue_make_empty(que);
		free(que->array);
		free(que);
	}
}

/* Make the give queue empty */
void 
queue_make_empty(Queue que)
{
	if ( que->freefn ) {
		int i;
		for ( i = 0; i < que->size; ++i) {
			free((char *)que->array + 
			     que->elemsize * i);
		}
	}
	que->size = 0;
	que->front = 1;
	que->rear = 0;
}

/* Return true if the queue is empty */
int 
queue_is_empty(Queue que)
{
	return que->size == 0;
}

/* Return true if the queue is full */
int 
queue_is_full(Queue que)
{
	return que->size == que->capacity;
}

static int 
successor(Queue que, int index)
{
	if ( ++index == que->capacity)
		index = 0;
	return index;
}

/* Insert a new element onto queue(rear) */
void 
queue_enqueue(Queue que, ElementAddr elemaddr)
{
	void *target;

	if ( queue_is_full(que) ) {
		fprintf(stderr, "Full queue\n");
		exit(1);
	}
	que->rear = successor(que, que->rear);
	target = (char *)que->array + que->elemsize * que->rear;
	memcpy(target, elemaddr, que->elemsize);
	que->size++;
}

/* Delete the front element off the queue */
void 
queue_dequeue(Queue que)
{
	if ( queue_is_empty(que) ) {
		fprintf(stderr, "Empty queue\n");
		exit(1);
	}
	if ( que->freefn ) {
		void *target = (char *)que->array +
			       que->front * que->elemsize;
		que->freefn(target);
	}
	que->size--;
	que->front = successor(que, que->front);
}

/* Fetch the front element from the queue */
void 
queue_front(Queue que, ElementAddr elemaddr)
{
	void *target = (char *)que->array + 
                       que->front * que->elemsize;
	memcpy(elemaddr, target, que->elemsize);
}

/* Fetch and Delete the front element from the queue */
void 
queue_front_and_dequeue(Queue que, ElementAddr elemaddr)
{
	void *target;

	if ( queue_is_empty(que) ) {
		fprintf(stderr, "Empty queue\n");
		exit(1);
	}

	target = (char *)que->array + 
                       que->front * que->elemsize;
	memcpy(elemaddr, target, que->elemsize);

	que->size--;
	que->front = successor(que, que->front);
}

