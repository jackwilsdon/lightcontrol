CC     = gcc
CFLAGS = -Wall -Werror
DEPS   = serial.h hardware/packet.h
OBJ    = control.o serial.o packet.o

.PHONY: all clean install hardware bin

all: clean control

bin/%.o: src/%.c | bin
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf bin $(OBJ)


install: control
ifeq ($(OS), Windows_NT)
	$(error "Install not supported on Windows")
else
	install -m 755 bin/control /usr/local/bin
endif

control: $(addprefix bin/, $(OBJ)) | bin
	gcc -o bin/$@ $^ $(CFLAGS)

hardware:
	cd hardware && make all

bin:
	mkdir -p bin
