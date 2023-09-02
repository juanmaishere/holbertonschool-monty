#include "monty.h"
int
isInteger(const char string[])
{
    
    int i = 0;
   
   if (string == NULL || string[0] == '\0') {
        return 0;
    }
    if (string[i] == '+' || string[i] == '-') {
        i++;
    }
    while (string[i]) {
        if (!isdigit(string[i])) {
            return 0;
        }
        i++;
    }
    return 1;
}
void
_pint(stack_t **stack, unsigned int line_number)
{
    (void)line_number;
    c = isvalid(dat.tokens[0]);

    if (c == 0)
    {
    fprintf(stderr, "L%u: unknown instruction %s", line_number, dat.tokens[0]);
        exit(EXIT_FAILURE);
    }

	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	stack_t *line = *stack;
    printf("%d\n", line->n);
}
int
isvalid(const char *instruction)
{
    int len = strlen(instruction);

    if (len > 4)
    {
        return (0);
    }
    else
    {
        return (1);
    }
}