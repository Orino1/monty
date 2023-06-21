#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

int cmd_finder(char *token, int cmd_num, stack_t **top_element, unsigned int line_number)
{
    int i;

    for (i = 0; i < cmd_num; i++)
    {
        if (strcmp(instruction_cmd[i].opcode, token) == 0)
        {
            instruction_cmd[i].f(top_element, line_number);
            return (0);
        }
    }
    return (1);
}

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
