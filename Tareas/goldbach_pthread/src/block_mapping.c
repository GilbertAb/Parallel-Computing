// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>

#include "block_mapping.h"

int block_mapping_start(int64_t thread_number, int64_t total_numbers,
  int64_t thread_count) {
  int64_t mod = total_numbers % thread_count;
  int64_t min = thread_number < mod ? thread_number : mod;
  return thread_number * (total_numbers / thread_count) + min;
}

int block_mapping_finish(int64_t thread_number, int64_t total_numbers,
  int64_t thread_count) {
  return block_mapping_start(thread_number + 1, total_numbers, thread_count);
}
