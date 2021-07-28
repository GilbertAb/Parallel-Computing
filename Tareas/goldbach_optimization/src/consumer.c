// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>
// Simulates a producer and a consumer that share a unbounded buffer
// Consumes a goldbach_number struct

#include "consumer.h"

void* consume(void* data) {
  private_data_t* private_data = (private_data_t*)data;
  goldbach_pthread_t* goldbach_pthread = private_data->goldbach_pthread;

  while (true) {
    sem_wait(&goldbach_pthread->can_access_consumed_count);
    if (goldbach_pthread->consumed_count > goldbach_pthread->unit_count) {
      sem_post(&goldbach_pthread->can_access_consumed_count);
      break;
    }
    ++goldbach_pthread->consumed_count;
    sem_post(&goldbach_pthread->can_access_consumed_count);

    sem_wait(&goldbach_pthread->can_consume);

    // Consume
    goldbach_number_queue_dequeue(&goldbach_pthread->queue,
      &private_data->goldbach_number);
    goldbach_calculator_calculate_goldbach(private_data);
  }

  return NULL;
}
