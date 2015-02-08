#include "hardware/packet.h"
#include "serial.h"

int getvalue(char *text, char *name, int min, int max) {
    char *end;

    long result = strtol(text, &end, 10);

    if (*end != '\0' || result < min || result > max) {
        fprintf(stderr, "Invalid value for %s.\n", name);
        return -1;
    }

    return result;
}

int main(int argc, char *argv[]) {
    // 0: device
    // 1: group
    // 2: plug
    // 3: status

    if (argc != 5) {
        fprintf(stderr, "Usage: %s device group plug status\n", argv[0]);
        return 1;
    }

    char *device = argv[1];

    int group = getvalue(argv[2], "group", 1, 4);

    if (group == -1) {
        return 1;
    }

    int plug = getvalue(argv[3], "plug", 1, 4);

    if (plug == -1) {
        return 1;
    }

    int status = getvalue(argv[4], "status", 0, 1);

    if (status == -1) {
        return 1;
    }

    if (serial_connect(device) == SERIAL_ERROR) {
        fprintf(stderr, "Failed to connect to serial device \"%s\".\n", device);
        return 1;
    }

    struct Packet packet;

    packet.group = group - 1;
    packet.plug = plug - 1;
    packet.status = status;

    if (serial_transmit(packet) == SERIAL_ERROR) {
        fprintf(stderr, "Failed to send data to serial device \"%s\".\n", device);
        return 1;
    }

    serial_close();

    return 0;
}

