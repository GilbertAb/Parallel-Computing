#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXPRIMES 1000000

char* goldbach(int64_t * number, int64_t * primes);
char* goldbach_strong_conjecture(int64_t * primes);
char* goldbach_weak_conjecture(int64_t * primes);

int64_t * eratostenes_sieve(int64_t maxNum);

int main(void) {
  FILE* input = stdin;
  FILE* output = stdout;
  int64_t number = 0;
  
  int64_t * primes = eratostenes_sieve(MAXPRIMES);
  while(fscanf(input, "%"SCNd64, &number) == 1){
	if((number > 5 || number < 0)){
      fprintf(output, "%"SCNd64"\n", number, goldbach(&number, primes));
    }else{
      fprintf(output, "%"SCNd64 "%s", number,": NA\n");
    }
    
  }
  return EXIT_SUCCESS;
}

char* goldbach(int64_t * number, int64_t * primes) {
  char* goldbach= "";
  
  if(*number % 2 == 0){
    goldbach = goldbach_strong_conjecture(primes);
  }else{
    goldbach = goldbach_weak_conjecture(primes);
  }
  
  eratostenes_sieve(MAXPRIMES);

  return goldbach;
}

char* goldbach_strong_conjecture(int64_t * primes){
  char* a = "";
}
char* goldbach_weak_conjecture(int64_t * primes){
  char* a = "";
}
int64_t * eratostenes_sieve(int64_t maxNum){
   
  int64_t * primes = malloc(sizeof(int64_t) * MAXPRIMES);
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
