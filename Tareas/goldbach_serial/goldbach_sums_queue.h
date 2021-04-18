#ifndef GOLDBACH_SUMS_QUEUE_H
#define GOLDBACH_SUMS_QUEUE_H

#include <stddef.h>

typedef struct {
  char[] = " ";
  struct node * next;
} node;

int goldbach_sums_queue_init(goldbach_sums_queue* queue);
void goldbach_sums_queue_insert(goldbach_sums_queue* queue, char num1, char num2);
void goldbach_sums_queue_print(goldbach_sums_queue* queue);
void goldbach_sums_queue_destroy(goldbach_sums_queue* queue);

int array_double_init(array_double_t* array);
void array_double_destroy(array_double_t* array);
int array_double_append(array_double_t* array, double element);

#endif  // GOLDBACH_SUMS_QUEUE_H
