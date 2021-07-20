// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>

#ifndef TAREAS_GOLDBACH_PTHREAD_BLOCK_MAPPING_H_
#define TAREAS_GOLDBACH_PTHREAD_BLOCK_MAPPING_H_

#include <stdlib.h>

/**
 * @brief returns the start index of a block mapping.
 * @details calculates and returns the start index of a block mapping.
 * @param thread_number the number of thread which index will be assigned.
 * @param total_numbers total of numbers to be assigned between all threads.
 * @param thread_count the total number of threads.
 * @return the start index of a block mapping.
 */
int block_mapping_start(int64_t thread_number, int64_t total_numbers,
  int64_t thread_count);

/**
* @brief returns the finish index of a block mapping.
* @details calculates and returns the finish index of a block mapping.
* @param thread_number the number of thread which index will be assigned.
* @param total_numbers total of numbers to be assigned between all threads.
* @param thread_count the total number of threads.
* @return the finish index of a block mapping.
*/
int block_mapping_finish(int64_t thread_number, int64_t total_numbers,
  int64_t thread_count);

#endif  // TAREAS_GOLDBACH_PTHREAD_BLOCK_MAPPING_H_
