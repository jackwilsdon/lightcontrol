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

#ifndef _DYNARRAY_H_
#define _DYNARRAY_H_

#define DYNARRAY_SUCCESS 1
#define DYNARRAY_ERROR (!DYNARRAY_SUCCESS)

struct dynarray {
	void **data;
	int initial_capacity;
	int capacity;
	int size;
};

typedef struct dynarray dynarray_t;

unsigned int dynarray_init(dynarray_t *array, int initial_capacity);
unsigned int dynarray_size(dynarray_t *array, int *size);
unsigned int dynarray_add(dynarray_t *array, void *item);
unsigned int dynarray_set(dynarray_t *array, int index, void *item);
unsigned int dynarray_get(dynarray_t *array, int index, void **item);
unsigned int dynarray_remove(dynarray_t *array, int index);
unsigned int dynarray_free(dynarray_t *array);

#endif
