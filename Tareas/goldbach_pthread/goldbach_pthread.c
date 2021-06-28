// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>
#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "goldbach_pthread.h"

#define NUMCOL 10

/**
 * @brief creates a matrix of goldbach sums.
 * @details creates a vector of pointers to array_int64 structures(the 
 * goldbach_sums_matrix)).
 * Every number has an array_int64 structure.
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
void free_matrix(const int64_t row_count, goldbach_sums_array_t** matrix);

/**
 * @brief returns the start index of a block mapping.
 * @details calculates and returns the start index of a block mapping.
 * @param thread_number the number of thread which index will be assigned.
 * @param total_numbers total of numbers to be assigned between all threads.
 * @param thread_count the total number of threads.
 * @return the start index of a block mapping.
 */
int block_mapping_start(int64_t thread_number, int64_t total_numbers,
  int64_t thread_count);

/**
* @brief returns the finish index of a block mapping.
* @details calculates and returns the finish index of a block mapping.
* @param thread_number the number of thread which index will be assigned.
* @param total_numbers total of numbers to be assigned between all threads.
* @param thread_count the total number of threads.
* @return the finish index of a block mapping.
*/
int block_mapping_finish(int64_t thread_number, int64_t total_numbers, 
  int64_t thread_count);
/**
 * @brief returns if a number is even
 * @details proves if a number is divisible by 2
 * @param number the number
 * @return true if a number is even
 */
bool is_even_number(int64_t number);

/**
 * @brief returns if a number is a prime number
 * @details determines if a number is a prime number by checking if it
 * has more than two divisors
 * @param number the number
 * @return true if a number is a prime number
 */
bool isPrime(int64_t number);


goldbach_pthread_t* goldbach_pthread_create(array_int64_t* numbers) {
  goldbach_pthread_t* goldbach_pthread = (goldbach_pthread_t*)
    calloc(1, sizeof(goldbach_pthread_t));
  
  goldbach_pthread->numbers = numbers;

  return goldbach_pthread;
}

int goldbach_pthread_run(goldbach_pthread_t* goldbach_pthread, int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  
  goldbach_pthread->thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  if (goldbach_pthread) {
    if(argc == 2){
      if (sscanf(argv[1], "%zu", &goldbach_pthread->thread_count) != 1 || errno) {
        fprintf(stderr, "error: invalid thread count\n");
        error = 1;
      }
    }
    if (error == EXIT_SUCCESS) {
      goldbach_pthread->goldbach_sums = create_goldbach_sums_matrix(goldbach_pthread->numbers);
    }    
    goldbach_pthread_create_threads(goldbach_pthread);

  }
  return EXIT_SUCCESS;
}

int goldbach_pthread_create_threads(goldbach_pthread_t* goldbach_pthread){
  assert(goldbach_pthread);
  int error = EXIT_SUCCESS;
  
  pthread_t* threads = (pthread_t*) calloc(goldbach_pthread->thread_count
    , sizeof(pthread_t));
  private_data_t* private_data = (private_data_t*)
    calloc(goldbach_pthread->thread_count, sizeof(private_data_t));

  if (threads && private_data) {
    int64_t amount_numbers = array_int64_getCount(goldbach_pthread->numbers);
    int64_t amount_threads = goldbach_pthread->thread_count;

    if (amount_numbers < amount_threads) {
      amount_threads = amount_numbers;
    }
    
    for (int64_t index = 0; index < goldbach_pthread->thread_count; ++index) {
      private_data[index].thread_number = index;
      private_data[index].goldbach_pthread = goldbach_pthread;
      private_data[index].start_index = block_mapping_start(
        private_data[index].thread_number, amount_numbers, amount_threads);
      private_data[index].finish_index = block_mapping_finish(
        private_data[index].thread_number, amount_numbers, amount_threads);

      if (pthread_create(&threads[index], /*attr*/NULL, 
        goldbach_pthread_calculate_goldbach, &private_data[index]
        ) == EXIT_SUCCESS) {
      } else {
          fprintf(stderr, "error: could not create thread %zu\n", index);
          error = 21;
          goldbach_pthread->thread_count = index;
          break;
        }
    }
    
    for (int64_t index = 0; index < goldbach_pthread->thread_count; ++index) {
      pthread_join(threads[index], /*value_ptr*/ NULL);
    }
    
    for (int64_t index = 0; index < array_int64_getCount(goldbach_pthread->numbers); index++) {
      goldbach_sums_array_print(goldbach_pthread->goldbach_sums[index]);
    }

    free(threads);
    free(private_data);
  } else {
    fprintf(stderr, "Could not allocate memory for %zu threads\n"
      , goldbach_pthread->thread_count);
    error = 22;
  }
  return error;
}

void* goldbach_pthread_calculate_goldbach(void* data) {
  int error = EXIT_SUCCESS;
  const private_data_t* private_data = (private_data_t*)data;
  int64_t thread_number = private_data->thread_number;
  goldbach_pthread_t* goldbach_pthread = private_data->goldbach_pthread;
  
  for (int index = private_data->start_index; index < private_data->finish_index; index++) {
    int64_t number = array_int64_getElement(goldbach_pthread->numbers,index);
    if (number < 0) {
      number *= -1;
    }

    if (number < 0 || number > 5) {
      if (is_even_number(number)) {
        error = goldbach_pthread_strong_conjecture(goldbach_pthread, number, index);
      } else {
        error = goldbach_pthread_weak_conjecture(goldbach_pthread, number, index);
      }
    }
  }  
  return NULL;
}

int goldbach_pthread_strong_conjecture(goldbach_pthread_t* goldbach_pthread, int64_t number, int64_t thread_number) {
  int error = EXIT_SUCCESS;

  for (int64_t num1 = 2; num1 < number && !error; ++num1) {
    if (isPrime(num1)) {
      for (int64_t num2 = num1; num2 < number; ++num2) {
        if (num1 + num2 == number && isPrime(num2)) {
          error = goldbach_sums_array_append(goldbach_pthread->goldbach_sums[thread_number], num1);
          if (error) {
            break;
          }
          error = goldbach_sums_array_append(goldbach_pthread->goldbach_sums[thread_number], num2);
          if (error) {
            break;
          }
        }
      }
    }
  }
  return error;
}

int goldbach_pthread_weak_conjecture(goldbach_pthread_t* goldbach_pthread, int64_t number, int64_t thread_number) {
  int error = EXIT_SUCCESS;

  for (int64_t num1 = 2; num1 < number && !error; ++num1) {
    if (isPrime(num1)) {
      for (int64_t num2 = num1; num2 < number && !error; ++num2) {
        if (isPrime(num2)) {
          for (int64_t num3 = num2; num3 < number; ++num3) {
            if (num1 + num2 + num3 == number && isPrime(num3)) {
              error = goldbach_sums_array_append(goldbach_pthread->goldbach_sums[thread_number], num1);
              if (error) {
                break;
              }
              error = goldbach_sums_array_append(goldbach_pthread->goldbach_sums[thread_number], num2);
              if (error) {
                break;
              }
              error = goldbach_sums_array_append(goldbach_pthread->goldbach_sums[thread_number], num3);
              if (error) {
                break;
              }
            }
          }
        }
      }
    }
  }
  return error;
}

int goldbach_pthread_destroy(goldbach_pthread_t* goldbach_pthread) {
  free(goldbach_pthread);
  return EXIT_SUCCESS;
}

goldbach_sums_array_t** create_goldbach_sums_matrix(array_int64_t* numbers) {
  goldbach_sums_array_t** matrix = (goldbach_sums_array_t**) 
    calloc((size_t)array_int64_getCount(numbers), sizeof(goldbach_sums_array_t));
  if (matrix == NULL) {
    return NULL;
  }
  
  for (int64_t row = 0; row < array_int64_getCount(numbers); ++row) {
    goldbach_sums_array_t* array_goldbach_sums = (goldbach_sums_array_t*) 
      calloc(1, sizeof(goldbach_sums_array_t));
    int error = goldbach_sums_array_init(array_goldbach_sums,
      array_int64_getElement(numbers,row));
    if (error) {
      free_matrix(array_int64_getCount(numbers), matrix);
      return NULL;
    }
    matrix[row] = array_goldbach_sums;
  }

  return matrix;
}

void free_matrix(const int64_t row_count, goldbach_sums_array_t** matrix) {
  if (matrix) {
    for (int64_t row = 0; row < row_count; ++row) {
      free(matrix[row]);
      goldbach_sums_array_destroy(matrix[row]);
    }
  }

  free(matrix);
}

int block_mapping_start(int64_t thread_number, int64_t total_numbers, int64_t thread_count) {
  int64_t mod = total_numbers % thread_count;
  int64_t min = thread_number < mod ? thread_number : mod;
  return thread_number * (total_numbers / thread_count) + min;
}

int block_mapping_finish(int64_t thread_number, int64_t total_numbers, int64_t thread_count) {
  return block_mapping_start(thread_number + 1, total_numbers, thread_count);
}

bool is_even_number(int64_t number) {
  return number % 2 == 0;
}

bool isPrime(int64_t number) {
  bool isPrime = true;

  for (int64_t i = 2; i < number; ++i) {
    if (number % i == 0) {
      isPrime = false;
    }
  }

  return isPrime;
}