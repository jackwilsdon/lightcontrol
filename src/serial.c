#include "serial.h"
#include "packet.h"

#ifdef _WIN32

#include <windows.h>
#include <stdlib.h>

HANDLE serialHandle;
DCB serialParameters = {0};
COMMTIMEOUTS serialTimeouts = {0};

unsigned int serial_connect(char device[]) {
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

unsigned int serial_transmit(struct Packet packet) {
    char bytes[] = { packet_to_binary(packet) };

    DWORD bytes_written;

    if (!WriteFile(serialHandle, bytes, 1, &bytes_written, NULL)) {
        CloseHandle(serialHandle);

        return SERIAL_ERROR;
    }

    return SERIAL_SUCCESS;
}

unsigned int serial_close() {
    if (CloseHandle(serialHandle) == 0) {
        return SERIAL_ERROR;
    }

    return SERIAL_SUCCESS;
}

#elif __linux

#include <unistd.h>
#include <termios.h>

int fd = -1;

unsigned int serial_connect(char *name) {
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

unsigned int serial_transmit(struct Packet packet) {
    char bytes[] = { packet_to_binary(packet) };

    if (write(fd, bytes, 1) != 1) {
        close(fd);

        return SERIAL_ERROR;
    }

    return SERIAL_SUCCESS;
}

unsigned int serial_close() {
    if (close(fd) != 0) {
        return SERIAL_ERROR;
    }

    return SERIAL_SUCCESS;
}

#else
#error Operating System not supported!
#endif
