// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
// Simulates a producer and a consumer that share a unbounded buffer

#include <stdio.h>

#include "common.h"
#include "goldbach_calculator.h"
#include "consumer.h"

#include <stdbool.h>
#include <stdio.h>

void* consume(void* data) {
  private_data_t* private_data = (private_data_t*)data;
  //goldbach_pthread_t* goldbach_pthread = (goldbach_pthread_t*)data;
  goldbach_pthread_t* goldbach_pthread = private_data->goldbach_pthread;

  while (true) {
    sem_wait(&goldbach_pthread->can_access_consumed_count);
    if (goldbach_pthread->consumed_count >/*=*/ goldbach_pthread->unit_count) {
      sem_post(&goldbach_pthread->can_access_consumed_count);
      break;
    }
    ++goldbach_pthread->consumed_count;
    sem_post(&goldbach_pthread->can_access_consumed_count);

    sem_wait(&goldbach_pthread->can_consume);

    goldbach_number_t goldbach_number; // = goldbach_number_queue_dequeue(&goldbach_pthread->queue, &value);
    goldbach_number_queue_dequeue(&goldbach_pthread->queue, &private_data->goldbach_number);
    //printf("\tConsumed %zu\n", value);
    //printf("Number %zu \n", private_data->goldbach_number.number);
    //printf("threadNumber %zu \n", private_data->thread_number);
    goldbach_calculator_calculate_goldbach(private_data);
    // Call goldbach_calculate
  }

  return NULL;
}
