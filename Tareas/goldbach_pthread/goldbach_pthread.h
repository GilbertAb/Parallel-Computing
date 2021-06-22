#ifndef GOLDBACH_PTHREAD
#define GOLDBACH_PTHREAD

#include <stddef.h>
#include "array_int64.h"

typedef struct goldbach_pthread{
  array_int64_t numbers;
} goldbach_pthread_t;

typedef struct {
  int64_t thread_count;
  struct array_int64* goldbach_sums;
} shared_data_t;

typedef struct  {
  int64_t amount_goldbach_sums;
  int64_t thread_number;
  shared_data_t* shared_data;
} private_data_t;
goldbach_pthread_t* goldbach_pthread_create();
int goldbach_pthread_run(goldbach_pthread_t* goldbach_pthread, int argc, char* argv[]);
int goldbach_pthread_calculate_goldbach(goldbach_pthread_t* goldbach_pthread,
  private_data_t* private_data, int64_t start_index, int64_t finish_index,
  array_int64_t* numbers);
int goldbach_pthread_strong_conjecture(goldbach_pthread_t* goldbach_pthread, int64_t number, array_int64_t * goldbach_sums);
int goldbach_pthread_weak_conjecture(goldbach_pthread_t* goldbach_pthread, int64_t number, array_int64_t * goldbach_sums);
int goldbach_pthread_create_threads(goldbach_pthread_t* goldbach_pthread, shared_data_t* shared_data);
void print_goldbach_sums(goldbach_pthread_t* goldbach_pthread, int64_t number, array_int64_t * goldbachSums);
int goldbach_pthread_destroy(goldbach_pthread_t* goldbach_pthread);
#endif  // GOLDBACH_PTHREAD
