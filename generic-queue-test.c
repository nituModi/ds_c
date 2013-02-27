#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic-queue.h"

void strfreefn(ElementAddr elemaddr)
{
	free(*(char **)elemaddr);
}

int 
main(int argc, char **argv)
{
	Queue int_que, str_que;
	int i;
	char *names[] = { 
		"C", "C++", "Jave", "C#", "Python", 
		"PHP", "Basic", "Objective C", "Matlab", "Golang" 
	};

	/* test integer queue */
	printf("Test integer queue\n");
	int_que = queue_create(sizeof(int), 15, NULL);
	for ( i = 0; i < 10; ++i ) {
		queue_enqueue(int_que, &i);
	}

	while ( !queue_is_empty(int_que) ) {
		int val;
		queue_front_and_dequeue(int_que, &val);
		printf("%d\n", val);
	}
	
	queue_dispose(int_que);

	/* test string queue */
	printf("Test string queue\n");
	str_que = queue_create(sizeof(char *), 15, strfreefn);
	for ( i = 0; i < 10; ++i ) {
		char *copy = strdup(names[i]);
		char *dest;
		queue_enqueue(str_que, &copy);
	}
	
	while ( !queue_is_empty(str_que) ) {
		char *dest;
		queue_front_and_dequeue(str_que, &dest);
		printf("%s\n", dest);
		free(dest);
	}
	queue_dispose(str_que);

	return 0;
}

