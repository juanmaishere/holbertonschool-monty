#ifndef MONTY_H
#define MONTY_H
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
typedef struct stack_s
{
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;

typedef struct instruction_s
{
    char *opcode;
    void (*func)(stack_t **stack, unsigned int line_number);
} instruction_t;

typedef struct data_s
{
    stack_t *top;
    char *tokens[1000];
} data_t;

extern data_t dat;

int main(int argc, char *argv[]);
void _push(stack_t **stack, unsigned int line_number);
void _pall(stack_t **stack, unsigned int line_number);
void nop_f(stack_t **stack, unsigned int line_number);
void (*getfunc(char *op))(stack_t **stack, unsigned int line_number);

#endif