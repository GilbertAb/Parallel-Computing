#ifndef GOLDBACH_SUMS_ARRAY
#define GOLDBACH_SUMS_ARRAY

#include <stddef.h>

typedef struct goldbach_sums_array{
  int64_t capacity;
  int64_t count;
  int64_t* elements;
} goldbach_sums_array_t;


int goldbach_sums_array_init(goldbach_sums_array_t* array);
void goldbach_sums_array_destroy(goldbach_sums_array_t* array);
int goldbach_sums_array_append(goldbach_sums_array_t* array, int64_t element);
int64_t goldbach_sums_array_getCount(goldbach_sums_array_t* array);
int64_t goldbach_sums_array_getElement(goldbach_sums_array_t* array, int64_t position);
#endif  // GOLDBACH_SUMS_ARRAY