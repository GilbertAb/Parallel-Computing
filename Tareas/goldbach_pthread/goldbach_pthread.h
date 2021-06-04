#ifndef GOLDBACH_PTHREAD
#define GOLDBACH_PTHREAD

#include <stddef.h>
#include "array_int64.h"

typedef struct goldbach_pthread{
  int64_t capacity;
  int64_t count;
  int64_t* elements;
} goldbach_pthread_t;

int goldbach_pthread_create();
int goldbach_pthread_run(goldbach_pthread_t* goldbach_pthread, int argc, char* argv[]);
int goldbach_pthread_calculate_goldbach(goldbach_pthread_t* goldbach_pthread, int64_t number, array_int64_t * goldbach_sums);
int goldbach_pthread_strong_conjecture(goldbach_pthread_t* goldbach_pthread, int64_t number, array_int64_t * goldbach_sums);
int goldbach_pthread_weak_conjecture(goldbach_pthread_t* goldbach_pthread, int64_t number, array_int64_t * goldbach_sums);
int goldbach_pthread_create_threads(goldbach_pthread_t* goldbach_pthread, char* argv[]);
void print_goldbach_sums(goldbach_pthread_t* goldbach_pthread, int64_t number, array_int64_t * goldbachSums);
int goldbach_pthread_destroy(goldbach_pthread_t* goldbach_pthread);
#endif  // GOLDBACH_PTHREAD