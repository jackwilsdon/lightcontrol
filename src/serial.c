#ifdef _WIN32
    #include "serial_win.h"
#elif defined(__linux__)
    #include "serial_linux.h"
#else
#error Operating System not supported!
#endif

unsigned int serial_connect(char device[]) {
#ifdef _WIN32
    return win_serial_connect(device);
#elif defined(__linux__)
    return linux_serial_connect(device);
#endif
}

unsigned int serial_transmit(struct Packet packet) {
#ifdef _WIN32
    return win_serial_transmit(packet);
#elif defined(__linux__)
    return linux_serial_transmit(packet);
#endif
}

unsigned int serial_close() {
#ifdef _WIN32
    return win_serial_close();
#elif defined(__linux__)
    return linux_serial_close();
#endif
}
