#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "softuart.h"

#define PIN_LED PB3

#define DELAY_MS 100

#define DIGITAL_WRITE_H(port, pin) port |= (1 << pin)
#define DIGITAL_WRITE_L(port, pin) port &= ~(1 << pin)

#define ESC \x27

void long_delay_ms(uint16_t ms) {
    for (ms /= 10; ms > 0; ms--) _delay_ms(10);
}

// program entry point
int main(void) {
    softuart_init();

    // enable interrupts
    sei();

    // clear terminal
    softuart_puts("\x1B\x63");

    DDRB |= (1 << PIN_LED);

    DIGITAL_WRITE_L(PORTB, PIN_LED);

    while (1) {

        if (softuart_kbhit()) {
            softuart_getchar();

            DIGITAL_WRITE_H(PORTB, PIN_LED);

            long_delay_ms(200);

            DIGITAL_WRITE_L(PORTB, PIN_LED);

            long_delay_ms(200);
        }

        long_delay_ms(DELAY_MS);
    }

    return 0;
}
