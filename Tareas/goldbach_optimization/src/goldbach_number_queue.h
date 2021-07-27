// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
// Simulates a producer and a consumer that share a bounded buffer

#ifndef GOLDBACH_NUMBER_QUEUE_H
#define GOLDBACH_NUMBER_QUEUE_H

#include <pthread.h>
#include <stdbool.h>
//#include "common.h"

typedef struct  {
  int64_t number;
  int64_t index;
} goldbach_number_t;

typedef struct goldbach_number_queue_node {
  goldbach_number_t data;
  struct goldbach_number_queue_node* next;
} goldbach_number_queue_node_t;

typedef struct {
  pthread_mutex_t can_access_queue;
  goldbach_number_queue_node_t* head;
  goldbach_number_queue_node_t* tail;
} goldbach_number_queue_t;

/**
 * ...
 * @remaks This subroutine is NOT thread-safe
 */
int goldbach_number_queue_init(goldbach_number_queue_t* queue);

int goldbach_number_queue_destroy(goldbach_number_queue_t* queue);

bool goldbach_number_queue_is_empty(goldbach_number_queue_t* queue);
int goldbach_number_queue_enqueue(goldbach_number_queue_t* queue,
  const goldbach_number_t data);
int goldbach_number_queue_dequeue(goldbach_number_queue_t* queue,
  goldbach_number_t* data);
void goldbach_number_queue_clear(goldbach_number_queue_t* queue);

#endif  // GOLDBACH_NUMBER_QUEUE_H
