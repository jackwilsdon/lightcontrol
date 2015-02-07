#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "hardware/packet.h"

#define SERIAL_SUCCESS 1
#define SERIAL_ERROR !SERIAL_SUCCESS

unsigned int serial_connect(char device[]);
unsigned int serial_transmit(struct Packet packet);
unsigned int serial_close();

#endif
