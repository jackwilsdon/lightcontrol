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

#include "serial.h"
#include "packet/packet.h"

#include <windows.h>
#include <stdlib.h>

HANDLE serialHandle;
DCB serialParameters = {0};
COMMTIMEOUTS serialTimeouts = {0};

unsigned int win_serial_connect(char device[]) {
    serialHandle = CreateFile(device, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (serialHandle == INVALID_HANDLE_VALUE) {
        return SERIAL_ERROR;
    }

    serialParameters.DCBlength = sizeof(serialParameters);

    if (GetCommState(serialHandle, &serialParameters) == 0) {
        CloseHandle(serialHandle);

        return SERIAL_ERROR;
    }

    serialParameters.BaudRate = CBR_9600;
    serialParameters.ByteSize = 8;
    serialParameters.StopBits = ONESTOPBIT;
    serialParameters.Parity = NOPARITY;

    if (SetCommState(serialHandle, &serialParameters) == 0) {
        CloseHandle(serialHandle);

        return SERIAL_ERROR;
    }

    serialTimeouts.ReadIntervalTimeout = 50;
    serialTimeouts.ReadTotalTimeoutMultiplier = 10;
    serialTimeouts.ReadTotalTimeoutConstant = 50;
    serialTimeouts.WriteTotalTimeoutMultiplier = 10;
    serialTimeouts.WriteTotalTimeoutConstant = 50;

    if (SetCommTimeouts(serialHandle, &serialTimeouts) == 0) {
        CloseHandle(serialHandle);

        return SERIAL_ERROR;
    }

    return SERIAL_SUCCESS;
}

unsigned int win_serial_transmit(packet_t packet) {
    char bytes[] = { packet_to_binary(packet) };

    DWORD bytes_written;

    if (!WriteFile(serialHandle, bytes, 1, &bytes_written, NULL)) {
        CloseHandle(serialHandle);

        return SERIAL_ERROR;
    }

    return SERIAL_SUCCESS;
}

unsigned int win_serial_close() {
    if (CloseHandle(serialHandle) == 0) {
        return SERIAL_ERROR;
    }

    return SERIAL_SUCCESS;
}

#endif
