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
void free_goldbach_sums_matrix(const int64_t row_count,
  goldbach_sums_array_t** matrix);

goldbach_pthread_t* goldbach_pthread_create(array_int64_t* numbers) {
  goldbach_pthread_t* goldbach_pthread = (goldbach_pthread_t*)
    calloc(1, sizeof(goldbach_pthread_t));

  if (goldbach_pthread) {
    goldbach_pthread->numbers = numbers;
    goldbach_pthread->unit_count =
      array_int64_getCount(goldbach_pthread->numbers);
    goldbach_number_queue_init(&goldbach_pthread->queue);
    goldbach_pthread->consumed_count = 0;
    sem_init(&goldbach_pthread->can_consume, 0, 0);
    sem_init(&goldbach_pthread->can_access_next_unit, 0, 1);
    goldbach_pthread->next_unit = 0;
    sem_init(&goldbach_pthread->can_access_consumed_count, 0, 1);
    goldbach_pthread->consumed_count = 0;
  }


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
    // Create consumers and producers
    error = create_consumers_producers(goldbach_pthread);
    // Print the results
    for (int64_t index = 0; index < array_int64_getCount(
      goldbach_pthread->numbers); index++) {
      goldbach_sums_array_print(goldbach_pthread->goldbach_sums[index]);
    }

    goldbach_number_queue_destroy(&goldbach_pthread->queue);

    // Free matrix after all calculations finished
    free_goldbach_sums_matrix(array_int64_getCount(goldbach_pthread->numbers),
      goldbach_pthread->goldbach_sums);
  }
  return error;
}

int create_consumers_producers(goldbach_pthread_t* goldbach_pthread) {
  assert(goldbach_pthread);
  int error = EXIT_SUCCESS;
  int64_t producer_count = 1;
  pthread_t* producer = create_threads(producer_count, produce
    , goldbach_pthread);
  pthread_t* consumers = create_threads(goldbach_pthread->consumer_count,
    consume, goldbach_pthread);

  if (producer && consumers) {
    wait_threads(producer_count, producer);
    for (int64_t index = 0; index < goldbach_pthread->consumer_count; ++index) {
      sem_post(&goldbach_pthread->can_consume);
    }
    wait_threads(goldbach_pthread->consumer_count, consumers);
  } else {
    fprintf(stderr, "error: could not allocate create threads\n");
    error = 22;
  }

  return error;
}

pthread_t* create_threads(size_t count, void*(*subroutine)(void*),
  goldbach_pthread_t* data) {
  pthread_t* threads = (pthread_t*) calloc(count, sizeof(pthread_t));
  // Create as many private_data as threads
  private_data_t* private_data = (private_data_t*)
    calloc(count, sizeof(private_data_t));
  if (threads) {
    for (size_t index = 0; index < count; ++index) {
      private_data[index].thread_number = index;
      // data is goldbach_pthread (shared_data)
      private_data[index].goldbach_pthread = data;

      // "Link" threads with its private_data (GoldbachNumbers are
      // stored in each private_data when consumed)
      if (pthread_create(&threads[index], /*attr*/ NULL, subroutine,
        &private_data[index]) == EXIT_SUCCESS) {
      } else {
        fprintf(stderr, "error: could not create thread %zu\n", index);
        break;
      }
    }
  }
  return threads;
}

int wait_threads(size_t count, pthread_t* threads) {
  int error = EXIT_SUCCESS;
  for (size_t index = 0; index < count; ++index) {
    error += pthread_join(threads[index], /*value_ptr*/ NULL);
  }
  free(threads);
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

