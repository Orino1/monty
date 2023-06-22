#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

instruction_t instruction_cmd[] = {
	{"push", push},
	{"pall", pall},
	{"pint", pint},
	{"pop", pop},
	{"swap", swap},
	{"add", add},
	{"nop", nop},
	{"sub", sub},
	{"div", divide},
	{"mul", mul},
	{"mod", mod},
	{"pchar", pchar},
	{"pstr", pstr},
	{"rotl", rotl},
	{"rotr", rotr}
};

/**
 * main - Entry point of the program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return: EXIT_SUCCESS upon successful execution, EXIT_FAILURE otherwise.
 */
int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		FILE *file;
		char buffer_line[1024], *token;
		int cmd_num;
		unsigned int i;
		stack_t *top_element;

		top_element = NULL;
		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
			return (EXIT_FAILURE);
		}
		for (i = 1; fgets(buffer_line, sizeof(buffer_line), file) != NULL; i++)
		{
			if (line_checker(buffer_line) == 0)
			{
				cmd_num = sizeof(instruction_cmd) / sizeof(instruction_cmd[0]);
				token = strtok(buffer_line, " \n");
				if (cmd_finder(token, cmd_num, &top_element, i) == 1)
				{
					fprintf(stderr, "L%d: unknown instruction %s\n", i, token);
					exit(EXIT_FAILURE);
				}
			}
		}
		fclose(file);
		free_dlistint(top_element);
		return (EXIT_SUCCESS);
	}
	fprintf(stderr, "USAGE: monty file\n");
	return (EXIT_FAILURE);
}
