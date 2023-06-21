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

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        FILE *file;
        char buffer[BUFFER], *token;
        int cmd_num;
        unsigned int i;
        stack_t *head, *top_element;


        head = NULL;
        top_element = head;
        file = fopen(argv[1], "r");
        if (file == NULL)
        {
            fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
            return (EXIT_FAILURE);
        }
        for (i = 1; fgets(buffer, sizeof(buffer), file) != NULL; i++)
        {
            if (line_checker(buffer) == 0)
            {
                cmd_num = sizeof(instruction_cmd)/sizeof(instruction_cmd[0]);
                token = strtok(buffer , " \n");
                if (cmd_finder(token, cmd_num, &top_element, i) == 1)
                {
                    fprintf(stderr, "L%d: unknown instruction %s\n", i, token);
                    free(token);
                    exit(EXIT_FAILURE);
                }
            }
        }
        fclose(file);
        return (EXIT_SUCCESS);
    }
    fprintf(stderr, "USAGE: monty file\n");
    return (EXIT_FAILURE);
}
