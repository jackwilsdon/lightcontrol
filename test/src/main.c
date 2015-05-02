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
	packet_t sourcePacket;
	packet_t destPacket;

	unsigned int binaryData;
	int group, plug, status;

	for (group = 0; group < 4; group++) {
		sourcePacket.group = group;

		for (plug = 0; plug < 4; plug++) {
			sourcePacket.plug = plug;

			for (status = 0; status < 2; status++) {
				sourcePacket.status = status;

				binaryData = packet_to_binary(sourcePacket);
				binary_to_packet(&destPacket, binaryData);

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
