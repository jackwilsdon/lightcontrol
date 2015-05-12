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

#include "dynarray.h"

unsigned int dynarray_init(dynarray_t *array, int initial_capacity) {
	if (array == NULL) {
		return DYNARRAY_ERROR;
	}

	void **data = malloc(sizeof(void *) * initial_capacity);

	if (data == NULL) {
		return DYNARRAY_ERROR;
	}

	array->data = data;
	array->initial_capacity = initial_capacity > 0 ? initial_capacity : 8;
	array->capacity = initial_capacity;
	array->size = 0;

	return DYNARRAY_SUCCESS;
}

unsigned int dynarray_size(dynarray_t *array, int *size) {
	if (array == NULL) {
		return DYNARRAY_ERROR;
	}

	*size = array->size;

	return DYNARRAY_SUCCESS;
}

unsigned int dynarray_resize(dynarray_t *array, int capacity) {
	if (array == NULL || array->data == NULL) {
		return DYNARRAY_ERROR;
	}

	void **data = realloc(array->data, sizeof(void *) * capacity);

	if (data == NULL) {
		return DYNARRAY_ERROR;
	}

	array->data = data;
	array->capacity = capacity;

	return DYNARRAY_SUCCESS;
}

unsigned int dynarray_add(dynarray_t *array, void *item) {
	if (array == NULL || array->data == NULL || item == NULL) {
		return DYNARRAY_ERROR;
	}

	int capacity = array->capacity;
	int size = array->size;

	if (size >= capacity) {
		if (dynarray_resize(array, capacity * 2) != DYNARRAY_SUCCESS) {
			return DYNARRAY_ERROR;
		}
	}

	array->data[array->size] = item;
	array->size++;

	return DYNARRAY_SUCCESS;
}

unsigned int dynarray_set(dynarray_t *array, int index, void *item) {
	if (array == NULL || array->data == NULL ||
		index < 0 || index >= array->capacity ||
		item == NULL) {

		return DYNARRAY_ERROR;
	}

	array->data[index] = item;

	return DYNARRAY_SUCCESS;
}

unsigned int dynarray_get(dynarray_t *array, int index, void **item) {
	if (array == NULL || array->data == NULL ||
		index < 0 || index >= array->size ||
		item == NULL) {

		return DYNARRAY_ERROR;
	}

	*item = array->data[index];

	return DYNARRAY_SUCCESS;
}

unsigned int dynarray_remove(dynarray_t *array, int index) {
	if (array == NULL || array->data == NULL ||
		index < 0 || index >= array->size) {

		return DYNARRAY_ERROR;
	}

	void **data = array->data;
	int initial_capacity = array->initial_capacity;
	int capacity = array->capacity;
	int size = array->size;

	data[index] = NULL;

	if (index < (size - 1)) {
		int current;

		for (current = index; current < (size - 1); current++) {
			data[current] = data[current + 1];
			data[current + 1] = NULL;
		}
	}

	array->size = --size;

	int new_capacity = capacity / 2;

	if (size > 0 && size <= new_capacity && new_capacity >= initial_capacity) {
		if (dynarray_resize(array, new_capacity) != DYNARRAY_SUCCESS) {
			return DYNARRAY_ERROR;
		}
	}

	return DYNARRAY_SUCCESS;
}

unsigned int dynarray_free(dynarray_t *array) {
	if (array == NULL || array->data == NULL) {
		return DYNARRAY_ERROR;
	}

	free(array->data);
	array->data = NULL;

	array->capacity = 0;
	array->size = 0;

	return DYNARRAY_SUCCESS;
}
