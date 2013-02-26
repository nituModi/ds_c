/************************************************************************
 * 
 * File name:		calculate-expression.h
 * Description:		Calculate Expression API
 * Author:		dennis_fan(dennis_fan@outlook.com), 2013/2/26
 * Version:		1.0
 *************************************************************************/

#ifndef _CAL_EXPRESSION_H
#define _CAL_EXPRESSION_H


/* Balance symbols */
int balance_symbols(const char *expression);

/* Convert infix expression to postfix expression */
void infix2postfix(const char *infixexp, char *postfix);

/* Calculate postfix expression */
double calc_postfix_expression(const char *postexp);

/* Calculate infix expression */
double calc_infix_expression(const char *infixexp);

#endif /* THE END */
