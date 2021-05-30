#include <assert.h>
#include <stdlib.h>
#include <stdio.h>/////////////////////
#include <stdint.h>////////////////////
#include <inttypes.h>//////////////////

#include "array_int64.h"

/*
typedef struct array_int64{
  int64_t capacity;
  int64_t count;
  int64_t* elements;
} array_int64_t;
*/

int array_int64_increase_capacity(array_int64_t* array);

int array_int64_init(array_int64_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->elements = NULL;
  return EXIT_SUCCESS;
}

void array_int64_destroy(array_int64_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  free(array->elements);
}

int array_int64_append(array_int64_t* array, int64_t element) {
  assert(array);
  if (array->count == array->capacity) {
    if (array_int64_increase_capacity(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  array->elements[array->count++] = element;
  return EXIT_SUCCESS;
}

int array_int64_increase_capacity(array_int64_t* array) {
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

int64_t array_int64_getCount(array_int64_t* array) {
  return array->count;
}

int64_t array_int64_getElement(array_int64_t* array, int64_t position) {
  return array->elements[position];
}

void array_int64_print(array_int64_t* array){////////////////////////
  printf("%s", "eratostenes: ");
  for (int i = 0; i < array->count; i++){
    printf("%"SCNd64"%s",array->elements[i], ",");
  }
  printf("%s","\n");
}