#include "hardware/packet.h"
#include "serial.h"

void btoa(int num, char *buf, int digits) {
    int shift = digits - 1;
    int current = pow(2, shift);

    char digit[2];

    while (current > 0) {
        sprintf(digit, "%d", ((num & current) >> shift) & 1);
        strncat(buf, digit, 1);

        shift--;
        current /= 2;
    }

    strcat(buf, "\0");
}

int main(int argc, char *argv[]) {
    // 0: device
    // 1: group
    // 2: plug
    // 3: status

    char device[] = "\\\\.\\\\COM5";

    if (serial_connect(device) == SERIAL_ERROR) {
        printf("Failed to connect to serial device \"%s\"\n", device);
        return 1;
    }

    struct Packet packet = { 0, 0, 0 };

    if (serial_transmit(packet) == SERIAL_ERROR) {
        printf("Failed to send data to serial device \"%s\"\n", device);
        return 1;
    }

    serial_close(device);

    return 0;
}

