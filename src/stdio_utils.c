#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stdio_utils.h"
#include "constants.h"

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

int split_command(char *command, const char *delimeter, char *output_arr[])
{
    int count = 0;
    char *token = strtok(command, delimeter);

    while (token != NULL && count < MAX_COMMAND_SIZE)
    {
        output_arr[count++] = token;
        token = strtok(NULL, delimeter);
    }

    return count; 
}

int valid_char_digit(const char *str)
{
    if (str == NULL || *str == '\0') {
        return 0;
    }

    while (*str == ' ') {
        str++;
    }

    if (*str == '-') {
        str++;
    }

    while (*str) {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }

    return 1;
}