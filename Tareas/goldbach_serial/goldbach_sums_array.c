#include <assert.h>
#include <stdlib.h>

#include "goldbach_sums_array.h"


int goldbach_sums_array_increase_capacity(goldbach_sums_array_t* array);

/**
 * @brief initialize the goldbach_sums_array struct
 * @details initialize the goldbach_sums_array struct
 * @param array pointer to the array to be initialized
 * @return returns an integer to check errors
 */
int goldbach_sums_array_init(goldbach_sums_array_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->elements = NULL;
  return EXIT_SUCCESS;
}
/**
 * @brief destroys the goldbach_sums_array struct
 * @details initialize the goldbach_sums_array struct
 * @param array pointer to the array to be destroyed
 * @return returns an integer to check errors
 */
void goldbach_sums_array_destroy(goldbach_sums_array_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  free(array->elements);
}

/**
 * @brief appends an element to the goldbach_sums_array struct
 * @details appends an element to the goldbach_sums_array struct
 * @param array pointer to the array
 * @param element element to be Appended
 * @return returns an integer to check errors
 */
int goldbach_sums_array_append(goldbach_sums_array_t* array, int64_t element) {
  assert(array);
  if (array->count == array->capacity) {
    if (goldbach_sums_array_increase_capacity(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  array->elements[array->count++] = element;
  return EXIT_SUCCESS;
}
/**
 * @brief increases the capacity of the goldbach_sums_array struct
 * @details increases the capacity of the goldbach_sums_array struct by making it
 * 10 times bigger
 * @param array pointer to the array
 * @return returns an integer to check errors
 */
int goldbach_sums_array_increase_capacity(goldbach_sums_array_t* array) {
  int64_t new_capacity = 10 * (array->capacity ? array->capacity : 1);
  int64_t* new_elements = (int64_t*)
    realloc(array->elements, new_capacity * sizeof(int64_t));

  if (new_elements) {
    array->capacity = new_capacity;
    array->elements = new_elements;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

/**
 * @brief returns the count of elements in the array
 * @details returns the count of elements in the array
 * @param array pointer to the array
 * @return returns the count of elements in the array
 */
int64_t goldbach_sums_array_getCount(goldbach_sums_array_t* array) {
  return array->count;
}

/**
 * @brief returns an element of the array
 * @details returns an element of an specific position in the array 
 * @param array pointer to the array
 * @param position position of the element in the array
 * @return returns an element of the array
 */
int64_t goldbach_sums_array_getElement(goldbach_sums_array_t* array, int64_t position) {
  return array->elements[position];
}
