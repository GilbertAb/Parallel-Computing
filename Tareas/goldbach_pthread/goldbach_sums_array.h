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


int goldbach_sums_array_init(goldbach_sums_array_t* array, int64_t number);
void goldbach_sums_array_destroy(goldbach_sums_array_t* array);
int goldbach_sums_array_append(goldbach_sums_array_t* array, int64_t element);
void goldbach_sums_array_print(goldbach_sums_array_t* array);
#endif  // GOLDBACH_SUMS_ARRAY