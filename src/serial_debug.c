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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "serial.h"
#include "packet.h"

const char *debug_prefix = "[Debug] ";

void debug_printf(const char *format, ...) {
    char *debug_format = malloc(strlen(debug_prefix) + strlen(format));

    strcpy(debug_format, debug_prefix);
    strcat(debug_format, format);

    va_list args;
    va_start(args,format);
    vprintf(debug_format, args);
    va_end(args);
}

unsigned int debug_serial_connect(char device[]) {
    debug_printf("Connected to device `%s'\n", device);

    return SERIAL_SUCCESS;
}

unsigned int debug_serial_transmit(packet_t packet) {
    debug_printf("Transmitting (Status: %d, Group: %d [%d], Plug: %d [%d])\n",
        packet.status,
        packet.group + 1,
        packet.group,
        packet.plug + 1,
        packet.plug);

    return SERIAL_SUCCESS;
}

unsigned int debug_serial_close() {
    debug_printf("Closed device\n");

    return SERIAL_SUCCESS;
}
