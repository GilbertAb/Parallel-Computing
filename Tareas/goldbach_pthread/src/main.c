// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>

#include <stdlib.h>
#include <time.h>
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
    // Start time measurement
    struct timespec start_time;
    clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &start_time);

    int result = goldbach_pthread_run(goldbach_pthread, argc, argv);

    // Finish time measurement
    struct timespec finish_time;
    clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &finish_time);

    double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
      (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
    printf("execution time: %.9lfs\n", elapsed);

    goldbach_pthread_destroy(goldbach_pthread);
    array_int64_destroy(&numbers);
    return result;
  } else {
    fprintf(stderr, "error: could not allocate goldbach_pthread\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
