CC     = gcc
CFLAGS = -Wall -Werror
DEPS   = serial.h hardware/packet.h
OBJ    = control.o serial.o packet.o

.PHONY: all clean hardware bin

all: clean control

bin/%.o: src/%.c | bin
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf bin $(OBJ)

control: $(addprefix bin/, $(OBJ)) | bin
	gcc -o bin/$@ $^ $(CFLAGS)

hardware:
	cd hardware && make all

bin:
	mkdir -p bin
