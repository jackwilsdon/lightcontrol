CC     = gcc
CGLAGS = -Wall -Werror
DEPS   = serial.h hardware/packet.h
OBJ    = control.o serial.o hardware/packet.o

.PHONY: all clean

all: clean control

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf control $(OBJ)

control: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
