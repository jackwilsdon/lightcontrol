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

CC     = gcc
CFLAGS = -Wall -Werror
DEPS   = serial.h hardware/packet.h
OBJ    = main.o serial.o serial_win.o serial_linux.o packet.o

.PHONY: all clean install uninstall hardware bin

all: control

bin/%.o: src/%.c | bin
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf bin $(OBJ)

install: control
ifeq ($(OS), Windows_NT)
	$(error Not supported on Windows)
else
	install -m 755 bin/control /usr/local/bin
endif

uninstall:
ifeq ($(OS), Windows_NT)
	$(error Not supported on Windows)
else
	rm /usr/local/bin/control
endif

control: $(addprefix bin/, $(OBJ)) | bin
	gcc -o bin/$@ $^ $(CFLAGS)

hardware:
	cd hardware && make all

bin:
	mkdir -p bin
