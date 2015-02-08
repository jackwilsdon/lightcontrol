#ifndef _SERIAL_WIN_H_
#define _SERIAL_WIN_H_

#include "packet.h"

unsigned int win_serial_connect(char device[]);
unsigned int win_serial_transmit(struct Packet packet);
unsigned int win_serial_close();

#endif
