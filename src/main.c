#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"

#include "constants.h"
#include "stdio_utils.h"
#include "pin_config.h"
#include "motor.h"

int main(void) {
    stdio_init_all();

    init_input_pin(OPTO_FORK);

    init_output_pin(IN_1);
    init_output_pin(IN_2);
    init_output_pin(IN_3);
    init_output_pin(IN_4);

    bool calibrated = false;
    int steps_per_revolution = 0;
    int current_step = 0;

    char *command = NULL;
    while (true) {
        if (command == NULL) {
            int status = read_line(&command);
            if (status > 0) {
                command = NULL;
                fprintf(stderr, "An error occurred\n");
                return status;
            }
        }

        char *splitted_command[MAX_COMMAND_SIZE];
        int split_count = split_command(command, " ", splitted_command);

        if (split_count > 0) {
            if (strcmp(splitted_command[0], "status") == 0) {
                if (calibrated) {
                    printf("Motor is calibrated.\n");
                    printf("Steps per revolution: %d.\n", steps_per_revolution);
                } else {
                    printf("Motor is not calibrated.\n");
                    printf("Steps per revolution: Not available.\n");
                }
            }
    
            else if (strcmp(splitted_command[0], "calib") == 0) {
                printf("Calibrating...\n");
                steps_per_revolution = calibrate_motor(&current_step);
                calibrated = true;
                printf("Calibrated.\n");
            }

            else if (strcmp(splitted_command[0], "run") == 0) {
                if (calibrated) {
                    int N = SEQUENCE_COUNT;
                    int steps = (steps_per_revolution * N) / SEQUENCE_COUNT;
    
                    if (split_count > 1) {
                        if (valid_char_digit(splitted_command[1])) {
                            N = atoi(splitted_command[1]);
                            if (N < 1) {
                                fprintf(stderr, "Too small.\n");
                            } else {
                                printf("Running %d/%d of a revolution.\n", N, SEQUENCE_COUNT);
                                steps = (steps_per_revolution * N) / SEQUENCE_COUNT;
                                run(steps, &current_step);
                                printf("Completed.\n");
                            }
                        } else {
                            fprintf(stderr, "%s not an integer.\n", splitted_command[1]);
                        }
                    } else {
                        printf("Running 1 revolution.\n");
                        run(steps, &current_step);
                        printf("Completed.\n");
                    }
                } else {
                    fprintf(stderr, "Not calibrated.\n");
                } 
            }

            else {
                printf("Invalid command.\n");
            }
        } else {
            printf("No commands provided.\n");
        }

        command = NULL;
    }
    return 0;
}
