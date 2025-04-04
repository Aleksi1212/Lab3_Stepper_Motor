#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "stdio_utils.h"

int main(void) {
    stdio_init_all();
    
    while (true) {
        char *command = NULL;
        int status = read_line(&command);

        if (status > 0 || command == NULL) {
            printf("Inalid commad\n");
            continue;
        }


    }
    return 0;
}
