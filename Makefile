CC     = gcc
CFLAGS = -Wall -Werror
DEPS   = serial.h hardware/packet.h
OBJ    = control.o serial.o packet.o

.PHONY: all clean

all: clean control

bin/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf bin $(OBJ)

control: $(addprefix bin/, $(OBJ))
	mkdir bin
	gcc -o bin/$@ $^ $(CFLAGS)
