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
OBJ    = main.o serial_win.o serial_linux.o serial_debug.o packet.o
BINARY = control

.PHONY: all build debug clean install uninstall control test doc bin

all: build

build: control

debug: CFLAGS += -DDEBUG_SERIAL
debug: BINARY = control_debug
debug: control

bin/%.o: src/%.c | bin
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf bin

install: control
ifeq ($(OS), Windows_NT)
	$(error Not supported on Windows)
else
	install -m 755 bin/$(BINARY) /usr/local/bin
endif

uninstall:
ifeq ($(OS), Windows_NT)
	$(error Not supported on Windows)
else
	rm /usr/local/bin/$(BINARY)
endif

control: $(addprefix bin/, $(OBJ))
	gcc -o bin/$(BINARY) $^ $(CFLAGS)

test:
	make -C test build run

doc:
	doxygen Doxyfile

bin:
	mkdir -p bin
