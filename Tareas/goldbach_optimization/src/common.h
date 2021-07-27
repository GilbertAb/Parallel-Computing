// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
// Simulates a producer and a consumer that share a bounded buffer

#ifndef COMMON_H
#define COMMON_H

// @see `man feature_test_macros`
// #define _DEFAULT_SOURCE

#include <semaphore.h>
#include <unistd.h>

#include "array_int64.h"
#include "goldbach_sums_array.h"
#include "goldbach_number_queue.h"

// Shared data
typedef struct goldbach_pthread {
  array_int64_t* numbers;
  int64_t unit_count;
  goldbach_number_queue_t queue;
  // thread_count
  int64_t consumer_count;
  sem_t can_consume;
  sem_t can_access_next_unit;
  int64_t next_unit;
  sem_t can_access_consumed_count;
  int64_t consumed_count;
  goldbach_sums_array_t** goldbach_sums;
} goldbach_pthread_t;

typedef struct  {
  goldbach_number_t goldbach_number;
  int64_t thread_number;
  goldbach_pthread_t* goldbach_pthread;
} private_data_t;

#endif  // COMMON_H
