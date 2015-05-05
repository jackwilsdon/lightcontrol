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

#ifndef _KEYVALUE_H_
#define _KEYVALUE_H_

#include "dynarray.h"

#define KEYVALUE_SUCCESS 1
#define KEYVALUE_ERROR (!DYNARRAY_SUCCESS)

struct keyvalue_pair {
	char *key;
	char *value;
};

typedef struct keyvalue_pair keyvalue_pair_t;

struct keyvalue_set {
	dynarray_t *array;
};

typedef struct keyvalue_set keyvalue_set_t;

unsigned int keyvalue_init(keyvalue_set_t *set, int initial_capacity);
unsigned int keyvalue_size(keyvalue_set_t *set, int *size);
unsigned int keyvalue_add_pair(keyvalue_set_t *set, keyvalue_pair_t *pair);
unsigned int keyvalue_add(keyvalue_set_t *set, char *key, char *value);
unsigned int keyvalue_set(keyvalue_set_t *set, char *key, char *value);
unsigned int keyvalue_find_key(keyvalue_set_t *set, char *key, int *index);
unsigned int keyvalue_get(keyvalue_set_t *set, char *key, char **value);
unsigned int keyvalue_get_index(keyvalue_set_t *set, int index, keyvalue_pair_t **pair);
unsigned int keyvalue_remove(keyvalue_set_t *set, char *key);
unsigned int keyvalue_free(keyvalue_set_t *set);

#endif
