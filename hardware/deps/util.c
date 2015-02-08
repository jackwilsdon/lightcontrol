#include <util/delay.h>

void delay_ms(uint16_t ms) {
    for (ms /= 10; ms > 0; ms--) _delay_ms(10);
}

void delay_us(uint16_t us) {
    for (us /= 10; us > 0; us--) _delay_us(10);
}
