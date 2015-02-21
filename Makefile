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
