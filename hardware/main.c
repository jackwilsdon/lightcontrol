#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "deps/util.h"
#include "deps/rcswitch/rcswitch.h"

#define PIN_RC PB2

#include "deps/rcswitch/softuart.h"
#include "packet.h"

int main(void) {
    // initialize serial
    softuart_init();

    // enable interrupts
    sei();

    // enable the rc switch
    rcswitch_enable(PIN_RC);

    while (1) {

        // if there is some data waiting for us
        if (softuart_kbhit()) {

            // parse the data
            struct Packet packet;

            binary_to_packet(&packet, softuart_getchar());

            // handle the packet
            if (packet.status) {
                rcswitch_switch_on(packet.group + 1, packet.plug + 1);
            } else {
                rcswitch_switch_off(packet.group + 1, packet.plug + 1);
            }
        }
    }

    return 0;
}
