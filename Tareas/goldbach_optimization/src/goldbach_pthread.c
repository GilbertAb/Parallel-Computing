// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>

#include "goldbach_pthread.h"

/**
 * @brief creates a matrix of goldbach sums.
 * @details creates a vector of pointers to array_int64 structures(the 
 * goldbach_sums_matrix)). Every number has an array_int64 structure.
 * @param numbers the numbers to create the matrix.
 * @return the matrix.
 */
goldbach_sums_array_t** create_goldbach_sums_matrix(array_int64_t* numbers);

/**
 * @brief frees a matrix of goldbach sums.
 * @details frees a vector of pointers to array_int64 structures(the
 * goldbach_sums_matrix).
 * @param row_count the amount of numbers.
 * @param numbers the matrix.
 * @return the matrix.
 */
void free_goldbach_sums_matrix(const int64_t row_count, goldbach_sums_array_t** matrix);

goldbach_pthread_t* goldbach_pthread_create(array_int64_t* numbers) {
  goldbach_pthread_t* goldbach_pthread = (goldbach_pthread_t*)
    calloc(1, sizeof(goldbach_pthread_t));

  goldbach_pthread->numbers = numbers;

  return goldbach_pthread;
}

int goldbach_pthread_run(goldbach_pthread_t* goldbach_pthread, int argc,
  char* argv[]) {
  assert(goldbach_pthread);
  int error = EXIT_SUCCESS;
  // Assign consumer_count
  goldbach_pthread->consumer_count = sysconf(_SC_NPROCESSORS_ONLN);
  if (goldbach_pthread) {
    if (argc == 2) {
      if (sscanf(argv[1], "%zu", &goldbach_pthread->consumer_count) != 1
        || errno) {
        fprintf(stderr, "error: invalid thread count\n");
        error = 1;
      }
    }
    if (error == EXIT_SUCCESS) {
      // Create goldbach sums matrix to use conditionally safety
      goldbach_pthread->goldbach_sums = create_goldbach_sums_matrix(
        goldbach_pthread->numbers);
    }
    // Create threads
    error = goldbach_pthread_create_threads(goldbach_pthread);
    // Free matrix after all calculations finished
    free_goldbach_sums_matrix(array_int64_getCount(goldbach_pthread->numbers),
      goldbach_pthread->goldbach_sums);
  }
  return error;
}

int goldbach_pthread_create_threads(goldbach_pthread_t* goldbach_pthread) {
  assert(goldbach_pthread);
  int error = EXIT_SUCCESS;
  
  // Allocate space for threads and their respective private data
  pthread_t* threads = (pthread_t*) calloc(goldbach_pthread->consumer_count
    , sizeof(pthread_t));
  private_data_t* private_data = (private_data_t*)
    calloc(goldbach_pthread->consumer_count, sizeof(private_data_t));

  if (threads && private_data) {
    int64_t numbers_count = array_int64_getCount(goldbach_pthread->numbers);
    int64_t consumer_count = goldbach_pthread->consumer_count;
    // If there are more threads than numbers, then use as many threads as 
    // numbers
    if (numbers_count < consumer_count) {
      consumer_count = numbers_count;
    }

    for (int64_t index = 0; index < goldbach_pthread->consumer_count; ++index) {
      private_data[index].thread_number = index;
      private_data[index].goldbach_pthread = goldbach_pthread;
      // Get working block for every thread

      // Create thread and make it work with it's respective working block
      if (pthread_create(&threads[index], /*attr*/NULL,
        goldbach_calculator_calculate_goldbach, &private_data[index])
        == EXIT_SUCCESS) {
      } else {
          fprintf(stderr, "error: could not create thread %zu\n", index);
          error = 21;
          goldbach_pthread->consumer_count = index;
          break;
        }
    }
    // Join of threads after finishing their work
    for (int64_t index = 0; index < goldbach_pthread->consumer_count; ++index) {
      pthread_join(threads[index], /*value_ptr*/ NULL);
    }
    // Printing the results
    for (int64_t index = 0; index < array_int64_getCount(
      goldbach_pthread->numbers); index++) {
      goldbach_sums_array_print(goldbach_pthread->goldbach_sums[index]);
    }
    // Free memory
    free(threads);
    free(private_data);
  } else {
    fprintf(stderr, "Could not allocate memory for %zu threads\n"
      , goldbach_pthread->consumer_count);
    error = 22;
  }
  return error;
}

int goldbach_pthread_destroy(goldbach_pthread_t* goldbach_pthread) {
  assert(goldbach_pthread);
  free(goldbach_pthread);
  return EXIT_SUCCESS;
}

goldbach_sums_array_t** create_goldbach_sums_matrix(array_int64_t* numbers) {
  assert(numbers);
  goldbach_sums_array_t** matrix = (goldbach_sums_array_t**)
    calloc((size_t)array_int64_getCount(numbers), sizeof(
    goldbach_sums_array_t));
  if (matrix == NULL) {
    return NULL;
  }

  for (int64_t row = 0; row < array_int64_getCount(numbers); ++row) {
    goldbach_sums_array_t* array_goldbach_sums = (goldbach_sums_array_t*)
      calloc(1, sizeof(goldbach_sums_array_t));
    int error = goldbach_sums_array_init(array_goldbach_sums,
      array_int64_getElement(numbers, row));
    if (error) {
      free_goldbach_sums_matrix(array_int64_getCount(numbers), matrix);
      return NULL;
    }
    matrix[row] = array_goldbach_sums;
  }
  return matrix;
}

void free_goldbach_sums_matrix(const int64_t row_count, 
  goldbach_sums_array_t** matrix) {
  if (matrix) {
    for (int64_t row = 0; row < row_count; ++row) {
      goldbach_sums_array_destroy(matrix[row]);
      free(matrix[row]);
    }
  }
  free(matrix);
}

