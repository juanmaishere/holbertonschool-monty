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