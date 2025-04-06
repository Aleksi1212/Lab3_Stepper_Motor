#ifndef STDIO_UTILS_H
#define STDIO_UTILS_H

int read_line(char **dst);
int split_command(char *command, const char *delimeter, char *output_arr[]);
int valid_char_digit(const char *str);

#endif