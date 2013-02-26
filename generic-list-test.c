#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic-list.h"

typedef void (*PfCbPrintElement)(const ElementAddr elemaddr);

void 
print_list(List list, PfCbPrintElement printfn)
{
	Position pos;

	if ( list_is_empty(list) ) {
		fprintf(stdout, "Empty list\n");
		return ;
	}

	for ( pos = list_get_first(list); 
	      !list_is_end(pos);
	      pos = list_next(pos)
	) {
		printfn(list_retrieve(pos));
	}
	
	printf("\n");
}

int 
int_equal(ElementAddr left, ElementAddr right)
{
	if ( *(int *)left == *(int *)right )
		return 1;
	return 0;
}

void 
print_int(ElementAddr elemaddr)
{
	printf("%d ", *(int *)elemaddr);
}

void 
stringfree(ElementAddr elemaddr)
{
	free(*(void **)elemaddr);
}

int 
str_equal(ElementAddr left, ElementAddr right)
{
	if ( strcmp((char *)(*(void **)left), (char *)(*(void **)right)) == 0 )
		return 1;
	return 0;
}

void 
print_str(ElementAddr elemaddr)
{
	printf("%s ", (char *)(*(void **)elemaddr));
}

int main(int argc, char **argv)
{
	List int_list, str_list;
	Position pos;
	int i;
	char *names[] = { 
		"C", "C++", "Jave", "C#", "Python", 
		"PHP", "Basic", "Objective C", "Matlab", "Golang" 
	};

	/* test int list */
	printf("Test int list\n");
	int_list = list_create(sizeof(int), NULL);
	pos = list_get_header(int_list);

	for ( i = 0; i < 10; ++i ) {
		list_insert(int_list, pos, &i);
		print_list(int_list, print_int);
		pos = list_next(pos);
	}

	for ( i = 0; i < 10; i += 2 ) {
		int delval;
		int is_found;
		is_found = list_delete(int_list, &i, int_equal, &delval);
		if ( is_found )
			printf("Delete: %d\n", delval );
	}

	for ( i = 0; i < 10; ++i)
		if ( (i % 2 == 0) == (list_find(int_list, &i, int_equal) != NULL) )
			printf("Find fails\n");

	printf("Finished deletions\n");

	print_list(int_list, print_int);

	list_dispose(int_list);


	/* test string list */
	printf("Test string list\n");
	str_list = list_create(sizeof(char *), stringfree);
	pos = list_get_header(str_list);

	for ( i = 0; i < sizeof(names) / sizeof(names[0]); ++i) {
		char *copy = strdup(names[i]);
		list_insert(str_list, pos, &copy);
		print_list(str_list, print_str);
		pos = list_next(pos);
	}
	
	for ( i = 0; i < sizeof(names) / sizeof(names[0]); i += 2) {
		char *delstr;
		int is_found;
		is_found = list_delete(str_list, &names[i], str_equal, &delstr);
		if ( is_found ) {
			printf("Delete: %s\n", delstr);
			free(delstr);
		}
	}

	for ( i = 0; i < 10; ++i ) {
		if ( (i % 2 == 0) == (list_find(str_list, &names[i], str_equal) != NULL))
			printf("Find fails\n");
	}

	printf("Finished deletions\n");
	
	print_list(str_list, print_str);
	list_dispose(str_list);

	return 0;
}

