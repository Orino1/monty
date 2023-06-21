#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "monty.h"

stack_t *add_element_at_top(stack_t **top_element, int n)
{
	stack_t *new;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
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

void pall(stack_t **top_element, unsigned int line_number)
{
    stack_t *current;

    current = *top_element;
    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->prev;
    }
}
void push(stack_t **stack, unsigned int line_number)
{
    char *element_n;
    int i;

    element_n = strtok(NULL , " \n");
    if (element_n == NULL)
    {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }
    for (i = 0; element_n[i] != '\0'; i++)
    {
        if (isdigit(element_n[i]) == 0)
        {
            fprintf(stderr, "L%d: usage: push integer\n", line_number);
            exit(EXIT_FAILURE);
        }
    }
    add_element_at_top(stack, atoi(element_n));
}

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
void pop(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;

    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
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
void swap(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;
    int swapper;

    temp = (*stack)->prev;
    if (temp == NULL)
    {
        fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    swapper = temp->n;
    temp->n = (*stack)->n;
    (*stack)->n = swapper;
}
void add(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;
    int sum;

    temp = (*stack)->prev;
    if (temp == NULL)
    {
        fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    sum = temp->n;
    sum += (*stack)->n;
    pop(stack, line_number);
    (*stack)->n = sum;
}
void nop(stack_t **stack, unsigned int line_number)
{
}
void sub(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;
    int result;

    temp = (*stack)->prev;
    if (temp == NULL)
    {
        fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    result = (temp->n - (*stack)->n);
    pop(stack, line_number);
    (*stack)->n = result;
}
void divide(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;
    int result;

    temp = (*stack)->prev;
    if (temp == NULL)
    {
        fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%d: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }
    
    result = (temp->n / (*stack)->n);
    pop(stack, line_number);
    (*stack)->n = result;
}
void mul(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;
    int result;

    temp = (*stack)->prev;
    if (temp == NULL)
    {
        fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    result = (temp->n * (*stack)->n);
    pop(stack, line_number);
    (*stack)->n = result;
}
void mod(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;
    int result;

    temp = (*stack)->prev;
    if (temp == NULL)
    {
        fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }
    if ((*stack)->n == 0)
    {
        fprintf(stderr, "L%d: division by zero\n", line_number);
        exit(EXIT_FAILURE);
    }
    result = (temp->n % (*stack)->n);
    pop(stack, line_number);
    (*stack)->n = result;
}
void pchar(stack_t **stack, unsigned int line_number)
{
    char ascii_char;

    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }
    if ((*stack)->n > 127)
    {
        fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
        exit(EXIT_FAILURE);
    }
    ascii_char = (*stack)->n;
    printf("%c\n", ascii_char);
}
void pstr(stack_t **stack, unsigned int line_number)
{
    stack_t *temp;
    char ascii_char;
    int i;

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
void rotl(stack_t **stack, unsigned int line_number)
{
    stack_t *temp, *head;

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
void rotr(stack_t **stack, unsigned int line_number)
{
    stack_t *temp, *head;

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