#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "monty.h"

/**
 * add - Adds the top two elements of the stack.
 * @stack: A double pointer to the top of the stack.
 * @line_number: The line number where the add operation is performed.
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	int sum;

	temp = (*stack)->prev;
	if (temp == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
	sum = temp->n;
	sum += (*stack)->n;
	pop(stack, line_number);
	(*stack)->n = sum;
}

/**
 * nop - Does nothing.
 * @stack: A double pointer to the top of the stack.
 * @line_number: The line number where the nop operation is performed.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)line_number;
	(void)stack;
}

/**
 * sub - Subtracts the top element from the second top element of the stack.
 * @stack: A double pointer to the top of the stack.
 * @line_number: The line number where the sub operation is performed.
 */
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	int result;

	temp = (*stack)->prev;
	if (temp == NULL)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
	result = (temp->n - (*stack)->n);
	pop(stack, line_number);
	(*stack)->n = result;
}

/**
 * divide - Divides the second top element by the top element of the stack.
 * @stack: A double pointer to the top of the stack.
 * @line_number: The line number where the divide operation is performed.
 */
void divide(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	int result;

	temp = (*stack)->prev;
	if (temp == NULL)
	{
		fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_number);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
	result = (temp->n / (*stack)->n);
	pop(stack, line_number);
	(*stack)->n = result;
}

/**
 * mul - Multiplies the second top element with the top element of the stack.
 * @stack: A double pointer to the top of the stack.
 * @line_number: The line number where the mul operation is performed.
 */
void mul(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	int result;

	temp = (*stack)->prev;
	if (temp == NULL)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
	result = (temp->n * (*stack)->n);
	pop(stack, line_number);
	(*stack)->n = result;
}
