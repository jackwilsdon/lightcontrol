#ifdef _WIN32

#include "serial.h"
#include "packet.h"

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

unsigned int win_serial_transmit(struct Packet packet) {
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
