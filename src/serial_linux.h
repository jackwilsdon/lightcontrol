#ifndef _SERIAL_LINUX_H_
#define _SERIAL_LINUX_H_

#include "packet.h"

unsigned int linux_serial_connect(char device[]);
unsigned int linux_serial_transmit(struct Packet packet);
unsigned int linux_serial_close();

#endif
