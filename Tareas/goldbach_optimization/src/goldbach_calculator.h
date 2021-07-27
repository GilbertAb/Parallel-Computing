// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>

#ifndef TAREAS_GOLDBACH_OPTIMIZATION_GOLDBACH_CALCULATOR_H
#define TAREAS_GOLDBACH_OPTIMIZATION_GOLDBACH_CALCULATOR_H

#include <assert.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "array_int64.h"
#include "common.h"
#include "goldbach_sums_array.h"

/**
 * @brief constructs an array with the goldbach sums.
 * @details verifies if the number is even or odd, then calls
 * a conjecture to create the array of goldbach sums.
 * @param data (goldbach_pthread) struct that contains the shared data of the
 * threads.
 * @return null.
 */
void* goldbach_calculator_calculate_goldbach(void* data);

/**
 * @brief constructs an array with the goldbach sums.
 * @details the conjecture for even numbers, the first position of the array
 * is the amount of goldbach sums of the number. the next positions are the
 * numbers that conform the sums (they will be accessed in pairs to print).
 * @param goldbach_pthread struct that contains the shared data of the threads.
 * @param number number whose goldbach sums will be calculated.
 * @param index_number index of number to be calculated.
 * @return an integer to check errors.
 */
int goldbach_calculator_strong_conjecture(goldbach_pthread_t* goldbach_pthread,
  int64_t number, int64_t index_number);

/**
 * @brief constructs an array with the goldbach sums
 * @details the conjecture for odd numbers, the first position of the array
 * is the amount of goldbach sums of the number. the next positions are the
 * numbers that conform the sums (they will be accessed int trios to print).
 * @param goldbach_pthread struct that contains the shared data of the threads.
 * @param number number whose goldbach sums will be calculated.
 * @param index_number index of number to be calculated.
 * @return an integer to check errors.
 */
int goldbach_calculator_weak_conjecture(goldbach_pthread_t* goldbach_pthread,
  int64_t number, int64_t index_number);

/**
 * @brief returns if a number is a prime number
 * @details determines if a number is a prime number by checking if it
 * has more than two divisors
 * @param number the number
 * @return true if a number is a prime number
 */
bool isPrime(int64_t number);

#endif  // TAREAS_GOLDBACH_OPTIMIZATION_GOLDBACH_CALCULATOR_H
