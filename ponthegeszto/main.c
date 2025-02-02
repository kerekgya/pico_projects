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

    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(27);
    // Select ADC input 0 (GPIO26)
    adc_select_input(1);

    gpio_init(15);
    gpio_set_dir(15, GPIO_OUT);

    gpio_init(0);
    gpio_set_dir(0, 0);
    gpio_pull_down(0);

    while (1) {
        // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
        const float conversion_factor = 3.3f / (1 << 12);
        uint16_t result = adc_read();
        // printf("Raw value: 0x%03x, voltage: %f V, percentage: %f\n", result, result * conversion_factor, result * conversion_factor / 3.3f * 100);
        // sleep_ms(100);
        // if(result * conversion_factor / 3.3f > 0.5){
        //     gpio_put(15, 1);
        // } else {
        //     gpio_put(15, 0);
        // }
        if(gpio_get(0)){
            gpio_put(15, 1);
            sleep_ms(result * 1000 / (1 << 12));
            // printf("%f\n", result * 1000 / (1 << 12));
        }
        gpio_put(15, 0);
        
    }
}
