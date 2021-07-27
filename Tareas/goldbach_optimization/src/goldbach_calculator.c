// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>

#include "goldbach_calculator.h"

void* goldbach_calculator_calculate_goldbach(void* data) {
  assert(data);
  const private_data_t* private_data = (private_data_t*)data;
  goldbach_pthread_t* goldbach_pthread = private_data->goldbach_pthread;
  // Calculate number sums
  goldbach_number_t goldbach_number = private_data->goldbach_number;
  int64_t number = goldbach_number.number;
  int64_t index = goldbach_number.index;
  // Change number to positive if it is negative
  if (number < 0) {
    number *= -1;
  }

  // TODO: index should be passed from goldbach_pthread
  // If number is smaller than 6, it doesn't have any goldbach sum
  if (number > 5) {
    if (number % 2 == 0) {
      goldbach_calculator_strong_conjecture(goldbach_pthread, number, index);
    } else {
      goldbach_calculator_weak_conjecture(goldbach_pthread, number, index);
    }
  }
  
  return NULL;
}

int goldbach_calculator_strong_conjecture(goldbach_pthread_t* goldbach_pthread,
  int64_t number, int64_t index_number) {
  assert(goldbach_pthread);
  int error = EXIT_SUCCESS;

  for (int64_t num1 = 2, num2 = number - 2; num1 <= num2 && !error;
    ++num1, --num2) {
    if (isPrime(num1) && isPrime(num2)) {
      if (num1 + num2 == number) {
        error = goldbach_sums_array_append(goldbach_pthread
          ->goldbach_sums[index_number], num1);
        if (error) {
          break;
        }
        error = goldbach_sums_array_append(goldbach_pthread
          ->goldbach_sums[index_number], num2);
        if (error) {
          break;
        }
      }
    }
  }
  return error;
}

int goldbach_calculator_weak_conjecture(goldbach_pthread_t* goldbach_pthread,
  int64_t number, int64_t index_number) {
  assert(goldbach_pthread);
  int error = EXIT_SUCCESS;

  for (int start = 2, last = number - start; start <= last; start++, last--) {
    for (int medium = start, last_2 = last - medium; medium <= last_2;
      medium++, last_2--) {
      if (start + medium + last_2 == number && isPrime(start) &&
        isPrime(medium) && isPrime(last_2)) {
        error = goldbach_sums_array_append(goldbach_pthread
            ->goldbach_sums[index_number], start);;
        if (error) {
          break;
        }
        error = goldbach_sums_array_append(goldbach_pthread
            ->goldbach_sums[index_number], medium);
        if (error) {
          break;
        }
        error = goldbach_sums_array_append(goldbach_pthread
            ->goldbach_sums[index_number], last_2);
        if (error) {
          break;
        }
      }
    }
  }
  return error;
}

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
