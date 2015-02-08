/*
  RCSwitch - Arduino libary for remote control outlet switches
  Copyright (c) 2011 Suat Özgür.  All right reserved.

  Contributors:
  - Andre Koehler / info(at)tomate-online(dot)de
  - Gordeev Andrey Vladimirovich / gordeev(at)openpyro(dot)com
  - Skineffect / http://forum.ardumote.com/viewtopic.php?f=2&t=46
  - Dominik Fischer / dom_fischer(at)web(dot)de
  - Frank Oltmanns / <first name>.<last name>(at)gmail(dot)com
  - Andreas Steinel / A.<lastname>(at)gmail(dot)com

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

#include <avr/io.h>

#include "rcswitch.h"
#include "util.h"

int transmitterPin = -1;
int pulseLength = 350;
int repeatTransmit = 10;

unsigned int timings[RCSWITCH_MAX_CHANGES];

void rcswitch_enable(int pin) {
  transmitterPin = pin;
  PIN_MODE_OUT(DDRB, transmitterPin);
}

void rcswitch_disable() {
  transmitterPin = -1;
}

void rcswitch_switch_on(int addressCode, int channelCode) {
  rcswitch_send_tri_state(rcswitch_get_code_word_b(addressCode, channelCode, RCSWITCH_ON));
}

void rcswitch_switch_off(int addressCode, int channelCode) {
  rcswitch_send_tri_state(rcswitch_get_code_word_b(addressCode, channelCode, RCSWITCH_OFF));
}

char* rcswitch_get_code_word_b(int addressCode, int channelCode, unsigned int status) {
   int i = 0;
   int returnPos = 0;
   static char sReturn[13];

   char* code[5] = { "FFFF", "0FFF", "F0FF", "FF0F", "FFF0" };
   if (addressCode < 1 || addressCode > 4 || channelCode < 1 || channelCode > 4) {
    return '\0';
   }

   for (i = 0; i < 4; i++) {
     sReturn[returnPos++] = code[addressCode][i];
   }

   for (i = 0; i < 4; i++) {
     sReturn[returnPos++] = code[channelCode][i];
   }

   sReturn[returnPos++] = 'F';
   sReturn[returnPos++] = 'F';
   sReturn[returnPos++] = 'F';

   if (status) {
      sReturn[returnPos++] = 'F';
   } else {
      sReturn[returnPos++] = '0';
   }

   sReturn[returnPos] = '\0';

   return sReturn;
}

void rcswitch_send_tri_state(char* codeWord) {
    int repeat = 0;

  for (repeat = 0; repeat < repeatTransmit; repeat++) {
    int i = 0;
    while (codeWord[i] != '\0') {
      switch(codeWord[i]) {
        case '0':
          rcswitch_sendT0();
        break;
        case 'F':
          rcswitch_sendTF();
        break;
        case '1':
          rcswitch_sendT1();
        break;
      }
      i++;
    }
    rcswitch_send_sync();
  }
}

void rcswitch_transmit(int highPulses, int lowPulses) {
    if (transmitterPin != -1) {
        DIGITAL_WRITE_H(PORTB, transmitterPin);
        delay_us(pulseLength * highPulses);
        DIGITAL_WRITE_L(PORTB, transmitterPin);
        delay_us(pulseLength * lowPulses);
    }
}

/**
 * Sends a "0" Bit
 *                       _
 * Waveform Protocol 1: | |___
 */
void rcswitch_send0() {
    rcswitch_transmit(1, 3);
}

/**
 * Sends a "1" Bit
 *                       ___
 * Waveform Protocol 1: |   |_
 */
void rcswitch_send1() {
    rcswitch_transmit(3, 1);
}


/**
 * Sends a Tri-State "0" Bit
 *            _     _
 * Waveform: | |___| |___
 */
void rcswitch_sendT0() {
    rcswitch_send0();
    rcswitch_send0();
}

/**
 * Sends a Tri-State "1" Bit
 *            ___   ___
 * Waveform: |   |_|   |_
 */
void rcswitch_sendT1() {
    rcswitch_send1();
    rcswitch_send1();
}

/**
 * Sends a Tri-State "F" Bit
 *            _     ___
 * Waveform: | |___|   |_
 */
void rcswitch_sendTF() {
    rcswitch_send0();
    rcswitch_send1();
}

/**
 * Sends a "Sync" Bit
 *                       _
 * Waveform Protocol 1: | |_______________________________
 */
void rcswitch_send_sync() {
    rcswitch_transmit(1, 31);
}
