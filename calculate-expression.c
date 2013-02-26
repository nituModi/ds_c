/************************************************************************
 * 
 * File name:		calculate-expression.c
 * Description:		Balance Symbols Problem
 * Author:		dennis_fan(dennis_fan@outlook.com), 2013/2/26
 * Version:		1.0
 *************************************************************************/

#include "calculate-expression.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "generic-stack.h"

/* Balance symbols */
int 
balance_symbols(const char *expression)
{
	Stack symstk;
	char c, top;
	int current_success = 1;

	symstk = stack_create(sizeof(char), NULL);
	
	/* On-line Algorithm */
	while ( (c = *expression++) != '\0' ) {
		if ( c == '(' || c == '[' || c == '{')
			stack_push(symstk, &c);
		else if ( c == ')' || c == ']' || c == '}' ) {
			if ( stack_is_empty(symstk) ) {
				current_success = 0;
				break;
			}
			stack_top(symstk, &top);
			if ( c == ')' && top == '(' || 
			     c == ']' && top == '[' ||
			     c == '}' && top == '{'
			) {
				stack_pop(symstk);
			} else {
				current_success = 0;
				break;
			}
		}
	}

	if ( !stack_is_empty(symstk) )
		current_success = 0;

	#if 0
	if ( current_success)
		fprintf(stdout, "Success...\n");
	else 
		fprintf(stdout, "Fail...\n");
	#endif

	return current_success;
}

static int 
priority(int c)
{
	if ( c == '+' || c == '-' )
		return 1;
	if ( c == '*' || c == '/' )
		return 2;
	if ( c == '(' )
		return 3;
	fprintf(stderr, "Undefine this operator's priority\n");
	exit(1);
}

static int 
is_operator(int c)
{
	return c == '+' || c == '-' || 
	       c == '*' || c == '/' || c == '(';
}

/* Convert infix expression to postfix expression */
void 
infix2postfix(const char *infixexp, char *postfix)
{
	Stack operator_stk;
	char c = '(', top;
	int is_still_digit = 0;

	postfix[0] = '\0'; /* NULL in the beginning */

	operator_stk = stack_create(sizeof(char), NULL);
	/* Ensure the stack is not empty */
	stack_push(operator_stk, &c);

	while ( (c = *infixexp++) != '\0' ) {
		if ( isdigit(c) || c == '.' ) {		/* 1. operands */
			if ( is_still_digit ) {
				sprintf(postfix, "%s%c", postfix, c);
			} else {
				sprintf(postfix, "%s %c", postfix, c);
				is_still_digit = 1;
			}
		} else {
			is_still_digit = 0;
			if ( c == ')' ) {		/* 2. ')' */
				while ( stack_top_and_pop(operator_stk, &top), 
					top != '(' ) {
					sprintf(postfix, "%s %c", postfix, top);
				}
				/* Pop '(' */
				// stack_pop(operator_stk);
			} else if ( is_operator(c) ) {
				for ( stack_top(operator_stk, &top);
				      top != '(' && priority(c) <= priority(top);
				      stack_top(operator_stk, &top)) {
					sprintf(postfix, "%s %c", postfix, top);
					stack_pop(operator_stk);
				}
				/* Push the current operator */
				stack_push(operator_stk, &c);
			}
		}
	}
	
	while ( !stack_is_empty(operator_stk) ) {
		stack_top(operator_stk, &top);
		if ( top != '(' )
			sprintf(postfix, "%s %c", postfix, top);
		stack_pop(operator_stk);
	}
}

static double
calculate(char operator, double left, double right)
{
	double res;

	switch ( operator ) {
	case '+': 
		res = left + right;
		break;
	case '-':
		res = left - right;
		break;
	case '*':
		res = left * right;
		break;
	case '/':
		res = left / right;
		break;
	default:
		fprintf(stderr, "Undefined this operator\n");
		exit(1);
	}
	return res;
}

/* Calculate postfix expression */
double 
calc_postfix_expression(const char *postexp)
{
	Stack operand_stk;
	char c;
	double partial_res = 0, exp = 0.1;
	double left_operand, right_operand;
	int is_still_digit = 0, is_after_punct = 0;

	operand_stk = stack_create(sizeof(double), NULL);
	
	while ( (c = *postexp++) != '\0' ) {
		if ( isdigit(c) || c == '.' ) {		/* operand: digit & '.' */
			if ( !is_still_digit ) {
				partial_res = 0;
				is_still_digit = 1;
			} 
			if ( c == '.' )	/* '.' */
				is_after_punct = 1;
			else {
				if ( !is_after_punct )
					partial_res = partial_res * 10 +  (c - '0');
				else {
					partial_res += (c - '0') * exp;
					exp *= 0.1;
				}
			}	
		} else {				/* others */
			if ( is_still_digit ) {
				stack_push(operand_stk, &partial_res);
				is_still_digit = 0;
				is_after_punct = 0;
				exp = 0.1;
			}
			if ( is_operator(c) ) {
				stack_top_and_pop(operand_stk, &right_operand);
				stack_top_and_pop(operand_stk, &left_operand);
				partial_res = calculate(c, left_operand, right_operand);
				stack_push(operand_stk, &partial_res);
			}
		}
	}
	
	stack_top_and_pop(operand_stk, &partial_res);
	return partial_res;
}

/* Calculate infix expression */
double 
calc_infix_expression(const char *infixexp)
{
	Stack operator_stk, operand_stk;
	char c = '(', top;
	double partial_res, exp = 0.1;
	double left_operand, right_operand;
	int is_still_digit = 0, is_after_punct = 0;
	
	operand_stk = stack_create(sizeof(double), NULL);
	operator_stk = stack_create(sizeof(char), NULL);
	stack_push(operator_stk, &c);	/* Ensure the stack is not empty */


	while ( (c = *infixexp++) != '\0' ) {
		if ( isdigit(c) || c == '.' ) {		/* 1. operand: digit & '.' */
			if ( !is_still_digit ) {
				partial_res = 0;
				is_still_digit = 1;
			} 
			if ( c == '.' )	/* '.' */
				is_after_punct = 1;
			else {		/* digit */
				if ( !is_after_punct )
					partial_res = partial_res * 10 +  (c - '0');
				else {
					partial_res += (c - '0') * exp;
					exp *= 0.1;
				}
			}	
		} else {				/* others */
			if ( is_still_digit ) {
				stack_push(operand_stk, &partial_res);
				is_still_digit = 0;
				is_after_punct = 0;
				exp = 0.1;
			}
			if ( c == ')' ) {		/* 2: ')' */
				while ( stack_top_and_pop(operator_stk, &top), top != '(' ) {
					stack_top_and_pop(operand_stk, &right_operand);
					stack_top_and_pop(operand_stk, &left_operand);
					partial_res = calculate(top, left_operand, right_operand);
					stack_push(operand_stk, &partial_res);
				}
			} else if ( is_operator(c) ) {	/* 3: operators */
				for ( stack_top(operator_stk, &top);
				      top != '(' && priority(c) <= priority(top);
				      stack_top(operator_stk, &top)) {
					stack_top_and_pop(operand_stk, &right_operand);
					stack_top_and_pop(operand_stk, &left_operand);
					partial_res = calculate(top, left_operand, right_operand);
					stack_push(operand_stk, &partial_res);
					stack_pop(operator_stk);
				}
				/* Push the current operator */
				stack_push(operator_stk, &c);
			}
			
		}
	}

	if ( is_still_digit ) {
		stack_push(operand_stk, &partial_res);
		is_still_digit = 0;
		is_after_punct = 0;
		exp = 0.1;
	}

	while ( !stack_is_empty(operator_stk) ) {
		stack_top_and_pop(operator_stk, &top);
		if ( top != '(' ) {
			stack_top_and_pop(operand_stk, &right_operand);
			stack_top_and_pop(operand_stk, &left_operand);
			partial_res = calculate(top, left_operand, right_operand);
			stack_push(operand_stk, &partial_res);
		}
	}
	stack_top_and_pop(operand_stk, &partial_res);

	return partial_res;	
}

