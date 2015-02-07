#include "packet.h"

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
