#include "monty.h"

data_t dat;

void _push(stack_t **stack, unsigned int line_number)
{
    int c = 0;
    stack_t *node;

    if (!dat.tokens[1])
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    c = atoi(dat.tokens[1]);

    node = malloc(sizeof(stack_t));
    if (!node)
    {
        perror("Error: Unable to allocate memory");
        exit(EXIT_FAILURE);
    }

    node->n = c;
    node->prev = NULL;
    node->next = *stack;

    if (*stack)
        (*stack)->prev = node;

    *stack = node;
}
void
_pall(stack_t **stack, __attribute__((unused))unsigned int line_number)
{
    stack_t *temp = *stack;

    while (temp != NULL)
    {
        printf("%d\n", temp->n);
        temp = temp->next;
    }
}
void
nop_f(stack_t **stack, unsigned int line_number)
{
    (void)stack;
    (void)line_number;
}
void
(*getfunc(char *op))(stack_t **stack, unsigned int line_number)
{
    int i = 0;

    instruction_t instructions[] =
    {
        {"push", _push},
        {"pall", _pall},
        {"nop", nop_f},
        {NULL, NULL}
    };

    while (instructions[i].opcode != NULL)
    {
        if (strcmp(op, instructions[i].opcode) == 0)
        {
            return instructions[i].func;
        }
        i++;
    }

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int line_number = 0;
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        return (EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return (EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, file)) != -1)
    {
        line_number++;

        int i = 0;
        char *tokens[1000], *tok;
        tok = strtok(line, " \t\n");
        while (tok != NULL)
        {
            tokens[i] = strdup(tok);
            tok = strtok(NULL, " \t\n");
            i++;
        }

        dat.tokens[0] = tokens[0];
        dat.tokens[1] = tokens[1];

        void (*instruction_func)(stack_t **, unsigned int) = getfunc(dat.tokens[0]);
        if (instruction_func)
        {
            instruction_func(&dat.top, line_number);
        }
        else
        {
            fprintf(stderr, "L%u: Invalid instruction %s\n", line_number, dat.tokens[0]);
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < i; j++)
        {
            free(tokens[j]);
        }
    }

    if (line)
        free(line);

    fclose(file);

    while (dat.top != NULL)
    {
        stack_t *temp = dat.top;
        dat.top = dat.top->next;
        free(temp);
    }

    return (EXIT_SUCCESS);
}
