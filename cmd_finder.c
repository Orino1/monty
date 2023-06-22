#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

/**
 * cmd_finder - Finds and executes a command based on the given token.
 * @tok: The token representing the command to be found.
 * @num: The number of elements in the instruction command array.
 * @top: A double pointer to the top element of the stack.
 * @line: The line number where the command is being executed.
 *
 * Return: 0 if the command is found and executed successfully, 1 otherwise.
 */
int cmd_finder(char *tok, int num, stack_t **top, unsigned int line)
{
	int i;

	for (i = 0; i < num; i++)
	{
		if (strcmp(instruction_cmd[i].opcode, tok) == 0)
		{
			instruction_cmd[i].f(top, line);
			return (0);
		}
	}
	return (1);
}

/**
 * line_checker - Checks if a string is empty or contains only
 * whitespace or a comment.
 * @buffer: A pointer to a string to check.
 *
 * Return: 1 if the string is empty or contains only whitespace
 * or a comment, 0 otherwise.
 */
int line_checker(char *buffer)
{
	int i;

	if (buffer[0] == '#')
	{
		return (1);
	}
	if (strcmp("\n", buffer) == 0)
	{
		return (1);
	}
	for (i = 0; buffer[i] != '\n'; i++)
	{
		if (buffer[i] != ' ')
		{
			return (0);
		}
	}
	return (1);
}
