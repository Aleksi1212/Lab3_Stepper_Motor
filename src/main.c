#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "../include/stdio.h"

int main(void) {
    stdio_init_all();
    
    while (true) {
        char *test = NULL;
        int status = read_line(&test);
        printf("%s\n", test);
    }
    return 0;
}
