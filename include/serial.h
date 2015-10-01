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

#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "packet/packet.h"

#define SERIAL_SUCCESS 1
#define SERIAL_ERROR (!SERIAL_SUCCESS)

#ifdef DEBUG_SERIAL
    #include "serial_debug.h"

    #define serial_connect debug_serial_connect
    #define serial_transmit debug_serial_transmit
    #define serial_close debug_serial_close
#elif defined(_WIN32)
    #include "serial_win.h"

    #define serial_connect win_serial_connect
    #define serial_transmit win_serial_transmit
    #define serial_close win_serial_close
#elif defined(__linux__) || defined(__APPLE__)
    #include "serial_linux.h"

    #define serial_connect linux_serial_connect
    #define serial_transmit linux_serial_transmit
    #define serial_close linux_serial_close
#else
#error Operating System not supported!
#endif

#endif
