CC     = gcc
CGLAGS = -Wall -Werror
DEPS   = serial.h hardware/packet.h
OBJ    = control.o serial.o hardware/packet.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(OBJ)

control: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
