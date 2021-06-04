// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "goldbach_pthread.h"
#include "array_int64.h"

/*
int goldbach(int64_t number, array_int64_t * goldbach_sums);
int goldbach_strong_conjecture(int64_t number, array_int64_t * goldbach_sums);
int goldbach_weak_conjecture(int64_t number, array_int64_t * goldbach_sums);
void print_goldbach_sums(int64_t number, array_int64_t * goldbachSums);*/
bool is_even_number(int64_t number);
bool isPrime(int64_t number);

/**
 * @return zero if succeed
 */

int goldbach_pthread_create() {

  return EXIT_SUCCESS;
}
int goldbach_pthread_run(goldbach_pthread_t* goldbach_pthread, int argc, char* argv[]) {
  return EXIT_SUCCESS;
}
/*
int main(void) {
  int64_t error = EXIT_SUCCESS;
  int64_t number = 0;
  int64_t amountGoldbachSums = 0;

  while (scanf("%"SCNd64, &number) == 1) {
    bool negativeInput = number < 0 ? true : false;

    if (negativeInput) {
      number *= -1;
    }

    if (number < 0 || number > 5) {
      if (negativeInput) {
        printf("%"SCNd64, -number);
      } else {
        printf("%"SCNd64, number);
      }
      array_int64_t goldbach_sums;
      error = array_int64_init(&goldbach_sums);
      if (error == EXIT_SUCCESS) {
        error = goldbach(number, &goldbach_sums);
        if (error == EXIT_SUCCESS) {
          if (is_even_number(number)) {
            amountGoldbachSums = array_int64_getCount(&goldbach_sums) / 2;
          } else {
            amountGoldbachSums = array_int64_getCount(&goldbach_sums) / 3;
          }

          printf("%s""%"SCNd64"%s", ": " , amountGoldbachSums, " sums");
          if (negativeInput) {
            printf("%s", ": ");
            print_goldbach_sums(number, &goldbach_sums);
          }
          printf("%s", "\n");

          array_int64_destroy(&goldbach_sums);
        } else {
          fprintf(stderr, "error: could not calculate goldbach sums\n");
        }
      } else {
        fprintf(stderr, "error: could not init goldbach_sums.\n");
      }
    } else {
      if (negativeInput) {
        printf("%"SCNd64 "%s", -number, ": NA\n");
      } else {
        printf("%"SCNd64 "%s", number, ": NA\n");
      }
    }
  }

  return error;
}*/

/**
 * @brief Constructs an array with the goldbach sums
 * @details Verifies if the number is even or odd, then calls
 * a conjecture to create the array of goldbach sums
 * @param number The number wich goldbach sums will be find
 * @param goldbach_sums pointer to the array with the goldbach sums
 * @return Returns an integer to check errors
 */
int goldbach_pthread_calculate_goldbach(goldbach_pthread_t* goldbach_pthread, int64_t number, array_int64_t * goldbach_sums) {
  int error = EXIT_SUCCESS;

  if (is_even_number(number)) {
    error = goldbach_pthread_strong_conjecture(goldbach_pthread, number, goldbach_sums);
  } else {
    error = goldbach_pthread_weak_conjecture(goldbach_pthread, number, goldbach_sums);
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

int goldbach_pthread_create_threads(goldbach_pthread_t* goldbach_pthread, char* argv[]){

  return EXIT_SUCCESS;
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