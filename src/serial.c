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

#ifdef _WIN32
    #include "serial_win.h"
#elif defined(__linux__)
    #include "serial_linux.h"
#else
#error Operating System not supported!
#endif

unsigned int serial_connect(char device[]) {
#ifdef _WIN32
    return win_serial_connect(device);
#elif defined(__linux__)
    return linux_serial_connect(device);
#endif
}

unsigned int serial_transmit(struct Packet packet) {
#ifdef _WIN32
    return win_serial_transmit(packet);
#elif defined(__linux__)
    return linux_serial_transmit(packet);
#endif
}

unsigned int serial_close() {
#ifdef _WIN32
    return win_serial_close();
#elif defined(__linux__)
    return linux_serial_close();
#endif
}
