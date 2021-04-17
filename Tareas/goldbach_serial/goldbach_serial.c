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
    fprintf(output, "%"SCNd64"\n", goldbach(&number));
  }
  
  return EXIT_SUCCESS;
}

int64_t goldbach(int64_t * number) {
  int64_t goldbach= *number + *number;
  
  //int * primesVector = calculatePrimeNumbers();
  
  //if(*number )


  return goldbach;
}

