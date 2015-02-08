#ifndef _PACKET_H_
#define _PACKET_H_

#include <stdio.h>
#include <string.h>
#include <math.h>

struct Packet {
    unsigned int status: 1;
    unsigned int group: 2;
    unsigned int plug: 2;
};

unsigned int packet_to_binary(struct Packet packet);
void binary_to_packet(struct Packet *packet, unsigned int binary);

#endif
