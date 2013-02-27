/************************************************************************
 * 
 * File name:		generic-queue.h
 * Description:		Queue's API
 * Author:		dennis_fan(dennis_fan@outlook.com), 2013/2/26
 * Version:		1.0
 *************************************************************************/

#ifndef _GENERIC_QUEUE_H
#define _GENERIC_QUEUE_H

typedef void *ElementAddr;
typedef void (*PfCbFree)(ElementAddr);

typedef struct QueueRecord
{
	ElementAddr	*array;
	int		capacity;
	int		elemsize;
	int		front;
	int		rear;
	int		size;
	PfCbFree	freefn;
} *Queue;

/* Create a new queue */
Queue queue_create(int elemsize, int capacity, PfCbFree freefn);

/* Dispose the queue */
void queue_dispose(Queue que);

/* Make the give queue empty */
void queue_make_empty(Queue que);

/* Return true if the queue is empty */
int queue_is_empty(Queue que);

/* Return true if the queue is full */
int queue_is_full(Queue que);

/* Insert a new element onto queue */
void queue_enqueue(Queue que, ElementAddr elemaddr);

/* Delete the front element off the queue */
void queue_dequeue(Queue que);

/* Fetch the front element from the queue */
void queue_front(Queue que, ElementAddr elemaddr);

/* Fetch and Delete the front element from the queue */
void queue_front_and_dequeue(Queue que, ElementAddr elemaddr);

#endif /* THE END */

