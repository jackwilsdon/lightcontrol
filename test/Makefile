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
CFLAGS = -Wall -Werror -lcmocka
OBJ    = src/main.o ../src/packet.o ../src/dynarray.o
BINARY = test

.PHONY: all build clean test run bin

all: build

build: test

$(OBJ): | bin
	$(CC) -c -o $(addprefix bin/, $(notdir $@)) $(@:.o=.c) $(CFLAGS)

clean:
	rm -rf bin

test: $(OBJ) | bin
	gcc -o bin/$(BINARY) $(addprefix bin/, $(notdir $^)) $(CFLAGS)

run:
	bin/$(BINARY)

bin:
	mkdir -p bin
