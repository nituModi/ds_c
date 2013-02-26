#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic-stack.h"

void strfreefn(ElementAddr elemaddr)
{
	free(*(char **)elemaddr);
}

int 
main(int argc, char **argv)
{
	Stack int_stk, str_stk;
	int i;
	char *names[] = { 
		"C", "C++", "Jave", "C#", "Python", 
		"PHP", "Basic", "Objective C", "Matlab", "Golang" 
	};

	/* test integer stack */
	printf("Test integer stack\n");
	int_stk = stack_create(sizeof(int), NULL);
	for ( i = 0; i < 10; ++i ) {
		stack_push(int_stk, &i);
	}

	while ( !stack_is_empty(int_stk) ) {
		int val;
		stack_top_and_pop(int_stk, &val);
		printf("%d\n", val);
	}
	
	stack_dispose(int_stk);

	/* test string stack */
	printf("Test string stack\n");
	str_stk = stack_create(sizeof(char *), strfreefn);
	for ( i = 0; i < 10; ++i ) {
		char *copy = strdup(names[i]);
		char *dest;
		stack_push(str_stk, &copy);
	}
	
	while ( !stack_is_empty(str_stk) ) {
		char *dest;
		stack_top_and_pop(str_stk, &dest);
		printf("%s\n", dest);
		free(dest);
	}
	stack_dispose(str_stk);

	return 0;
}

