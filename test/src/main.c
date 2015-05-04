#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>

#include "../../src/packet.h"
#include "../../src/dynarray.h"
#include "../../src/keyvalue.h"

#define TEST_DYNARRAY(name) cmocka_unit_test_setup_teardown(name, setup_dynarray, teardown_dynarray)
#define TEST_KEYVALUE(name) cmocka_unit_test_setup_teardown(name, setup_keyvalue, teardown_keyvalue)

/**
 * @brief Assert that the two given packets are equal.
 *
 * The function calls assert_true to assert that the values of the fields in
 * the two packets are the same.
 *
 * @param[in] a The first packet to compare.
 * @param[in] b The packet to compare against the first one.
 *
 * @see assert_true()
 */
static void assert_packet_equal(packet_t a, packet_t b) {
	assert_true(a.status == b.status);
	assert_true(a.group == b.group);
	assert_true(a.plug == b.plug);
}

/**
 * @brief Test the conversion from packet to binary and back again.
 *
 * The function iterates all possible group, plug and status combinations and
 * creates binary data from them using packet_to_binary. It then converts it
 * back to a packet_t before comparing it with the original packet using
 * assert_packet_equal.
 *
 * @param[in] state The current state. Unused by this method.
 *
 * @see packet_to_binary()
 * @see binary_to_packet()
 * @see assert_packet_equal()
 */
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

static int setup_dynarray(void **state) {
	dynarray_t *array = malloc(sizeof(dynarray_t));

	assert_true(dynarray_init(array, 8) == DYNARRAY_SUCCESS);

	*state = array;

	return 0;
}

static int teardown_dynarray(void **state) {
	dynarray_free(*state);
	free(*state);

	return 0;
}

static void test_dynarray_init(void **state) {
	dynarray_t *array = *state;

	assert_int_equal(array->initial_capacity, array->capacity);
	assert_int_equal(array->initial_capacity, 8);
	assert_int_equal(array->size, 0);
}

static void test_dynarray_size(void **state) {
	dynarray_t *array = *state;

	int size;

	assert_true(dynarray_size(array, &size) == DYNARRAY_SUCCESS);
	assert_int_equal(size, 0);

	array->size = 2;

	assert_true(dynarray_size(array, &size) == DYNARRAY_SUCCESS);
	assert_int_equal(size, 2);
}

static void test_dynarray_add(void **state) {
	dynarray_t *array = *state;

	int value = 123;

	assert_true(dynarray_add(array, &value) == DYNARRAY_SUCCESS);
	assert_int_equal(array->size, 1);
	assert_int_equal(array->data[0], &value);
}

static void test_dynarray_resize(void **state) {
	dynarray_t *array = *state;

	int index;
	int value = 123;

	for (index = 0; index < array->initial_capacity; index++) {
		assert_true(dynarray_add(array, &value) == DYNARRAY_SUCCESS);
	}

	assert_int_equal(array->capacity, array->initial_capacity);
	assert_int_equal(array->size, array->capacity);

	for (index = 0; index < array->initial_capacity; index++) {
		assert_true(dynarray_add(array, &value) == DYNARRAY_SUCCESS);
	}

	assert_int_equal(array->capacity, array->initial_capacity * 2);
	assert_int_equal(array->size, array->capacity);
}

static void test_dynarray_set(void **state) {
	dynarray_t *array = *state;

	int value = 123;

	assert_true(dynarray_add(array, &value) == DYNARRAY_SUCCESS);
	assert_int_equal(array->data[0], &value);

	int new_value = 1234;

	assert_true(dynarray_set(array, 0, &new_value) == DYNARRAY_SUCCESS);
	assert_int_equal(array->data[0], &new_value);
}

static void test_dynarray_get(void **state) {
	dynarray_t *array = *state;

	int value = 123;
	int *retrieved_value;

	assert_true(dynarray_add(array, &value) == DYNARRAY_SUCCESS);
	assert_true(dynarray_get(array, 0, (void **) &retrieved_value) == DYNARRAY_SUCCESS);
	assert_int_equal(value, *retrieved_value);
}

static void test_dynarray_remove(void **state) {
	dynarray_t *array = *state;

	int first_value = 123;
	int second_value = 456;

	assert_true(dynarray_add(array, &first_value) == DYNARRAY_SUCCESS);
	assert_true(dynarray_add(array, &second_value) == DYNARRAY_SUCCESS);
	assert_int_equal(array->data[0], &first_value);
	assert_int_equal(array->data[1], &second_value);
	assert_int_equal(array->size, 2);

	assert_true(dynarray_remove(array, 0) == DYNARRAY_SUCCESS);
	assert_int_equal(array->data[0], &second_value);
	assert_int_equal(array->size, 1);

	assert_true(dynarray_add(array, &first_value) == DYNARRAY_SUCCESS);
	assert_int_equal(array->data[0], &second_value);
	assert_int_equal(array->data[1], &first_value);
	assert_int_equal(array->size, 2);

	assert_true(dynarray_remove(array, 1) == DYNARRAY_SUCCESS);
	assert_int_equal(array->data[0], &second_value);
	assert_int_equal(array->size, 1);
}

static void test_dynarray_free(void **state) {
	dynarray_t *array = *state;

	assert_true(dynarray_free(array) == DYNARRAY_SUCCESS);
	assert_int_equal(array->data, NULL);
	assert_int_equal(array->capacity, 0);
	assert_int_equal(array->size, 0);
}

static int setup_keyvalue(void **state) {
	keyvalue_set_t *set = malloc(sizeof(keyvalue_set_t));

	assert_true(keyvalue_init(set, 8) == KEYVALUE_SUCCESS);

	*state = set;

	return 0;
}

static int teardown_keyvalue(void **state) {
	keyvalue_free(*state);
	free(*state);

	return 0;
}

static void test_keyvalue_init(void **state) {
	keyvalue_set_t *set = *state;
	dynarray_t *array = set->array;

	assert_int_equal(array->initial_capacity, array->capacity);
	assert_int_equal(array->initial_capacity, 8);
	assert_int_equal(array->size, 0);
}

static void test_keyvalue_size(void **state) {
	keyvalue_set_t *set = *state;

	int size;

	assert_true(keyvalue_size(set, &size) == KEYVALUE_SUCCESS);
	assert_int_equal(size, 0);

	set->array->size = 2;

	assert_true(keyvalue_size(set, &size) == KEYVALUE_SUCCESS);
	assert_int_equal(size, 2);
}

static void test_keyvalue_add_pair(void **state) {
	keyvalue_set_t *set = *state;
	dynarray_t *array = set->array;

	keyvalue_pair_t *pair = malloc(sizeof(keyvalue_pair_t));

	pair->key = "hello";
	pair->value = "world";

	assert_true(keyvalue_add_pair(set, pair) == KEYVALUE_SUCCESS);
	assert_int_equal(array->size, 1);
	assert_int_equal(array->data[0], pair);
}

static void test_keyvalue_add(void **state) {
	keyvalue_set_t *set = *state;
	dynarray_t *array = set->array;

	char *key = "hello";
	char *value = "world";

	assert_true(keyvalue_add(set, key, value) == KEYVALUE_SUCCESS);
	assert_int_equal(array->size, 1);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->key, key);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->value, value);
}

static void test_keyvalue_set(void **state) {
	keyvalue_set_t *set = *state;
	dynarray_t *array = set->array;

	char *key = "hello";
	char *value = "earth";

	assert_true(keyvalue_add(set, key, value) == KEYVALUE_SUCCESS);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->key, key);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->value, value);

	char *new_value = "pluto";

	assert_true(keyvalue_set(set, key, new_value) == KEYVALUE_SUCCESS);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->key, key);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->value, new_value);
}

static void test_keyvalue_get(void **state) {
	keyvalue_set_t *set = *state;

	char *key = "hello";
	char *value = "world";

	char *retrieved_value;

	assert_true(keyvalue_add(set, key, value) == KEYVALUE_SUCCESS);
	assert_true(keyvalue_get(set, key, &retrieved_value) == KEYVALUE_SUCCESS);
	assert_int_equal(value, retrieved_value);
}

static void test_keyvalue_remove(void **state) {
	keyvalue_set_t *set = *state;
	dynarray_t *array = set->array;

	char *first_key = "hello";
	char *first_value = "earth";

	char *second_key = "goodbye";
	char *second_value = "pluto";

	assert_true(keyvalue_add(set, first_key, first_value) == KEYVALUE_SUCCESS);
	assert_true(keyvalue_add(set, second_key, second_value) == KEYVALUE_SUCCESS);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->key, first_key);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->value, first_value);
	assert_int_equal(((keyvalue_pair_t *) array->data[1])->key, second_key);
	assert_int_equal(((keyvalue_pair_t *) array->data[1])->value, second_value);
	assert_int_equal(array->size, 2);

	assert_true(keyvalue_remove(set, first_key) == KEYVALUE_SUCCESS);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->key, second_key);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->value, second_value);
	assert_int_equal(array->size, 1);

	assert_true(keyvalue_add(set, first_key, first_value) == KEYVALUE_SUCCESS);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->key, second_key);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->value, second_value);
	assert_int_equal(((keyvalue_pair_t *) array->data[1])->key, first_key);
	assert_int_equal(((keyvalue_pair_t *) array->data[1])->value, first_value);
	assert_int_equal(array->size, 2);

	assert_true(keyvalue_remove(set, first_key) == KEYVALUE_SUCCESS);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->key, second_key);
	assert_int_equal(((keyvalue_pair_t *) array->data[0])->value, second_value);
	assert_int_equal(array->size, 1);
}

static void test_keyvalue_free(void **state) {
	keyvalue_set_t *set = *state;

	assert_true(keyvalue_free(set) == KEYVALUE_SUCCESS);
	assert_int_equal(set->array, NULL);
}

int main(void) {

	// A list of tests to be done
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_packet_conversion), // Packet conversion test (original->binary->cloned)
		TEST_DYNARRAY(test_dynarray_init),
		TEST_DYNARRAY(test_dynarray_size),
		TEST_DYNARRAY(test_dynarray_add),
		TEST_DYNARRAY(test_dynarray_resize),
		TEST_DYNARRAY(test_dynarray_set),
		TEST_DYNARRAY(test_dynarray_get),
		TEST_DYNARRAY(test_dynarray_remove),
		TEST_DYNARRAY(test_dynarray_free),
		TEST_KEYVALUE(test_keyvalue_init),
		TEST_KEYVALUE(test_keyvalue_size),
		TEST_KEYVALUE(test_keyvalue_add_pair),
		TEST_KEYVALUE(test_keyvalue_add),
		TEST_KEYVALUE(test_keyvalue_set),
		TEST_KEYVALUE(test_keyvalue_get),
		TEST_KEYVALUE(test_keyvalue_remove),
		TEST_KEYVALUE(test_keyvalue_free)
	};

	// Run the tests and return the number of failed tests
	return cmocka_run_group_tests(tests, NULL, NULL);
}
