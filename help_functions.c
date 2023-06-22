#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "monty.h"

/**
 * add_element_at_top - Adds a new element at the top of the stack.
 * @top_element: Double pointer to the top element of the stack.
 * @n: Value to be stored in the new element.
 *
 * Return: Pointer to the newly added element.
*/
stack_t *add_element_at_top(stack_t **top_element, int n)
{
	stack_t *new;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_dlistint(*top_element);
		exit(EXIT_FAILURE);
	}
	new->n = n;
	if (*top_element == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		*top_element = new;
		return (new);
	}
	new->next = NULL;
	new->prev = *top_element;
	(*top_element)->next = new;
	*top_element = new;
	return (new);
}

/**
 * free_dlistint - Frees a doubly linked list.
 * @current: Pointer to the current node in the doubly linked list.
 *
 * Description: Frees the memory allocated for a doubly linked list.
 * It starts from the current node and iterates through the list,
 * freeing each node until the end.
 * If the current node is NULL, no action is performed.
 */
void free_dlistint(stack_t *current)
{
	stack_t *next, *head;

	if (current != NULL)
	{
		head = current;
		while (head->prev != NULL)
		{
			head = head->prev;
		}
		while (head->next != NULL)
		{
			next = head->next;
			free(head);
			head = next;
		}
		free(head);
	}
}
