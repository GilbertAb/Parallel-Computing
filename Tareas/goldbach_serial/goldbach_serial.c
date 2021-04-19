#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#define MAXPRIMES 1000000

int64_t * eratostenes_sieve(int64_t maxNum);
int64_t* goldbach(int64_t * number, int64_t * primes);
int64_t* goldbach_strong_conjecture(int64_t number, int64_t * primes);
int64_t* goldbach_weak_conjecture(int64_t number, int64_t * primes);
void * print_goldbach_sums(int64_t number, int64_t * goldbachSums);
bool is_even_number(int64_t number);

int main(void) {
  int64_t number = 0;
  int64_t * primes = eratostenes_sieve(MAXPRIMES);
  /*int64_t sizePrimes = sizeof(primes) / sizeof(int64_t);
  printf("%"SCNd64"\n", sizePrimes);*/
  while(scanf("%"SCNd64, &number) == 1){
	if((number > 5 || number < 0)){
      printf("%"SCNd64"\n", number);
      /*if(number > primes[sizePrimes - 1]){
        primes = eratostenes_sieve(number);
      }*/
      int64_t * goldbach_sums = goldbach(&number, primes);
      
    }else{
      printf("%"SCNd64 "%s", number,": NA\n");
    }
    
  }
  return EXIT_SUCCESS;
}

int64_t * eratostenes_sieve(int64_t maxNum) {   
  //int64_t * primes = malloc(sizeof(int64_t) * MAXPRIMES);
  int64_t * primes = calloc(MAXPRIMES, sizeof(int64_t));

  int64_t amountPrimes = 0;
  int64_t prime = 0;
  int64_t nums[maxNum];

  for(int index = 2;index <= maxNum; index++) {
    if(nums[index] != 1 || index == 2) {
      primes[amountPrimes] = index;
      for(prime = 2;(prime * index) <= maxNum; prime++) {
        nums[(prime * index)] = 1;
      }
      amountPrimes++;
    }
  }    
  return primes;
}

int64_t* goldbach(int64_t * number, int64_t * primes) {
  int64_t* goldbach;
  
  if(/**number % 2 == 0*/ is_even_number(*number)){
    goldbach = goldbach_strong_conjecture(*number, primes);
  }else{
    goldbach = goldbach_weak_conjecture(*number, primes);
  }
  
  eratostenes_sieve(MAXPRIMES);

  return goldbach;
}

// Para pares
int64_t* goldbach_strong_conjecture(int64_t number, int64_t * primes) {
  int64_t* a; 
  bool negative = false;
  int64_t n = number / 2;
  int64_t amountSums = 0;
   
  if(number < 0){
    negative = true;
    number *= -1;
    n *= -1; 
  }      
  
  for(int i = 0; i < n; i++){
    for(int j = i; j < number; j++){
      if(primes[i] + primes[j] == number){
        ++amountSums;
      }      
    }  
  }
  printf("%"SCNd64 "%s" "%"SCNd64 "%s", number," sums: ", amountSums,"\n");
  
  return a;
}
int64_t* goldbach_weak_conjecture(int64_t number, int64_t * primes) {
  int64_t* a;
  bool negative = false;
  int64_t n = number / 2;
  int64_t amountSums = 0;
   
  if(number < 0){
    negative = true;
    number *= -1;
    n *= -1; 
  }
  
  for(int i = 0; i < n; i++){
    for(int j = i; j < number; j++){
      for(int k = j; k < number; k++){
        if(primes[i] + primes[j] + primes[k] == number){
          ++amountSums;
        }
      }      
    }  
  }
  printf("%"SCNd64 "%s" "%"SCNd64 "%s", number," sums: ", amountSums,"\n");
  
  
  return a;
}

void * print_goldbach_sums(int64_t number, int64_t * goldbachSums){
  int64_t size = 10;
  int counter = 1;
  int counterMax = 3;
  
  if(is_even_number(number)){
    counterMax = 2;
  }
  
  for(int index = 0; index < size; index++){
      printf("%"SCNd64, goldbachSums[index]);
      if(counter < counterMax){
        printf("%s", " + ");
        ++counter;
      }else{
        if(index + 1 != size){
          printf("%s", ", ");
          counter = 0;   
	    } 
      }
  }
}

bool is_even_number(int64_t number){
  return number % 2 == 0;
}