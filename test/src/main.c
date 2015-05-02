#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../../src/packet.h"

/**
 * @brief Assert that the two given packets are equal.
 *
 * The function calls assert_true to assert that the values of the fields in
 * the two packets are the same.
 *
 * @param[in] a The first packet to compare.
 * @param[in] b The packet to compare against the first one.
 */
static void assert_packet_equal(packet_t a, packet_t b) {
	assert_true(a.status == b.status);
	assert_true(a.group == b.group);
	assert_true(a.plug == b.plug);
}

static void test_packet_conversion(void **state) {
	packet_t sourcePacket; // The original packet
	packet_t destPacket;   // The "cloned" packet (original->binary->this)

	unsigned int binaryData; // The binary data (original->this->cloned)
	int group, plug, status; // The group, plug and status for the current test

	// Iterate all possible groups
	for (group = 0; group < 4; group++) {
		sourcePacket.group = group; // Update the source group

		// Iterate all possible plugs
		for (plug = 0; plug < 4; plug++) {
			sourcePacket.plug = plug; // Update the source plug

			// Iterate all possible statuses
			for (status = 0; status < 2; status++) {
				sourcePacket.status = status; // Update the source status

				// Convert the current packet to binary and back again
				binaryData = packet_to_binary(sourcePacket);
				binary_to_packet(&destPacket, binaryData);

				// Compare the "cloned" packet to the source packet
				assert_packet_equal(sourcePacket, destPacket);
			}
		}
	}
}

int main(void)
{
    const struct CMUnitTest tests[] =
    {
    	cmocka_unit_test(test_packet_conversion)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
