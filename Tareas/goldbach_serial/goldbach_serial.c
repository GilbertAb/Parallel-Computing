#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int64_t goldbach(int64_t * number);

int main(void) {
  FILE* input = stdin;
  FILE* output = stdout;
  int64_t number = 0;
  
  while(fscanf(input, "%"SCNd64, &number) == 1){
	if((number > 5 || number < 0)){
      fprintf(output, "%"SCNd64"\n", goldbach(&number));
    }else{
      fprintf(output, "%"SCNd64 "%s", number,": NA\n");
    }
    
  }
  return EXIT_SUCCESS;
}

int64_t goldbach(int64_t * number) {
  int64_t goldbach= 0;
  
  //for(int )
  
  //int * primesVector = calculatePrimeNumbers();
  
  //if(*number )


  return goldbach;
}

int64_t * calculatePrimeNumbers(int num){
  int64_t * primes = (int64_t*)malloc(sizeof(int64_t));
  int primesSize = sizeof(primes)/sizeof(int64_t);
  
  for(int index = 0; index < primesSize; index++){
    primes[index]=0;
  }
  
  
  return primes;
}
