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

#include <getopt.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "packet.h"
#include "serial.h"

#define BUILD_VERSION "0.0.4"

// The default serial device
const char *default_device = "/dev/ttyUSB0";

// The name of the current file
static char *filename = "Unknown";

int getvalue(char *text, int *value) {
    // The first character after the number
    char *end;

    // Retrieve the numeric value of the text
    long result = strtol(text, &end, 10);

    // Ensure that there are no characters after the number
    if (*end != '\0') {
        *value = 0;

        // Return a failure
        return -1;
    }

    // Return the number value of the text
    *value = result;

    // Return a success
    return 0;
}

// Print usage for this command
void print_usage() {
    printf("Usage: %s [OPTIONS] [PLUG] GROUP STATUS\n", filename);
    printf("  -d, --device device       device to control\n");
    printf("                              defaults to %s\n", default_device);
    printf("  -h, --help                display this help and exit\n");
    printf("\n");
    printf("lightcontrol v%s\n", BUILD_VERSION);
}

int main(int argc, char *argv[]) {

    // Current device to control
    char *device = malloc(strlen(default_device) + 1);

    // Copy default device
    strcpy(device, default_device);

    // Current option for getopt
    int c;

    // Set options for getopt
    const char *short_options = "d:h";
    static struct option long_options[] = {
        { "device", optional_argument, NULL, 'd' },
        { "help",   no_argument,       NULL, 'h' }
    };

    // Disable getopt errors
    opterr = 0;

    // Retrieve the current filename
    filename = basename(argv[0]);

    // Iterate the provided arguments
    while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (c) {
            case 'd': // Device option
                device = optarg;
                break;

            case 'h': // Help option
                print_usage();
                return EXIT_SUCCESS;

            default: // Error

                // Check whether the error is a device error or not
                switch (optopt) {
                    case 'd': // Device error

                        // Output the error
                        fprintf(stderr, "%s: invalid device\n", filename);
                        break;

                    default: // Generic error

                        // Output the error
                        fprintf(stderr, "%s: invalid option -- %c\n", filename, optopt);
                        fprintf(stderr, "Try `%s --help' for more information.\n", filename);
                        break;
                }

                // Exit with an error
                return EXIT_FAILURE;
        }
    }

    // Current argument and start index
    int index;
    int start = optind;

    // Command information
    int group = -1;
    int plug = -1;
    int status = -1;

    int error = -1;

    // Iterate arguments
    for (index = start; index < argc; index++) {

        // Current argument
        char *arg = argv[start + (argc - index - 1)];

        // Get value of current argument
        int value = 0;
        int result = getvalue(arg, &value);

        int current = index - start;

        switch (current) {
            case 0: // Status
                if (!result && value >= 0 && value <= 1) {
                    status = value;
                } else {
                    error = current;
                }
                break;

            case 1: // Group
                if (!result && value >= 1 && value <= 4) {
                    group = value;
                } else {
                    error = current;
                }
                break;

            case 2: // Plug
                if (!result && value >= 1 && value <= 4) {
                    plug = value;
                } else {
                    error = current;
                }
                break;

            default: // Other
                error = current;
                break;
        }
    }

    // If no error has occurred and the group is invalid
    if (error == -1 && group == -1) {

        // There is an error in the group
        error = 1;
    }

    // Handle any errors
    switch (error) {
        case -1: // No error
            break;

        case 0: // Status
            fprintf(stderr, "%s: invalid status (must be 0 or 1)\n", filename);
            fprintf(stderr, "Try `%s --help' for more information.\n", filename);
            break;

        case 1: // Group
            fprintf(stderr, "%s: invalid group (must be 1 to 4)\n", filename);
            fprintf(stderr, "Try `%s --help' for more information.\n", filename);
            break;

        case 2: // Plug
            fprintf(stderr, "%s: invalid plug (must be 1 to 4)\n", filename);
            fprintf(stderr, "Try `%s --help' for more information.\n", filename);
            break;

        default: // Other
            fprintf(stderr, "%s: invalid usage\n", filename);
            fprintf(stderr, "Try `%s --help' for more information.\n", filename);
            break;
    }

    // No error
    if (error == -1) {

        // Try to connect to the serial device
        if (serial_connect(device) == SERIAL_ERROR) {
            fprintf(stderr, "%s: failed to connect to serial device `%s'\n", filename, device);

            // Free the device and exit
            free(device);
            return EXIT_FAILURE;
        }

        // Create a packet to transmit
        packet_t packet;

        // Fill the packet with the provided information
        packet.status = status;
        packet.group = group - 1;

        int start; // The start of the plugs to be changed
        int end;   // The end of the plugs to be changed
        int index; // The current plug

        // If no plugs were provided, change all plugs
        if (plug == -1) {
            start = 0;
            end = 4;
        } else { // Otherwise only change the provided plug
            start = plug - 1;
            end = plug;
        }

        // Iterate the plugs
        for (index = start; index < end; index++) {

            // Update the packet with the new plug
            packet.plug = index;

            // Transmit the packet
            if (serial_transmit(packet) == SERIAL_ERROR) {
                fprintf(stderr, "%s: failed to send data to serial device `%s'\n", filename, device);

                // Free the device and exit
                free(device);
                return EXIT_FAILURE;
            }
        }

        // Close the serial device
        serial_close();
    } else { // There was an error
        return EXIT_FAILURE;
    }

    // Free the device
    free(device);

    // Exit with a success
    return EXIT_SUCCESS;
}
