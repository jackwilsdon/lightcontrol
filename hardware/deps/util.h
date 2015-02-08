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
