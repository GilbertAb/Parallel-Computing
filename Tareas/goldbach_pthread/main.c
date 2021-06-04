// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>

#include <stdlib.h>
#include <stdio.h>

#include "goldbach_pthread.h"

int main(int argc, char* argv[]) {
  goldbach_pthread_t* goldbach_pthread = goldbach_pthread_create();
  if (goldbach_pthread) {
    int result = goldbach_pthread_run(goldbach_pthread, argc, argv);
    goldbach_pthread_destroy(goldbach_pthread);
    return result;
  } else {
    fprintf(stderr, "error: could not allocate goldbach_pthread\n");
    return EXIT_FAILURE;
  }
}
