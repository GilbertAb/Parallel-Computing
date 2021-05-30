// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_int64.h"

/*#define MAXPRIMES 1000000
#define MAXNUMBERS 1000000*/

//int64_t * eratostenes_sieve(int64_t maxNum);
array_int64_t eratostenes_sieve(int64_t maxNum);
//int64_t* goldbach(int64_t * number, int64_t * primes);
array_int64_t * goldbach(int64_t number, array_int64_t * goldbach_sums, array_int64_t primes);
//int64_t* goldbach_strong_conjecture(int64_t number, int64_t * primes);
array_int64_t * goldbach_strong_conjecture(int64_t number, array_int64_t * goldbach_sums, array_int64_t primes);
//int64_t* goldbach_weak_conjecture(int64_t number, int64_t * primes);
array_int64_t * goldbach_weak_conjecture(int64_t number, array_int64_t * goldbach_sums, array_int64_t primes);
void print_goldbach_sums(int64_t number, array_int64_t * goldbachSums);
bool is_even_number(int64_t number);

/**
 * @return zero if succeed
 */
int main(void) {
  int64_t number = 0;
  int64_t maxPrime = 0;//***********************
  int64_t amountGoldbachSums = 0;
  //int64_t * primes = eratostenes_sieve(MAXPRIMES);//
  //array_int64 primes = eratostenes_sieve();
  array_int64_t primes;
  array_int64_init(&primes);
  primes = eratostenes_sieve(number);
  while (scanf("%"SCNd64, &number) == 1) {
    
    //********************************************************
    if(number > maxPrime){
      array_int64_destroy(&primes);
      array_int64_init(&primes);
      primes = eratostenes_sieve(number);
      
      maxPrime = number;
    }
    //********************************************************
    
    if (number < 0 || number > 5) {
      printf("%"SCNd64, number);
      
      //int64_t * goldbach_sums = goldbach(&number, primes);
      array_int64_t goldbach_sums;
      array_int64_init(&goldbach_sums);
      goldbach(number, &goldbach_sums, primes); //******************************

      //*******************************************************************
      if (is_even_number(number)) {
        amountGoldbachSums = array_int64_getCount(&goldbach_sums) / 2;
        printf("%"SCNd64, amountGoldbachSums);
      } else {
        amountGoldbachSums = array_int64_getCount(&goldbach_sums) / 3;
      }
      //******************************************************************
      
      //prinarray_int64_ttf("%s""%"SCNd64"%s", ": " , goldbach_sums[0], " sums");
      printf("%s""%"SCNd64"%s", ": " , amountGoldbachSums, " sums");
      if (number < 0) {
        printf("%s", ": ");
        print_goldbach_sums(number, &goldbach_sums);
      }
      printf("%s", "\n");
      
      //free(goldbach_sums);
      array_int64_destroy(&goldbach_sums);
    
    } else {
      printf("%"SCNd64 "%s", number, ": NA\n");
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
  //int64_t * primes = calloc(MAXPRIMES, sizeof(int64_t));
  
  array_int64_t primes;
  array_int64_init(&primes);
  
  int64_t amountPrimes = 0;
  int64_t prime = 0;
  int64_t * nums = calloc(maxNum, sizeof(int64_t));

  for (int64_t index = 2; index < maxNum; index++) {
    if (nums[index] != 1 || index == 2) {
      //primes[amountPrimes] = index;
      array_int64_append(&primes, index);
      for (prime = 2; (prime * index) <= maxNum; prime++) {
        if (prime * index < maxNum) {
          nums[(prime * index)] = 1;
        }
      }
      amountPrimes++;
    }
  }
  //free(nums);
  array_int64_destroy(&primes);

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
//int64_t* goldbach(int64_t * number, int64_t * primes) {
array_int64_t * goldbach(int64_t number, array_int64_t * goldbach_sums, array_int64_t primes) {
  //int64_t* goldbach;
  
  //****************************
  if (is_even_number(number)){
    goldbach_strong_conjecture(number, goldbach_sums, primes);
  } else {
    //goldbach = goldbach_weak_conjecture(number, primes);
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
//int64_t* goldbach_strong_conjecture(int64_t number, int64_t * primes) {
array_int64_t * goldbach_strong_conjecture(int64_t number, array_int64_t * goldbach_sums, array_int64_t primes) {
  int64_t n = number / 2;
  //int64_t amountSums = 0;
  //int64_t countNumbers = 1;  // First pos of goldbachSums is the amount of sums
  //int64_t * goldbachSums = calloc(MAXNUMBERS, sizeof(int64_t));

  /*for (int i = 0; i < MAXNUMBERS; i++) {
    goldbachSums[i] = 0;
  }*/

  if (number < 0) {
    number *= -1;
    n *= -1;
  }

  for (int i = 0; i < n; i++) {
    for (int j = i; j < number; j++) {
      //if (primes[i] + primes[j] == number) {
      int64_t num1 = array_int64_getElement(&primes, i);
      int64_t num2 = array_int64_getElement(&primes, j);
      if(num1 + num2 == number){  
        /*++amountSums;
        goldbachSums[countNumbers++] = primes[i];
        goldbachSums[countNumbers++] = primes[j];*/
        array_int64_append(goldbach_sums, num1);
        array_int64_append(goldbach_sums, num2);
      }
    }
  }
  //goldbachSums[0] = amountSums;

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
//int64_t* goldbach_weak_conjecture(int64_t number, int64_t * primes) {
array_int64_t * goldbach_weak_conjecture(int64_t number, array_int64_t * goldbach_sums, array_int64_t primes){
  int64_t n = number / 2;
  //int64_t countNumbers = 1;  // First pos of goldbachSums is the amount of sums
  //int64_t * goldbachSums = calloc(MAXNUMBERS, sizeof(int64_t));

  /*for (int i = 0; i < MAXNUMBERS; i++) {
    goldbachSums[i] = 0;
  }*/

  if (number < 0) {
    number *= -1;
    n *= -1;
  }

  for (int i = 0; i < n; i++) {
    for (int j = i; j < number; j++) {
      for (int k = j; k < number; k++) {
        int64_t num1 = array_int64_getElement(&primes, i);
        int64_t num2 = array_int64_getElement(&primes, j);
        int64_t num3 = array_int64_getElement(&primes, k);

        if (num1 + num2 + num3 == number) {
          /*++amountSums;
          goldbachSums[countNumbers++] = primes[i];
          goldbachSums[countNumbers++] = primes[j];
          goldbachSums[countNumbers++] = primes[k];
          */
          array_int64_append(goldbach_sums, num1);
          array_int64_append(goldbach_sums, num2);
          array_int64_append(goldbach_sums, num3);
        }
      }
    }
  }
    //goldbachSums[0] = amountSums;
  return goldbach_sums;
}
void print_goldbach_sums(int64_t number, array_int64_t * goldbach_sums) {
  int counter = 1;
  int counterMax = 3;
  //int index = 1;  // First position of goldbachSums is the amount of sums
  int index = 0;

  if (is_even_number(number)) {
    counterMax = 2;
  }

  //while (goldbachSums[index] != 0) {
  while (index < array_int64_getCount(goldbach_sums)) {
    //printf("%"SCNd64, goldbachSums[index]);
    printf("%"SCNd64, array_int64_getElement(goldbach_sums, index));
    if (counter < counterMax) {
      printf("%s", " + ");
      ++counter;
    } else {
      if (array_int64_getElement(goldbach_sums, index + 1) == array_int64_getCount(goldbach_sums)) {
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
