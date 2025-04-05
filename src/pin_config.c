#include "pico/stdlib.h"

#include "constants.h"
#include "pin_config.h"

void init_input_pin(uint gpio)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_IN);
    gpio_pull_up(gpio);
}

void init_output_pin(uint gpio)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
}