/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

int main() {
    stdio_init_all();
    printf("ADC Example, measuring GPIO26\n");

    adc_init();

    adc_gpio_init(27);
    adc_select_input(1);

    gpio_init(15);
    gpio_set_dir(15, GPIO_OUT);
    gpio_put(15, 0);

    gpio_init(0);
    gpio_set_dir(0, 0);
    gpio_pull_up(0);

    while (1) {
        const float conversion_factor = 3.3f / (1 << 12);
        uint16_t result = adc_read();
        if(!gpio_get(0)){
            printf("Raw value: 0x%03x, voltage: %f V, percentage: %f\n", result, result * conversion_factor, result * conversion_factor / 3.3f * 100);
            gpio_put(15, 1);
            sleep_ms(result * 1000 / (1 << 12));
            gpio_put(15, 0);
            sleep_ms(250);
        }
        
    }
}
