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

#ifndef _PACKET_H_
#define _PACKET_H_

struct Packet {
    unsigned int status: 1;
    unsigned int group: 2;
    unsigned int plug: 2;
};

typedef struct Packet packet_t;

unsigned int packet_to_binary(packet_t packet);
void binary_to_packet(packet_t *packet, unsigned int binary);

#endif
