/*
  lightcontrol - Control your 433MHz lights using an Arduino and some simple software.
  Copyright (C) 2015 Jack Wilsdon

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Affero General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Affero General Public License for more details.

  You should have received a copy of the GNU Affero General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>

#include "packet.h"
#include "serial.h"

static char *filename = "Unknown";

#define RESULT_ERROR 0
#define RESULT_ARG_ERROR 1
#define RESULT_SUCCESS 2

int getvalue(char *text, char *name, int min, int max) {
    char *end;

    long result = strtol(text, &end, 10);

    if (*end != '\0' || result < min || result > max) {
        fprintf(stderr, "Invalid value for %s.\n", name);
        return -1;
    }

    return result;
}

void print_usage() {
    fprintf(stderr, "Usage: %s device group plug status", filename);
}

int run(int argc, char *argv[]) {
    // 0: device
    // 1: group
    // 2: plug
    // 3: status

     if (argc != 5) {
        return RESULT_ARG_ERROR;
    }

    char *device = argv[1];

    int group = getvalue(argv[2], "group", 1, 4);

    if (group == -1) {
        return RESULT_ARG_ERROR;
    }

    int plug = getvalue(argv[3], "plug", 1, 4);

    if (plug == -1) {
        return RESULT_ARG_ERROR;
    }

    int status = getvalue(argv[4], "status", 0, 1);

    if (status == -1) {
        return RESULT_ARG_ERROR;
    }

    if (serial_connect(device) == SERIAL_ERROR) {
        fprintf(stderr, "Failed to connect to serial device \"%s\".\n", device);
        return RESULT_ERROR;
    }

    packet_t packet = { status, group - 1, plug - 1 };

    if (serial_transmit(packet) == SERIAL_ERROR) {
        fprintf(stderr, "Failed to send data to serial device \"%s\".\n", device);
        return RESULT_ERROR;
    }

    serial_close();

    return RESULT_SUCCESS;
}

int main(int argc, char *argv[]) {
    filename = basename(argv[0]);

    if (argc != 5) {
        print_usage();
        return 1;
    }

    int result = run(argc, argv);

    switch (result) {
        case RESULT_ERROR:
            return EXIT_FAILURE;
        case RESULT_ARG_ERROR:
            print_usage();
            return EXIT_FAILURE;
        case RESULT_SUCCESS:
            return EXIT_SUCCESS;
    }

    return 0;
}

