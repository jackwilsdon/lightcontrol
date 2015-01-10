#include <stdio.h>
#include <string.h>
#include <math.h>

struct Packet {
    unsigned int status: 1;
    unsigned int group: 2;
    unsigned int plug: 2;
};

unsigned int packet_to_binary(struct Packet packet) {
    unsigned int binary = (packet.status << 7);
    binary |= ((packet.group & 0x3) << 2);
    binary |= (packet.plug  & 0x3);

    return binary & 0xFF;
}

void binary_to_packet(struct Packet *packet, unsigned int binary) {
    packet->status = (binary >> 7);
    packet->group = (binary >> 2) & 0x3;
    packet->plug = binary & 0x3;
}

void printBinary(int num, int digits) {
    int shift = digits - 1;
    int current = pow(2, shift);

    while (current > 0) {
        printf("%d", ((num & current) >> shift) & 1);

        shift--;
        current /= 2;
    }

    printf("\n");
}
