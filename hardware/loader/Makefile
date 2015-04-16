# lightcontrol - Control your 433MHz lights using an Arduino and some simple software.
# Copyright (C) 2015 Jack Wilsdon
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

DEVICE     = attiny85
CLOCK      = 8000000
PROGRAMMER = usbasp
OBJECTS    = main.o
FUSES      = -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m

AVRDUDE = avrdude -c $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Werror -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

.PHONY: all flash fuse install clean

all: main.hex

.c.o:
	$(COMPILE) -c $< -o $@

flash: all
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

install: flash fuse

clean:
	rm -f main.hex main.elf $(OBJECTS)

main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf
