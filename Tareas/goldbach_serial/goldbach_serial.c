// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "goldbach_sums_array.h"

int goldbach(int64_t number, goldbach_sums_array_t * goldbach_sums);
int goldbach_strong_conjecture(int64_t number, goldbach_sums_array_t*
  goldbach_sums);
int goldbach_weak_conjecture(int64_t number, goldbach_sums_array_t*
  goldbach_sums);
bool is_even_number(int64_t number);
bool isPrime(int64_t number);

/**
 * @return zero if succeed
 */
int main(void) {
  int64_t error = EXIT_SUCCESS;
  int64_t number = 0;

  // Start time measurement
  struct timespec start_time;
  clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &start_time);

  while (scanf("%"SCNd64, &number) == 1) {
    bool negative_input = number < 0 ? true : false;
    if (negative_input) {
      number *= -1;
    }

    if (number < 0 || number > 5) {
      goldbach_sums_array_t goldbach_sums;
      error = goldbach_sums_array_init(&goldbach_sums, number, negative_input);

      if (error == EXIT_SUCCESS) {
        error = goldbach(number, &goldbach_sums);
        if (error == EXIT_SUCCESS) {
          goldbach_sums_array_print(&goldbach_sums);
          goldbach_sums_array_destroy(&goldbach_sums);
        } else {
          fprintf(stderr, "error: could not calculate goldbach sums\n");
        }
      } else {
        fprintf(stderr, "error: could not init goldbach_sums.\n");
      }
    } else {
      if (negative_input) {
        printf("%"SCNd64 "%s", -number, ": NA\n");
      } else {
        printf("%"SCNd64 "%s", number, ": NA\n");
      }
    }
  }

  // Finish time measurement
  struct timespec finish_time;
  clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &finish_time);

  double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
    (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
  printf("execution time: %.9lfs\n", elapsed);

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
int goldbach(int64_t number, goldbach_sums_array_t * goldbach_sums) {
  int error = EXIT_SUCCESS;

  if (is_even_number(number)) {
    error = goldbach_strong_conjecture(number, goldbach_sums);
  } else {
    error = goldbach_weak_conjecture(number, goldbach_sums);
  }
  return error;
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
int goldbach_strong_conjecture(int64_t number, goldbach_sums_array_t*
  goldbach_sums) {
  int error = EXIT_SUCCESS;

  for (int64_t num1 = 2, num2 = number - 2; num1 <= num2 && !error;
    ++num1, --num2) {
    if (isPrime(num1) && isPrime(num2)) {
        if (num1 + num2 == number) {
          error = goldbach_sums_array_append(goldbach_sums, num1);
          if (error) {
            break;
          }
          error = goldbach_sums_array_append(goldbach_sums, num2);
          if (error) {
            break;
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
int goldbach_weak_conjecture(int64_t number, goldbach_sums_array_t*
  goldbach_sums) {
  int error = EXIT_SUCCESS;

  for (int start = 2, last = number - start; start <= last; start++, last--) {
    for (int medium = start, last_2 = last - medium; medium <= last_2;
      medium++, last_2--) {
      if (start + medium + last_2 == number && isPrime(start) &&
        isPrime(medium) && isPrime(last_2)) {
        error = goldbach_sums_array_append(goldbach_sums, start);
        if (error) {
          break;
        }
        error = goldbach_sums_array_append(goldbach_sums, medium);
        if (error) {
          break;
        }
        error = goldbach_sums_array_append(goldbach_sums, last_2);
        if (error) {
          break;
        }
      }
    }
  }
  return error;
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
  int64_t number_sqrt = (int64_t)sqrt((double)number);
  if (number % 2 == 0 && 2 < number) {
    isPrime = false;
  }
  for (int64_t i = 3; i < number_sqrt + 1 && isPrime; i+=2) {
    if (number % i == 0) {
      isPrime = false;
    }
  }
  return isPrime;
}
