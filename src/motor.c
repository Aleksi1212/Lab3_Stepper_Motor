#include "pico/stdlib.h"

#include "constants.h"
#include "motor.h"

static int SEQUENCE[SEQUENCE_COUNT][STEPS_COUNT] = {
    { 1, 0, 0, 0 },
    { 1, 1, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 1, 1, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 1, 1 },
    { 0, 0, 0, 1 },
    { 1, 0, 0, 1 }
};

static void half_step_motor(int *current_step)
{
    gpio_put(IN_1, SEQUENCE[*current_step][0]);
    gpio_put(IN_2, SEQUENCE[*current_step][1]);
    gpio_put(IN_3, SEQUENCE[*current_step][2]);
    gpio_put(IN_4, SEQUENCE[*current_step][3]);

    *current_step = (*current_step + 1) % SEQUENCE_COUNT;
    sleep_ms(1);
}

int calibrate_motor(int *current_step)
{
    int steps = 0;

    while (gpio_get(OPTO_FORK))
        half_step_motor(current_step);

    while (!gpio_get(OPTO_FORK)) {
        half_step_motor(current_step);
        steps += 3;
    }

    while (gpio_get(OPTO_FORK)) {
        half_step_motor(current_step);
        steps += 3;
    }

    return steps / 3;
}

void run(const int steps, int *current_step)
{
    for (int i = 0; i < steps; i++) {
        half_step_motor(current_step);
    }
}