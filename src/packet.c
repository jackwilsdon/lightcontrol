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
