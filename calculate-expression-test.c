#include <stdio.h>
#include "calculate-expression.h"

#define MAX_LINE 300

/**
 * 写的不错，加油！
 */
int 
main(int argc, char **argv)
{
	char infixexp[MAX_LINE+1], postfixexp[MAX_LINE+1];
	while ( gets(infixexp) ) {
		printf("expression: %s\n", infixexp);
		if ( !balance_symbols(infixexp) )
			printf("Fail to Convert infix to postfix\n");
		else {
			infix2postfix(infixexp, postfixexp);
			printf("Convert infix to postfix successful: %s\n",
                                postfixexp);
			printf("Result: infixexp %f; postfixexp %f\n", 
			       	calc_infix_expression(infixexp), calc_postfix_expression(postfixexp));
		}
	}

	return 0;
}

