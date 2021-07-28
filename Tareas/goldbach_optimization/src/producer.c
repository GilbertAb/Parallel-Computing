// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
// Simulates a producer and a consumer that share a unbounded buffer

#include <stdio.h>

#include "common.h"
#include "producer.h"

#include <stdio.h>


void* produce(void* data) {
  printf("produce");
  private_data_t* private_data = (private_data_t*)data;
  //goldbach_pthread_t* goldbach_pthread = (goldbach_pthread_t*)data;
  goldbach_pthread_t* goldbach_pthread = private_data->goldbach_pthread;
  while (true) {
    sem_wait(&goldbach_pthread->can_access_next_unit);
    // unit_count = numbers_count
    if (goldbach_pthread->next_unit >= goldbach_pthread->unit_count-1) {
      sem_post(&goldbach_pthread->can_access_next_unit);
      break;
    }
    // index of the unit/goldbach_number to produce
    //int64_t my_unit = ++goldbach_pthread->next_unit; // tal vez con post-incremento no hace falta hacer my_unit-1
    int64_t my_unit = goldbach_pthread->next_unit++;
    sem_post(&goldbach_pthread->can_access_next_unit);

    // Produce
    goldbach_number_t goldbach_number;
    //goldbach_number.number = array_int64_getElement(goldbach_pthread->numbers, my_unit-1); // race condition
    //goldbach_number.index = my_unit - 1;
    goldbach_number.number = array_int64_getElement(goldbach_pthread->numbers, my_unit); // race condition
    goldbach_number.index = my_unit;
    goldbach_number_queue_enqueue(&goldbach_pthread->queue, goldbach_number);
    //printf("Produced %zu\n", my_unit);
    sem_post(&goldbach_pthread->can_consume);
  }

  return NULL;
}
