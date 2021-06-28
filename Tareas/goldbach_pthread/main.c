// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "goldbach_pthread.h"
#include "array_int64.h"

/**
 * @return zero if succeed
 */
int main(int argc, char* argv[]) {
  array_int64_t numbers;
  array_int64_init(&numbers);
  int64_t number = 0;
  
  while (scanf("%"SCNd64, &number) == 1) {
    array_int64_append(&numbers, number);
  }
  goldbach_pthread_t* goldbach_pthread = goldbach_pthread_create(&numbers);

  if (goldbach_pthread) {
    int result = goldbach_pthread_run(goldbach_pthread, argc, argv);
    goldbach_pthread_destroy(goldbach_pthread);
    array_int64_destroy(&numbers);
    return result;
  } else {
    fprintf(stderr, "error: could not allocate goldbach_pthread\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
