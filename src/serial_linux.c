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

#ifdef __linux__

#include "serial.h"
#include "packet.h"

#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int fd = -1;

unsigned int linux_serial_connect(char *name) {
    fd = open(name, O_WRONLY | O_NOCTTY | O_SYNC);

    if (fd < 0) {
        return SERIAL_ERROR;
    }

    struct termios tty = {0};

    if (tcgetattr(fd, &tty) != 0) {
        close(fd);

        return SERIAL_ERROR;
    }

    if (cfsetspeed(&tty, B9600) != 0) {
        close(fd);

        return SERIAL_ERROR;
    }

    tty.c_cflag &= ~(CSIZE | CREAD | PARENB);
    tty.c_cflag |= (CS8 | CLOCAL);

    tty.c_oflag = 0;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        close(fd);

        return SERIAL_ERROR;
    }

    return SERIAL_SUCCESS;
}

unsigned int linux_serial_transmit(packet_t packet) {
    char bytes[] = { packet_to_binary(packet) };

    if (write(fd, bytes, 1) != 1) {
        close(fd);

        return SERIAL_ERROR;
    }

    return SERIAL_SUCCESS;
}

unsigned int linux_serial_close() {
    if (close(fd) != 0) {
        return SERIAL_ERROR;
    }

    return SERIAL_SUCCESS;
}

#endif
