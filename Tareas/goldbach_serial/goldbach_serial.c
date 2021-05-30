// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_int64.h"

array_int64_t eratostenes_sieve(int64_t maxNum);
array_int64_t * goldbach(int64_t number, array_int64_t * goldbach_sums, array_int64_t primes);
array_int64_t * goldbach_strong_conjecture(int64_t number, array_int64_t * goldbach_sums, array_int64_t primes);
array_int64_t * goldbach_weak_conjecture(int64_t number, array_int64_t * goldbach_sums, array_int64_t primes);
void print_goldbach_sums(int64_t number, array_int64_t * goldbachSums);
bool is_even_number(int64_t number);

/**
 * @return zero if succeed
 */
int main(void) {
  int64_t number = 0;
  int64_t maxPrime = 5;//***********************
  int64_t amountGoldbachSums = 0;

  array_int64_t primes;
  array_int64_init(&primes);
  primes = eratostenes_sieve(maxPrime);
  array_int64_print(&primes);//////////////////////////////////////////
  while (scanf("%"SCNd64, &number) == 1) {
    //********************************************************
    bool negativeInput = number < 0 ? true : false;
    
    if(negativeInput){
      number *= -1;
    }

    if(number > maxPrime){
      array_int64_destroy(&primes);
      array_int64_init(&primes);
      primes = eratostenes_sieve(number);
      array_int64_print(&primes);////////////////////////
      maxPrime = number;
    }
    //********************************************************
    
    if (number < 0 || number > 5) {
      if (negativeInput) {
        printf("%"SCNd64, -number);
      }else{
        printf("%"SCNd64, number);
      }
      array_int64_t goldbach_sums;
      array_int64_init(&goldbach_sums);
      goldbach(number, &goldbach_sums, primes); //******************************

      //*******************************************************************
      if (is_even_number(number)) {
        amountGoldbachSums = array_int64_getCount(&goldbach_sums) / 2;
      } else {
        amountGoldbachSums = array_int64_getCount(&goldbach_sums) / 3;
      }
      //******************************************************************
      
      printf("%s""%"SCNd64"%s", ": " , amountGoldbachSums, " sums");
      if (negativeInput){
        printf("%s", ": ");
        print_goldbach_sums(number, &goldbach_sums);
      }
      printf("%s", "\n");
      
      //free(goldbach_sums);
      array_int64_destroy(&goldbach_sums);
    
    } else {
      if (negativeInput) {
        printf("%"SCNd64 "%s", -number, ": NA\n");
      }else{
        printf("%"SCNd64 "%s", number, ": NA\n");
      }
    }
  }
  //free(primes);
  array_int64_destroy(&primes);

  return EXIT_SUCCESS;
}
/**
 * @brief Creates and returns an array of prime numbers 
 * @details Uses the Eratostenes sieve to fill an array with prime numbers
 * @param maxNum The highest amount of numbers that the array can contain
 * @return a pointer to an array of prime numbers
 */
//int64_t * eratostenes_sieve(int64_t maxNum) {
array_int64_t eratostenes_sieve(int64_t maxNum) { 
  
  array_int64_t primes;
  array_int64_init(&primes);
  
  int64_t amountPrimes = 0;
  int64_t prime = 0;
  int64_t * nums = calloc(maxNum, sizeof(int64_t));

  for (int64_t index = 2; index < maxNum; index++) {
    if (nums[index] != 1 || index == 2) {
      array_int64_append(&primes, index);
      for (prime = 2; (prime * index) <= maxNum; prime++) {
        if (prime * index < maxNum) {
          nums[(prime * index)] = 1;
        }
      }
      amountPrimes++;
    }
  }
  free(nums);

  return primes;
}


/**
 * @brief Returns an array with the amount of goldbach sums and/or 
 * the goldbach sums
 * @details Verifies if the number is even or odd, then calls
 * a conjecture to create the array of goldbach sums
 * @param number The number wich goldbach sums will be find
 * @param primes The vector with the prime numbers
 * @return Rearray_int64_tturns a pointer to an array of the goldbach sums of a number
 */
array_int64_t * goldbach(int64_t number, array_int64_t * goldbach_sums, array_int64_t primes) {
  
  //****************************
  if (is_even_number(number)){
    goldbach_strong_conjecture(number, goldbach_sums, primes);
  } else {
    goldbach_weak_conjecture(number, goldbach_sums, primes);
  }

  return goldbach_sums;
}

/**
 * @brief Returns an array with the amount of goldbach sums and/or 
 * the goldbach sums
 * @details The conjecture for even numbers, the first position of the array
 * is the amount of goldbach sums of the number. the next positions are the
 * numbers that conform the sums (they will be accessed in pairs to print)
 * @param number The number wich goldbach sums will be find
 * @param primes The vector with the prime numbers
 * @return Returns a pointer to an array of the goldbach sums of a number
 */
array_int64_t * goldbach_strong_conjecture(int64_t number, array_int64_t * goldbach_sums, array_int64_t primes) {
  int64_t half = number / 2;

  bool lastPrime_i = false;

  for (int i = 0; array_int64_getElement(&primes, i) <= half && !lastPrime_i; i++) {
    bool lastPrime_j = false;
    int64_t num1 = array_int64_getElement(&primes, i);
    if (num1 != 0) {

      for (int j = i; array_int64_getElement(&primes, j) <= number && !lastPrime_j; j++) {
        //int64_t num1 = array_int64_getElement(&primes, i);
        int64_t num2 = array_int64_getElement(&primes, j);
        if(num2 != 0){
          if(num1 + num2 == number /*&& num1 != 0 && num2 != 0*/){  
            array_int64_append(goldbach_sums, num1);
            array_int64_append(goldbach_sums, num2);
          }
        } else {
          lastPrime_j = true;
        }
      }
    } else {
      lastPrime_i = true;
    }
  }  

  return goldbach_sums;
}
/**
 * @brief Returns an array with the amount of goldbach sums and/or 
 * the goldbach sums
 * @details The conjecture for odd numbers, the first position of the array
 * is the amount of goldbach sums of the number. the next positions are the
 * numbers that conform the sums (they will be accessed int trios to print)
 * @param number The number wich goldbach sums will be find
 * @param primes The vector with the prime numbers
 * @return Returns a pointer to an array of the goldbach sums of a number
 */
array_int64_t * goldbach_weak_conjecture(int64_t number, array_int64_t * goldbach_sums, array_int64_t primes){
  int64_t half = number / 2;

  bool lastPrime_i = false;

  for (int i = 0; array_int64_getElement(&primes, i) <= half && !lastPrime_i; i++) {
    bool lastPrime_j = false;
    int64_t num1 = array_int64_getElement(&primes, i);
    
    if (num1 != 0) {
      for (int j = i; array_int64_getElement(&primes, j) <= number && !lastPrime_j; j++) {
        bool lastPrime_k = false;
        int64_t num2 = array_int64_getElement(&primes, j);
      
        if (num2 != 0) {
          for (int k = j; array_int64_getElement(&primes, k) <= number && !lastPrime_k; k++) {
            //int64_t num1 = array_int64_getElement(&primes, i);
            //int64_t num2 = array_int64_getElement(&primes, j);
            int64_t num3 = array_int64_getElement(&primes, k);
            if (num3 != 0) {
              if (num1 + num2 + num3 == number /*&& num1 != 0 && num2 != 0 && num3 != 0*/) {
                array_int64_append(goldbach_sums, num1);
                array_int64_append(goldbach_sums, num2);
                array_int64_append(goldbach_sums, num3);
              }
            } else {
              lastPrime_k = true;
            }
          }  
        }   else {
          lastPrime_j = true;
        }
      }
    } else {
      lastPrime_i = true;
    }
  }
  return goldbach_sums;
}
void print_goldbach_sums(int64_t number, array_int64_t * goldbach_sums) {
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
 */
bool is_even_number(int64_t number) {
  return number % 2 == 0;
}
