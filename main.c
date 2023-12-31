#include "monty.h"
#define DELIM " \n\t\r"
data_t dat;
void _push(stack_t **stack, unsigned int line_number)
{
    (void)line_number;
    stack_t *node;

    if (!dat.tokens[1])
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    if (!isInteger(dat.tokens[1]))
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    node = malloc(sizeof(stack_t));
    if (!node)
    {
        perror("Error: Unable to allocate memory");
        exit(EXIT_FAILURE);
    }

    node->n = atoi(dat.tokens[1]);
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
        {"pint", _pint},
        {"pop", __pop},
        {"swap", _swap},
        {"add", _add},
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
    int read = 0;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        return (EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
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

        if (isvalid(dat.tokens[0]) == 0)
        {
            fprintf(stderr, "L%u: unknown instruction %s\n", line_number, dat.tokens[0]);
            exit(EXIT_FAILURE);
        }

        if (strcmp(dat.tokens[0], "push") == 0)
        {
            if (isInteger(dat.tokens[1]) == 0)
            {
                fprintf(stderr, "L%u: usage: push integer\n", line_number);
                exit(EXIT_FAILURE);
            }
        }
        
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
