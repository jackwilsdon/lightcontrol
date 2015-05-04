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

/**
 * @file dynarray.h
 */

#ifndef _DYNARRAY_H_
#define _DYNARRAY_H_

/**
 * @defgroup dynarray Dynamically Sized Arrays
 * @brief Simple dynamically sized arrays.
 * @{
 */

/**
 * @brief Represents a successful result.
 */
#define DYNARRAY_SUCCESS 1

/**
 * @brief Represents an error result.
 */
#define DYNARRAY_ERROR (!DYNARRAY_SUCCESS)

/**
 * @brief Represents a dynamically sized array.
 */
struct dynarray {

	/**
	 * @brief The data in the array.
	 */
	void **data;

	/**
	 * @brief The starting capacity of the array.
	 */
	int initial_capacity;

	/**
	 * @brief The current capacity of the array.
	 */
	int capacity;

	/**
	 * @brief The current number of items in the array.
	 */
	int size;
};

/**
 * @brief Represents a dynamically sized array
 */
typedef struct dynarray dynarray_t;

/**
 * @brief Initializes a @ref dynarray "dynamically sized array".
 *
 * This method performs the following actions on the provided array
 *  - Allocates an array of pointers for @ref dynarray#data.
 *  - Sets the initial capacity and current capacity to the capacity provided.
 *  - Sets the size to zero.
 *
 * This method should not be called on an existing array, instead the array
 * should be @ref dynarray_free "freed" first.
 *
 * @param[in,out] array The array to initialize.
 * @param[in] initial_capacity The initial capacity of the array.
 * @return @ref DYNARRAY_SUCCESS if the array was initialized successfully,
 *         @ref DYNARRAY_ERROR otherwise.
 */
unsigned int dynarray_init(dynarray_t *array, int initial_capacity);

/**
 * @brief Retrieves the size of a @ref dynarray "dynamically sized array".
 *
 * The size of an array is the current number of item in the array.
 *
 * This method uses @ref dynarray#size internally but should be used instead of
 * @ref dynarray#size as it performs a @c NULL check.
 *
 * @param[in] array The array to retrieve the size of.
 * @param[out] size The size of the array.
 * @return @ref DYNARRAY_SUCCESS if the size was retrieved successfully,
 *         @ref DYNARRAY_ERROR otherwise.
 */
unsigned int dynarray_size(dynarray_t *array, int *size);

/**
 * @brief Adds an item to a @ref dynarray "dynamically sized array".
 *
 * This method appends the provided item to the end of the array.
 * If the new size of the array is greater than the current
 * @ref dynarray#capacity "capacity" then the array's capacity is doubled.
 *
 * @param[in,out] array The array to add the item to.
 * @param[in] item The item to add to the array.
 * @return @ref DYNARRAY_SUCCESS if the item was added successfully,
 *         @ref DYNARRAY_ERROR otherwise.
 */
unsigned int dynarray_add(dynarray_t *array, void *item);

/**
 * @brief Sets the item at an index in a @ref dynarray "dynamically sized array".
 *
 * If the index provided is greater than the capacity of the array,
 * @ref DYNARRAY_ERROR is returned.
 *
 * @param[in,out] array The array to place the item in.
 * @param[in] index The index to place the item at.
 * @param[in] item The item to place at the index.
 * @return @ref DYNARRAY_SUCCESS if the item was placed successfully,
 *         @ref DYNARRAY_ERROR otherwise.
 */
unsigned int dynarray_set(dynarray_t *array, int index, void *item);

/**
 * @brief Retrieves an item from a @ref dynarray "dynamically sized array".
 *
 * If the index provided is greater than the capacity of the array,
 * @ref DYNARRAY_ERROR is returned.
 *
 * @param[in] array The array to retrieve the item from.
 * @param[in] index The index of the item to retrieve.
 * @param[out] item The item at the provided index.
 * @return @ref DYNARRAY_SUCCESS if the item was retrieved successfully,
 *         @ref DYNARRAY_ERROR otherwise.
 */
unsigned int dynarray_get(dynarray_t *array, int index, void **item);

/**
 * @brief Removes an item from a @ref dynarray "dynamically sized array".
 *
 * If the index provided is greater than the capacity of the array,
 * @ref DYNARRAY_ERROR is returned.
 *
 * If the index provided is before the last item of the array it is removed
 * and all items after it are shifted by one place to the left.
 *
 * @param[in,out] array The array to remove the item from.
 * @param[in] index The index of the item to remove.
 * @return @ref DYNARRAY_SUCCESS if the item was removed successfully,
 *         @ref DYNARRAY_ERROR otherwise.
 */
unsigned int dynarray_remove(dynarray_t *array, int index);

/**
 * @brief Frees the memory used by a @ref dynarray "dynamically sized array".
 *
 * This method performs the following actions on the provided array:
 *  - Frees the memory allocated to @ref dynarray#data.
 *  - Sets the pointer of @ref dynarray#data to \c NULL.
 *  - Sets the capacity of the array to zero.
 *  - Sets the size of the array to zero.
 *
 * @param[in,out] array The array to free.
 * @return @ref DYNARRAY_SUCCESS if the array was freed successfully,
 *         @ref DYNARRAY_ERROR otherwise.
 */
unsigned int dynarray_free(dynarray_t *array);

/**
 * @}
 */

#endif
