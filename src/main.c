#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"

#include "constants.h"
#include "stdio_utils.h"
#include "pin_config.h"

static int STEPS[STEP_COUNT][STEPS_COUNT] =
{
    { 1, 0, 0, 0 },
    { 1, 1, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 1 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 }
};

int main(void) {
    stdio_init_all();
    
    init_input_pin(OPTO_FORK);

    init_output_pin(IN_1);
    init_output_pin(IN_2);
    init_output_pin(IN_3);
    init_output_pin(IN_4);

    bool calibrated = false;
    int steps_per_revolution = 0;
    int stopped_step = 0;

    char *command = NULL;
    while (true) {
        if (command == NULL) {
            int status = read_line(&command);
            if (status > 0) {
                fprintf(stderr, "An error occurred\n");
                return status;
            }
        }

        if (strcmp(command, "spin") == 0) {
            int rot = (4096/8)*(1.0/8.0);
            printf("rot: %d\n", rot);
            for (int j = 0; j < rot; j++) {
                printf("%d\n", j);
                for (int i = 0; i < 8; i++) {
                    // if (gpio_get(OPTO_FORK) == 0) {
                    //     stopped_step = i;
                    //     break;
                    // }
    
                    gpio_put(IN_1, STEPS[i][0]);
                    gpio_put(IN_2, STEPS[i][1]);
                    gpio_put(IN_3, STEPS[i][2]);
                    gpio_put(IN_4, STEPS[i][3]);
                    
                    
                    // steps_per_revolution++;
                    sleep_ms(2);
                }
            }
            command = NULL;
        }

        if (strcmp(command, "calib") == 0) {
            // printf("Calibrating...\n");

            int revolutions = 0;
            while (revolutions < 3)
            {
                printf("Rvolution %d\n", revolutions);
                for (int i = stopped_step; i < STEP_COUNT; i++) {
                    if (gpio_get(OPTO_FORK) == 0) {
                        stopped_step = i;
                        printf("%d\n", stopped_step);
                        break;
                    }

                    gpio_put(IN_1, STEPS[i][0]);
                    gpio_put(IN_2, STEPS[i][1]);
                    gpio_put(IN_3, STEPS[i][2]);
                    gpio_put(IN_4, STEPS[i][3]);
                    
                    
                    // steps_per_revolution++;
                    sleep_ms(2);
                }
                revolutions++;
            }

            calibrated = true;
            // steps_per_revolution /= 3;            
            // printf("Calibrated\n");

        }

        // if (strcmp(command, "status") == 0) {
        //     if (calibrated) {
        //         printf("Motor is calibrated\n");
        //         printf("Steps per revolution %d\n", steps_per_revolution);
        //     } else {
        //         printf("Motor is not calibrated\n");
        //         printf("Not available\n");
        //     }
        // }

        // if (strcmp(command, "calib") == 0) {
        //     printf("calibrating...\n");
        //     for (int i = 0; i < STEP_COUNT; i++) {
        //         // if (gpio_get(OPTO_FORK) == 0) {
        //         //     calibrated = true;
        //         //     break;
        //         // }

        //         gpio_put(IN_1, STEPS[i][0]);
        //         gpio_put(IN_2, STEPS[i][1]);
        //         gpio_put(IN_3, STEPS[i][2]);
        //         gpio_put(IN_4, STEPS[i][3]);
        //         sleep_ms(2);
        //     }
        // }

        // if (!calibrated) {

        // }
        // else {
        //     printf("Calibrated\n");
        // }
    }
    return 0;
}
