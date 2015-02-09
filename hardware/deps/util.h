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

#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdint.h>

#define SET_BIT(reg, bit) reg |= (1 << bit)
#define UNSET_BIT(reg, bit) reg &= ~(1 << bit)

#define PIN_MODE_IN(port, pin) UNSET_BIT(port, pin)
#define PIN_MODE_OUT(port, pin) SET_BIT(port, pin)

#define DIGITAL_WRITE_H(port, pin) SET_BIT(port, pin)
#define DIGITAL_WRITE_L(port, pin) UNSET_BIT(port, pin)

void delay_ms(uint16_t ms);
void delay_us(uint16_t us);

#endif
