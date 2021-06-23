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
#include "array_int64.h"

#define NUMCOL 10

void** create_matrix(int64_t row_count, int64_t col_count, int64_t element_size);
void free_matrix(const int64_t row_count, void** matrix);
bool is_even_number(int64_t number);
bool isPrime(int64_t number);
int create_numbers_array(array_int64_t* numbers,char* argv[]);
int block_mapping_start(int64_t thread_number, int64_t total_numbers, int64_t thread_count);
int block_mapping_finish(int64_t thread_number, int64_t total_numbers, int64_t thread_count);
/**
 * @return zero if succeed
 */
goldbach_pthread_t* goldbach_pthread_create() {
  goldbach_pthread_t* goldbach_pthread = (goldbach_pthread_t*)
    calloc(1, sizeof(goldbach_pthread_t));
  array_int64_init(&goldbach_pthread->numbers);

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
    printf("%zu", goldbach_pthread->thread_count);
    if (error == EXIT_SUCCESS) {
      goldbach_pthread->goldbach_sums = (struct array_int64*) create_matrix(goldbach_pthread->thread_count
        , NUMCOL, sizeof(struct array_int64));
    }
    
    create_numbers_array(&goldbach_pthread->numbers, argv);
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
    int64_t amount_numbers = array_int64_getCount(&goldbach_pthread->numbers);
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
      
      // TODO: pthread_create's routine should have only 1 attribute
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
  }
  return error;
}
/**
 * @brief Constructs an array with the goldbach sums
 * @details Verifies if the number is even or odd, then calls
 * a conjecture to create the array of goldbach sums
 * @param number The number wich goldbach sums will be find
 * @param goldbach_sums pointer to the array with the goldbach sums
 * @return Returns an integer to check errors
 */
void* goldbach_pthread_calculate_goldbach(void* data) {
  const private_data_t* private_data = (private_data_t*)data;
  goldbach_pthread_t* goldbach_pthread = private_data->goldbach_pthread;
  /*
  if (is_even_number(number)) {
    error = goldbach_pthread_strong_conjecture(goldbach_pthread, number, goldbach_sums);
  } else {
    error = goldbach_pthread_weak_conjecture(goldbach_pthread, number, goldbach_sums);
  }
  */
  return NULL;
}

/**
 * @brief Constructs an array with the goldbach sums
 * @details The conjecture for even numbers, the first position of the array
 * is the amount of goldbach sums of the number. the next positions are the
 * numbers that conform the sums (they will be accessed in pairs to print)
 * @param number The number wich goldbach sums will be find
 * @param goldbach_sums pointer to the array with the goldbach sums
 * @return Returns an integer to check errors
 */
int goldbach_pthread_strong_conjecture(goldbach_pthread_t* goldbach_pthread, int64_t number, array_int64_t * goldbach_sums) {
  int error = EXIT_SUCCESS;

  for (int64_t num1 = 2; num1 < number && !error; ++num1) {
    if (isPrime(num1)) {
      for (int64_t num2 = num1; num2 < number; ++num2) {
        if (num1 + num2 == number && isPrime(num2)) {
          error = array_int64_append(goldbach_sums, num1);
          if (error) {
            break;
          }
          error = array_int64_append(goldbach_sums, num2);
          if (error) {
            break;
          }
        }
      }
    }
  }

  return error;
}

/**
 * @brief Constructs an array with the goldbach sums
 * @details The conjecture for odd numbers, the first position of the array
 * is the amount of goldbach sums of the number. the next positions are the
 * numbers that conform the sums (they will be accessed int trios to print)
 * @param number The number wich goldbach sums will be find
 * @param goldbach_sums pointer to the array with the goldbach sums
 * @return Returns an integer to check errors
 */
int goldbach_pthread_weak_conjecture(goldbach_pthread_t* goldbach_pthread, int64_t number, array_int64_t * goldbach_sums) {
  int error = EXIT_SUCCESS;

  for (int64_t num1 = 2; num1 < number && !error; ++num1) {
    if (isPrime(num1)) {
      for (int64_t num2 = num1; num2 < number && !error; ++num2) {
        if (isPrime(num2)) {
          for (int64_t num3 = num2; num3 < number; ++num3) {
            if (num1 + num2 + num3 == number && isPrime(num3)) {
              error = array_int64_append(goldbach_sums, num1);
              if (error) {
                break;
              }
              error = array_int64_append(goldbach_sums, num2);
              if (error) {
                break;
              }
              error = array_int64_append(goldbach_sums, num3);
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

/**
 * @brief Prints the goldbach sums of a number
 * @details Prints the goldbach sums of a number
 * @param number The number wich goldbach sums will be printed
 * @param goldbach_sums pointer to the array with the goldbach sums
 */
void print_goldbach_sums(goldbach_pthread_t* goldbach_pthread, int64_t number, array_int64_t * goldbach_sums) {
  int counter = 1;
  int counterMax = 3;
  int index = 0;

  if (is_even_number(number)) {
    counterMax = 2;
  }

  while (index < array_int64_getCount(goldbach_sums)) {
    printf("%"SCNd64, array_int64_getElement(goldbach_sums, index));
    if (counter < counterMax) {
      printf("%s", " + ");
      ++counter;
    } else {
      if ((index + 1) != array_int64_getCount(goldbach_sums)) {
        printf("%s", ", ");
      }
      counter = 1;
    }
    index++;
  }
}

/**
 * @brief Returns if a number is even
 * @details proves if a number is divisible by 2
 * @param number The number
 * @return Returns true if a number is even
 */
bool is_even_number(int64_t number) {
  return number % 2 == 0;
}

/**
 * @brief Returns if a number is a prime number
 * @details Determines if a number is a prime number by checking if it
 * has more than two divisors
 * @param number The number
 * @return Returns true if a number is a prime number
 */
bool isPrime(int64_t number) {
  bool isPrime = true;

  for (int64_t i = 2; i < number; ++i) {
    if (number % i == 0) {
      isPrime = false;
    }
  }

  return isPrime;
}

int goldbach_pthread_destroy(goldbach_pthread_t* goldbach_pthread) {
  
  return EXIT_SUCCESS;
}


void** create_matrix(int64_t row_count, int64_t col_count, int64_t element_size) {
  void** matrix = (void**) calloc(row_count, sizeof(void*));
  if ( matrix == NULL ) {
    return NULL;
  }

  for (int64_t row = 0; row < row_count; ++row) {
    if ( (matrix[row] = calloc(col_count, element_size) ) == NULL ) {
      free_matrix(row_count, matrix);
      return NULL;
    }
  }

  return matrix;
}

void free_matrix(const int64_t row_count, void** matrix) {
  if (matrix) {
    for (int64_t row = 0; row < row_count; ++row) {
      free(matrix[row]);
    }
  }

  free(matrix);
}

int create_numbers_array(array_int64_t* numbers,char* argv[]) {
  int error = EXIT_SUCCESS;
  int64_t number = 0;
  
  while (scanf("%"SCNd64, &number) == 1) {
    error = array_int64_append(numbers, number);
  }

  return error;
}

int block_mapping_start(int64_t thread_number, int64_t total_numbers, int64_t thread_count) {
  int64_t mod = total_numbers % thread_count;
  int64_t min = thread_number < mod ? thread_number : mod;
  return thread_number * (total_numbers / thread_count) + min;
}

int block_mapping_finish(int64_t thread_number, int64_t total_numbers, int64_t thread_count) {
  return block_mapping_start(thread_number + 1, total_numbers, thread_count);
}