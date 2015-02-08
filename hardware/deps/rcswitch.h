/*
  RCSwitch - Arduino libary for remote control outlet switches
  Copyright (c) 2011 Suat Özgür.  All right reserved.

  Contributors:
  - Andre Koehler / info(at)tomate-online(dot)de
  - Gordeev Andrey Vladimirovich / gordeev(at)openpyro(dot)com
  - Skineffect / http://forum.ardumote.com/viewtopic.php?f=2&t=46
  - Dominik Fischer / dom_fischer(at)web(dot)de
  - Frank Oltmanns / <first name>.<last name>(at)gmail(dot)com

  Project home: http://code.google.com/p/rc-switch/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef _RCSWITCH_H_
#define _RCSWITCH_H_

// Number of maximum High/Low changes per packet.
// We can handle up to (unsigned long) => 32 bit * 2 H/L changes per bit + 2 for sync
#define RCSWITCH_MAX_CHANGES 67

#define RCSWITCH_ON 1
#define RCSWITCH_OFF 0

void rcswitch_enable(int pin);
void rcswitch_disable();
void rcswitch_switch_on(int addressCode, int channelCode);
void rcswitch_switch_off(int addressCode, int channelCode);
char* rcswitch_get_code_word_b(int addressCode, int channelCode, unsigned int status);
void rcswitch_send_tri_state(char* codeWord);
void rcswitch_transmit(int highPulses, int lowPulses);
void rcswitch_send0();
void rcswitch_send1();
void rcswitch_sendT0();
void rcswitch_sendT1();
void rcswitch_sendTF();
void rcswitch_send_sync();

#endif
