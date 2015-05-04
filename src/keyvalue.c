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
#include <string.h>

#include "dynarray.h"
#include "keyvalue.h"

unsigned int keyvalue_find_key(keyvalue_set_t *set, char *key, int *index);
unsigned int keyvalue_get_index(keyvalue_set_t *set, int index, keyvalue_pair_t **pair);

unsigned int keyvalue_init(keyvalue_set_t *set, int initial_capacity) {
	if (set == NULL) {
		return KEYVALUE_ERROR;
	}

	set->array = malloc(sizeof(dynarray_t));

	if (dynarray_init(set->array, initial_capacity) != DYNARRAY_SUCCESS) {
		return KEYVALUE_ERROR;
	}

	return KEYVALUE_SUCCESS;
}

unsigned int keyvalue_size(keyvalue_set_t *set, int *size) {
	if (set == NULL) {
		return KEYVALUE_ERROR;
	}

	if (dynarray_size(set->array, size) != DYNARRAY_SUCCESS) {
		return KEYVALUE_ERROR;
	}

	return KEYVALUE_SUCCESS;
}

unsigned int keyvalue_add_pair(keyvalue_set_t *set, keyvalue_pair_t *pair) {
	if (set == NULL) {
		return KEYVALUE_ERROR;
	}

	if (dynarray_add(set->array, pair) != DYNARRAY_SUCCESS) {
		return KEYVALUE_ERROR;
	}

	return KEYVALUE_SUCCESS;
}

unsigned int keyvalue_add(keyvalue_set_t *set, char *key, char *value) {
	if (set == NULL || key == NULL || value == NULL) {
		return KEYVALUE_ERROR;
	}

	keyvalue_pair_t *pair = malloc(sizeof(keyvalue_pair_t));

	pair->key = key;
	pair->value = value;

	if (keyvalue_add_pair(set, pair) != KEYVALUE_SUCCESS) {
		return KEYVALUE_ERROR;
	}

	return KEYVALUE_SUCCESS;
}

unsigned int keyvalue_set(keyvalue_set_t *set, char *key, char *value) {
	if (set == NULL || key == NULL || value == NULL) {
		return KEYVALUE_ERROR;
	}

	int index;

	if (keyvalue_find_key(set, key, &index) != KEYVALUE_SUCCESS) {
		return KEYVALUE_ERROR;
	}

	if (index == -1) {
		if (keyvalue_add(set, key, value) != KEYVALUE_SUCCESS) {
			return KEYVALUE_ERROR;
		}
	} else {
		keyvalue_pair_t *pair;

		if (keyvalue_get_index(set, index, &pair) != KEYVALUE_SUCCESS) {
			return KEYVALUE_ERROR;
		}

		pair->value = value;

		if (dynarray_set(set->array, index, pair) != DYNARRAY_SUCCESS) {
			return KEYVALUE_ERROR;
		}
	}

	return KEYVALUE_SUCCESS;
}

unsigned int keyvalue_find_key(keyvalue_set_t *set, char *key, int *index) {
	if (set == NULL || key == NULL) {
		return KEYVALUE_ERROR;
	}

	int size;
	int curr;
	int found = 0;
	keyvalue_pair_t *pair;

	if (keyvalue_size(set, &size) != KEYVALUE_SUCCESS) {
		return KEYVALUE_ERROR;
	}

	for (curr = 0; curr < size; curr++) {
		if (dynarray_get(set->array, curr, (void **) &pair) != DYNARRAY_SUCCESS) {
			return KEYVALUE_ERROR;
		}

		if (strcmp(pair->key, key) == 0) {
			found = 1;
			break;
		}
	}

	if (found) {
		*index = curr;
	} else {
		*index = -1;
	}

	return KEYVALUE_SUCCESS;
}

unsigned int keyvalue_get(keyvalue_set_t *set, char *key, char **value) {
	if (set == NULL || key == NULL) {
		return KEYVALUE_ERROR;
	}

	int index;

	if (keyvalue_find_key(set, key, &index) != KEYVALUE_SUCCESS) {
		return KEYVALUE_ERROR;
	}

	if (index != -1) {
		keyvalue_pair_t *pair;

		if (keyvalue_get_index(set, index, &pair) != KEYVALUE_SUCCESS) {
			return KEYVALUE_ERROR;
		}

		*value = pair->value;
	} else {
		return KEYVALUE_ERROR;
	}

	return KEYVALUE_SUCCESS;
}


unsigned int keyvalue_get_index(keyvalue_set_t *set, int index, keyvalue_pair_t **pair) {
	if (set == NULL || pair == NULL) {
		return KEYVALUE_ERROR;
	}

	if (dynarray_get(set->array, index, (void **) pair) != DYNARRAY_SUCCESS) {
		return KEYVALUE_ERROR;
	}

	return KEYVALUE_SUCCESS;
}

unsigned int keyvalue_remove(keyvalue_set_t *set, char *key) {
	if (set == NULL || key == NULL) {
		return KEYVALUE_ERROR;
	}

	int index;

	if (keyvalue_find_key(set, key, &index) != KEYVALUE_SUCCESS) {
		return KEYVALUE_ERROR;
	}

	if (index != -1) {
		keyvalue_pair_t *pair;

		if (keyvalue_get_index(set, index, &pair) != KEYVALUE_SUCCESS) {
			return KEYVALUE_ERROR;
		}

		free(pair);

		if (dynarray_remove(set->array, index) != DYNARRAY_SUCCESS) {
			return KEYVALUE_ERROR;
		}
	} else {
		return KEYVALUE_ERROR;
	}

	return KEYVALUE_SUCCESS;
}

unsigned int keyvalue_free(keyvalue_set_t *set) {
	if (set == NULL) {
		return KEYVALUE_ERROR;
	}

	int size;
	int index;
	keyvalue_pair_t *pair;

	if (keyvalue_size(set, &size) != KEYVALUE_SUCCESS) {
		return KEYVALUE_ERROR;
	}

	for (index = 0; index < size; index++) {
		if (dynarray_get(set->array, index, (void **) &pair) != DYNARRAY_SUCCESS) {
			return KEYVALUE_ERROR;
		}

		free(pair);
	}

	if (dynarray_free(set->array) != DYNARRAY_SUCCESS) {
		return KEYVALUE_ERROR;
	}

	set->array = NULL;

	return KEYVALUE_SUCCESS;
}
