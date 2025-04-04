#include <stdio.h>
#include <stdlib.h>

#include "stdio_utils.h"

int read_line(char **dst)
{
    int initial_size = 64;
    int pos = 0;
    
    *dst = (char *)malloc(initial_size * sizeof(char));
    if (dst == NULL)
        return 1;
    
    char chr;
    while((chr = getchar()) != EOF && chr != '\n' && chr != '\r')
    {
        if (pos >= initial_size)
        {
            initial_size *= 2;
            char *tmp = (char *)realloc(*dst, initial_size * sizeof(char));
            if (tmp == NULL) {
                free(dst);
                return 1;
            }

            *dst = tmp;
            free(tmp);
        }

        printf("%c", chr);
        (*dst)[pos++] = chr;
    }
    (*dst)[pos] = '\0';

    printf("\n");
    return 0;
}