#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"

#include "hardware/pio.h"
#include "dimmer.pio.h"

#include <math.h>



// static inline void put_time(uint32_t time) {
//     pio_sm_put(pio0, 0, time);
// }

int main()
{
    stdio_init_all();
    printf("ADC Example, measuring GPIO26\n");
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &dimmer_program);


    dimmer_program_init(pio, 0, offset, 4, 0);

    uint32_t freq = clock_get_hz(clk_sys);

    // triac propogation time 10 us
    uint32_t propogation_cycles = 10 * (freq / 1000000);

    pio_sm_put_blocking(pio, 0, freq / propogation_cycles);

    // half cycle time 10 ms
    uint32_t half_cycle = 10 * (freq / 1000) - 100 * propogation_cycles;

    // pio_sm_put_blocking(pio, 0, dimming_cycles);

    uint32_t dimming_percent = 0;

    signed int dimming_step = 1;

    int i = 1;

    while (1) {
        dimming_percent += dimming_step;

        if(dimming_percent == 100 || dimming_percent == 0) {
            dimming_step = -dimming_step;
        }

        uint32_t dim_time = (uint32_t)(half_cycle * acos(dimming_percent / 100.0) / M_PI * 2);

        pio_sm_put(pio, 0, dim_time);

        printf("Dimming: %d, zero to ignite time: %d\n", dimming_percent, dim_time);

        // pio_sm_put(pio, 0, i);

        // printf("Dimming: %d, zero to ignite time: %d\n", i, i);

        // i+=100;

        sleep_ms(50);
    }


}

