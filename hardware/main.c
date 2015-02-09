/*
  lightcontrol - Control your 433MHz lights using an Arduino and some simple software.
  Copyright (C) 2015 Jack Wilsdon

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Affero General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Affero General Public License for more details.

  You should have received a copy of the GNU Affero General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "deps/rcswitch/rcswitch.h"
#include "deps/softuart/softuart.h"
#include "packet.h"

#define PIN_RC PB2

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
