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

SRCDIR = src
BINDIR = bin
OBJDIR = obj
DEPDIR = deps

OBJ    = main.o serial_win.o serial_linux.o serial_debug.o packet.o
BINARY = control

BINFILE = $(addprefix $(BINDIR)/, $(BINARY))

.PHONY: all build debug install uninstall clean test

all: build

build: $(BINFILE)

debug: CFLAGS += -DDEBUG_SERIAL
debug: build

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

clean:
	rm -rf $(BINDIR) $(OBJDIR) $(DEPDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(BINDIR) $(OBJDIR) $(DEPDIR)
	$(CC) -c $(CFLAGS) -MMD -MP -MF $(addprefix $(DEPDIR)/, $(notdir $(patsubst %.c,%.d,$<))) -o $(addprefix $(OBJDIR)/, $(notdir $@)) $<

$(BINFILE): $(addprefix $(OBJDIR)/, $(OBJ)) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OBJDIR)/, $(notdir $^))

$(BINDIR) $(OBJDIR) $(DEPDIR):
	@mkdir -p $@

test:
	make -C test build run
