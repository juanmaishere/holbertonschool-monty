#include "monty.h"
int isInteger(const char string[])
{
    int i = 0;

    if (string[0] == '-') {
        
        if (string[1] == '\0') {
            return 0; 
        }
    }

    for ( i = (string[0] == '-') ? 1 : 0; string[i] != '\0'; i++) {
        if (!isdigit(string[i])) {
            return 0; 
        }
    }

    return 1;
}