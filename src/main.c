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

#define BUILD_VERSION "0.0.2"

#define RESULT_ERROR 0
#define RESULT_ARG_ERROR 1
#define RESULT_SUCCESS 2

// The name of the current file
static char *filename = "Unknown";

// Convert a string into a number
//  text - The string to convert
//  name - The name of the value being converted. This is used when
//         printing errors.
//   min - The minimum value for the number returned. An error is
//         thrown if the number found is less than this.
//   max - The maximum value for the number returned. An error is
//         thrown if the number found is greater than this.
// Returns: The numeric value of `text` if valid, otherwise -1
int getvalue(char *text, char *name, int min, int max) {
    // The first character after the number
    char *end;

    // Retrieve the numeric value of the text
    long result = strtol(text, &end, 10);

    // Ensure that there are no characters after the number
    // and that the number is in the range provided
    if (*end != '\0' || result < min || result > max) {
        fprintf(stderr, "Invalid value for %s.\n", name);
        return -1;
    }

    // Return the number value of the text
    return result;
}

// Print usage for this command
void print_usage() {
    fprintf(stderr, "Usage: %s device group plug status\n", filename);
    fprintf(stdout, "lightcontrol v%s\n", BUILD_VERSION);
}

// Run the main program
//  argc - The number of arguments provided to the program
//  argv - The arguments for the program. Accepted in the format
//          [0] Current filename (not used)
//          [1] Device
//          [2] Group
//          [3] Plug
//          [4] Status
int run(int argc, char *argv[]) {

    // Ensure 5 arguments have been provided
    if (argc != 5) {
        return RESULT_ARG_ERROR;
    }

    // Retrieve the device from the arguments
    char *device = argv[1];

    // Retrieve the group from the arguments
    int group = getvalue(argv[2], "group", 1, 4);

    // If the group is invalid, return an error
    if (group == -1) {
        return RESULT_ARG_ERROR;
    }

    // Retrieve the plug from the arguments
    int plug = getvalue(argv[3], "plug", 1, 4);

    // If the plug is invalid, return an error
    if (plug == -1) {
        return RESULT_ARG_ERROR;
    }

    // Retrieve the status from the arguments
    int status = getvalue(argv[4], "status", 0, 1);

    // If the status is invalid, return an error
    if (status == -1) {
        return RESULT_ARG_ERROR;
    }

    // Try and connect to the serial device
    if (serial_connect(device) == SERIAL_ERROR) {
        fprintf(stderr, "Failed to connect to serial device \"%s\".\n", device);
        return RESULT_ERROR;
    }

    // Create a packet from the provided information
    packet_t packet = { status, group - 1, plug - 1 };

    // Transmit the packet
    if (serial_transmit(packet) == SERIAL_ERROR) {
        fprintf(stderr, "Failed to send data to serial device \"%s\".\n", device);
        return RESULT_ERROR;
    }

    // Close the serial port
    serial_close();

    return RESULT_SUCCESS;
}

// Main entry point for the program
int main(int argc, char *argv[]) {

    // Retrieve the current filename
    filename = basename(argv[0]);

    // Run the main program
    int result = run(argc, argv);

    // If an error occurred then return a failure status
    // If an argument error occurred, output usage and then return a failure status
    switch (result) {
        case RESULT_ARG_ERROR: // Falls through to RESULT_ERROR and returns a failure status
            print_usage();
        case RESULT_ERROR:
            return EXIT_FAILURE;
    }

    // Return a success status if no errors occurred
    return EXIT_SUCCESS;
}

