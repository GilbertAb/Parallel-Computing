// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>

#ifndef TAREAS_GOLDBACH_PTHREAD_ARRAY_INT64_H_
#define TAREAS_GOLDBACH_PTHREAD_ARRAY_INT64_H_

#include <stddef.h>

typedef struct array_int64 {
  int64_t capacity;
  int64_t count;
  int64_t* elements;
} array_int64_t;


int array_int64_init(array_int64_t* array);
void array_int64_destroy(array_int64_t* array);
int array_int64_append(array_int64_t* array, int64_t element);
int64_t array_int64_getCount(array_int64_t* array);
int64_t array_int64_getElement(array_int64_t* array, int64_t position);
#endif  // TAREAS_GOLDBACH_PTHREAD_ARRAY_INT64_H_
