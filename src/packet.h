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

/**
 * @defgroup packet Control Packets
 * @brief Light control packets.
 * @{
 */

/**
 * @brief Represents a control packet.
 */
struct packet {

    /**
     * @brief The status for the plug.
     */
    unsigned int status: 1;

    /**
     * @brief The group of the plug.
     */
    unsigned int group: 2;

    /**
     * @brief The plug to control.
     */
    unsigned int plug: 2;
};

/**
 * @brief Represents a control packet.
 */
typedef struct packet packet_t;

/**
 * @brief Converts a @ref packet to binary.
 *
 * See @ref md_FORMAT for more information.
 *
 * @param[in] packet The packet to convert.
 * @return The binary value of the packet data.
 */
unsigned int packet_to_binary(packet_t packet);

/**
 * @brief Converts binary to a @ref packet.
 *
 * See @ref md_FORMAT for more information.
 *
 * @param[out] packet The packet value of the binary data.
 * @param[in] binary The binary value of the packet data.
 */
void binary_to_packet(packet_t *packet, unsigned int binary);

/**
 * @}
 */

#endif
