// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#define MAXPRIMES 1000000
#define MAXNUMBERS 100

int64_t * eratostenes_sieve(int64_t maxNum);
int64_t* goldbach(int64_t * number, int64_t * primes);
int64_t* goldbach_strong_conjecture(int64_t number, int64_t * primes);
int64_t* goldbach_weak_conjecture(int64_t number, int64_t * primes);
void print_goldbach_sums(int64_t number, int64_t * goldbachSums);
bool is_even_number(int64_t number);

int main(void) {
  int64_t number = 0;
  int64_t * primes = eratostenes_sieve(MAXPRIMES);
  // int64_t sizePrimes = MAXPRIMES;
  printf("%"SCNd64"\n", sizeof(*primes));
  while (scanf("%"SCNd64, &number) == 1) {
    if ((number > 5 || number < 0)) {
      printf("%"SCNd64, number);
      /*if(number > primes[sizePrimes - 1]){
        primes = eratostenes_sieve(number);
      }*/
      int64_t * goldbach_sums = goldbach(&number, primes);
      printf("%s""%"SCNd64"%s", ": " , goldbach_sums[0], " sums");
      if (number < 0) {
        printf("%s", ": ");
        print_goldbach_sums(number, goldbach_sums);
      }
      printf("%s", "\n");
      free(goldbach_sums);
    } else {
      printf("%"SCNd64 "%s", number, ": NA\n");
    }
  }
  free(primes);
  return EXIT_SUCCESS;
}

int64_t * eratostenes_sieve(int64_t maxNum) {
  int64_t * primes = calloc(MAXPRIMES, sizeof(int64_t));

  int64_t amountPrimes = 0;
  int64_t prime = 0;
  int64_t * nums = calloc(maxNum, sizeof(int64_t));
  // int64_t nums[maxNum];
  /*for(int i = 0; i < maxNum; i++){
    nums[i] = 0;
  }*/
  for (int index = 2; index < maxNum; index++) {
    if (nums[index] != 1 || index == 2) {
      primes[amountPrimes] = index;
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

int64_t* goldbach(int64_t * number, int64_t * primes) {
  int64_t* goldbach;

  if (is_even_number(*number)) {
    goldbach = goldbach_strong_conjecture(*number, primes);
  } else {
    goldbach = goldbach_weak_conjecture(*number, primes);
  }

  return goldbach;
}

// Para pares
int64_t* goldbach_strong_conjecture(int64_t number, int64_t * primes) {
  int64_t n = number / 2;
  int64_t amountSums = 0;
  int64_t countNumbers = 1;  // First pos of goldbachSums is the amount of sums
  int64_t * goldbachSums = calloc(MAXNUMBERS, sizeof(int64_t));

  for (int i = 0; i < MAXNUMBERS; i++) {
    goldbachSums[i] = 0;
  }

  if (number < 0) {
    number *= -1;
    n *= -1;
  }

  for (int i = 0; i < n; i++) {
    for (int j = i; j < number; j++) {
      if (primes[i] + primes[j] == number) {
        ++amountSums;
        goldbachSums[countNumbers++] = primes[i];
        goldbachSums[countNumbers++] = primes[j];
      }
    }
  }
  goldbachSums[0] = amountSums;

  return goldbachSums;
}
int64_t* goldbach_weak_conjecture(int64_t number, int64_t * primes) {
  int64_t n = number / 2;
  int64_t amountSums = 0;
  int64_t countNumbers = 1;  // First pos of goldbachSums is the amount of sums
  int64_t * goldbachSums = calloc(MAXNUMBERS, sizeof(int64_t));

  for (int i = 0; i < MAXNUMBERS; i++) {
    goldbachSums[i] = 0;
  }

  if (number < 0) {
    number *= -1;
    n *= -1;
  }

  for (int i = 0; i < n; i++) {
    for (int j = i; j < number; j++) {
      for (int k = j; k < number; k++) {
        if (primes[i] + primes[j] + primes[k] == number) {
          ++amountSums;
          goldbachSums[countNumbers++] = primes[i];
          goldbachSums[countNumbers++] = primes[j];
          goldbachSums[countNumbers++] = primes[k];
        }
      }
    }
  }
  goldbachSums[0] = amountSums;

  return goldbachSums;
}

void print_goldbach_sums(int64_t number, int64_t * goldbachSums) {
  // int64_t size = 10;
  int counter = 1;
  int counterMax = 3;
  int index = 1;  // First position of goldbachSums is the amount of sums

  if (is_even_number(number)) {
    counterMax = 2;
  }
  while (goldbachSums[index] != 0) {
    printf("%"SCNd64, goldbachSums[index]);
    if (counter < counterMax) {
      printf("%s", " + ");
      ++counter;
    } else {
      if (goldbachSums[index + 1] != 0) {
        printf("%s", ", ");
      }
      counter = 1;
    }
    index++;
  }
}

bool is_even_number(int64_t number) {
  return number % 2 == 0;
}
