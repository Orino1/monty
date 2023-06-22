#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "monty.h"

/**
 * mod - Computes the modulus of the second top element by the top
 * element of the stack.
 * @stack: A double pointer to the top of the stack.
 * @line_number: The line number where the mod operation is performed.
 */
void mod(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	int result;

	temp = (*stack)->prev;
	if (temp == NULL)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_number);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
	result = (temp->n % (*stack)->n);
	pop(stack, line_number);
	(*stack)->n = result;
}

/**
 * pchar - Prints the character corresponding to the top element of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the pchar operation is performed.
 *
 * Description: Prints the character value of the top element in the stack.
 * If the stack is empty, it displays an error message and exits with failure.
 * If the top element is out of the ASCII range, it displays an error message
 * and exits with failure. Otherwise, it prints the character.
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	char ascii_char;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n > 127)
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
		free_dlistint(*stack);
		exit(EXIT_FAILURE);
	}
	ascii_char = (*stack)->n;
	printf("%c\n", ascii_char);
}

/**
 * pstr - Prints the string contained in the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the pstr operation is performed.
 *
 * Description: Prints the string formed by the ASCII values in the stack.
 * If the stack is empty, it prints a newline character. Otherwise, it iterates
 * through the stack, converting the ASCII values to characters and
 * printing them, until a non-printable character or a value out of
 * the ASCII range is encountered.
 * It then prints a newline character.
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	char ascii_char;
	int i;

	(void)line_number;
	if (*stack == NULL)
	{
		printf("\n");
	}
	else
	{
		temp = *stack;
		for (i = 0; temp != NULL; i++)
		{
			if (temp->n <= 0 || temp->n > 127)
			{
				break;
			}
			ascii_char = temp->n;
			printf("%c", ascii_char);
			temp = temp->prev;
		}
		printf("\n");
	}
}

/**
 * rotl - Rotates the stack to the left, moving the top element to the bottom.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the rotl operation is performed.
 *
 * Description: Rotates the stack by moving the top element to the bottom.
 * If the stack is not empty and has more than one element, it performs
 * the rotation by updating the appropriate pointers. The top element
 * becomes the new bottom element, and the rest of the elements shift
 * up. If the stack is empty or has only one element, no rotation occurs.
 */
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *temp, *head;

	(void)line_number;
	temp = *stack;
	head = *stack;
	if (temp != NULL && temp->prev != NULL)
	{
		while (head->prev != NULL)
		{
			head = head->prev;
		}
		(temp->prev)->next = NULL;
		temp->prev = NULL;
		temp->next = head;
		head->prev = temp;
		while ((*stack)->next != NULL)
		{
			*stack = (*stack)->next;
		}
	}
}

/**
 * rotr - Rotates the stack to the right, moving the bottom element to the top.
 * @stack: Double pointer to the top of the stack.
 * @line_number: Line number where the rotr operation is performed.
 *
 * Description: Rotates the stack by moving the bottom element to the top.
 * If the stack is not empty and has more than one element, it performs
 * the rotation by updating the appropriate pointers. The bottom element
 * becomes the new top element, and the rest of the elements shift
 * down. If the stack is empty or has only one element, no rotation occurs.
 */
void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp, *head;

	(void)line_number;
	head = *stack;
	if (head != NULL && head->prev != NULL)
	{
		while (head->prev != NULL)
		{
			head = head->prev;
		}
		temp = head->next;
		temp->prev = NULL;
		head->next = NULL;
		head->prev = *stack;
		(*stack)->next = head;
		*stack = head;
	}
}
