#ifndef GOLDBACH_SUMS_ARRAY
#define GOLDBACH_SUMS_ARRAY

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct goldbach_sums_array{
  int64_t capacity;
  int64_t count;
  int64_t* elements;
  int64_t number;
  bool is_negative_number;
} goldbach_sums_array_t;

/**
 * @brief initialize the goldbach_sums_array struct.
 * @details initialize the goldbach_sums_array struct.
 * @param array pointer to the array to be initialized.
 * @param number number which goldbach sums will be calculated.
 * @return an integer to check errors.
 */
int goldbach_sums_array_init(goldbach_sums_array_t* array, int64_t number);

/**
 * @brief destroys the goldbach_sums_array struct.
 * @details destroys the goldbach_sums_array struct.
 * @param array pointer to the array to be destroyed.
 * @return an integer to check errors.
 */
void goldbach_sums_array_destroy(goldbach_sums_array_t* array);

/**
 * @brief appends an element to the goldbach_sums_array struct.
 * @details appends an element to the goldbach_sums_array struct.
 * @param array pointer to the array.
 * @param element element to be Appended.
 * @return an integer to check errors.
 */
int goldbach_sums_array_append(goldbach_sums_array_t* array, int64_t element);

/**
 * @brief prints the number and/or its goldbach sums.
 * @details prints the number and/or its goldbach sums.
 * @param array pointer to the array.
 */
void goldbach_sums_array_print(goldbach_sums_array_t* array);
#endif  // GOLDBACH_SUMS_ARRAY