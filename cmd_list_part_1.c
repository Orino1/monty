#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "monty.h"

/**
 * pall - prints all the elements in a stack
 * @top_element: the top element of the stack
 * @line_number: the line number of the command
 *
 * Return: void
 */
void pall(stack_t **top_element, unsigned int line_number)
{
	stack_t *current;

	(void)line_number;
	current = *top_element;
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->prev;
	}
}

/**
 * push - add an integer to the top of a stack
 *
 * @stack: a pointer to the stack
 * @line_number: the line number in the file being read
 *
 * Description: This function reads the next integer from the input file and
 * adds it to the top of the stack. If there is no integer, or the input is not
 * a valid integer, an error message is printed to standard error and the
 * program exits with a failure status. The stack is implemented as a doubly
 * linked list.
 */
void push(stack_t **stack, unsigned int line_number)
{
	char *element_n;
	int i;

	element_n = strtok(NULL, " \n");
	if (element_n == NULL)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
	for (i = 0; element_n[i] != '\0'; i++)
	{
		if (isdigit(element_n[i]) == 0)
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			free_dlistint(*stack);
			exit(EXIT_FAILURE);
		}
	}
	add_element_at_top(stack, atoi(element_n));
}

/**
 * pint - Prints the value at the top of the stack.
 * @stack: A double pointer to the top of the stack.
 * @line_number: The line number where the pint operation is performed.
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack != NULL)
	{
		printf("%d\n", (*stack)->n);
	}
	else
	{
		printf("L%d: can't pint, stack empty\n", line_number);
	}
}

/**
 * pop - Removes the top element of the stack.
 * @stack: A double pointer to the top of the stack.
 * @line_number: The line number where the pop operation is performed.
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
	temp = (*stack)->prev;
	if (temp == NULL)
	{
		free(*stack);
		*stack = temp;
	}
	else
	{
		temp->next = NULL;
		free(*stack);
		*stack = temp;
	}
}

/**
 * swap - Swaps the top two elements of the stack.
 * @stack: A double pointer to the top of the stack.
 * @line_number: The line number where the swap operation is performed.
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	int swapper;

	temp = (*stack)->prev;
	if (temp == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
	swapper = temp->n;
	temp->n = (*stack)->n;
	(*stack)->n = swapper;
}
