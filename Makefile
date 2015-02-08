CC     = gcc
CFLAGS = -Wall -Werror
DEPS   = serial.h hardware/packet.h
OBJ    = control.o serial.o hardware/packet.o

.PHONY: all clean

all: clean control

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf bin $(OBJ)

control: $(OBJ)
	mkdir bin
	gcc -o bin/$@ $^ $(CFLAGS)
