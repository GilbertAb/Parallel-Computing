// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
// Implements a thread-safe queue

#include <assert.h>
#include <stdlib.h>

#include "goldbach_number_queue.h"

void goldbach_number_queue_remove_first_unsafe(goldbach_number_queue_t* queue);
bool goldbach_number_queue_is_empty_unsafe(const
  goldbach_number_queue_t* queue);

int goldbach_number_queue_init(goldbach_number_queue_t* queue) {
  assert(queue);
  queue->head = NULL;
  queue->tail = NULL;
  return pthread_mutex_init(&queue->can_access_queue, NULL);
}

int goldbach_number_queue_destroy(goldbach_number_queue_t* queue) {
  goldbach_number_queue_clear(queue);
  return pthread_mutex_destroy(&queue->can_access_queue);
}

bool goldbach_number_queue_is_empty_unsafe(const
  goldbach_number_queue_t* queue) {
  assert(queue);
  return queue->head == NULL;
}

bool goldbach_number_queue_is_empty(goldbach_number_queue_t* queue) {
  assert(queue);
  pthread_mutex_lock(&queue->can_access_queue);
  bool result = goldbach_number_queue_is_empty_unsafe(queue);
  pthread_mutex_unlock(&queue->can_access_queue);
  return result;
}

int goldbach_number_queue_enqueue(goldbach_number_queue_t* queue,
  const goldbach_number_t data) {
  assert(queue);
  int error = EXIT_SUCCESS;

  goldbach_number_queue_node_t* new_node = (goldbach_number_queue_node_t*)
    calloc(1, sizeof(goldbach_number_queue_node_t));

  if (new_node) {
    new_node->data = data;

    pthread_mutex_lock(&queue->can_access_queue);
    if (queue->tail) {
      queue->tail = queue->tail->next = new_node;
    } else {
      queue->head = queue->tail = new_node;
    }
    pthread_mutex_unlock(&queue->can_access_queue);
  } else {
    error = EXIT_FAILURE;
  }

  return error;
}

int goldbach_number_queue_dequeue(goldbach_number_queue_t* queue,
  goldbach_number_t* data) {
  assert(queue);
  int error = 0;

  pthread_mutex_lock(&queue->can_access_queue);
    if (!goldbach_number_queue_is_empty_unsafe(queue)) {
      if (data) {
        *data = queue->head->data;
      }
      goldbach_number_queue_remove_first_unsafe(queue);
    } else {
      error = EXIT_FAILURE;
    }
  pthread_mutex_unlock(&queue->can_access_queue);

  return error;
}

void goldbach_number_queue_remove_first_unsafe(goldbach_number_queue_t* queue) {
  assert(queue);
  assert(!goldbach_number_queue_is_empty_unsafe(queue));
  goldbach_number_queue_node_t* node = queue->head;
  queue->head = queue->head->next;
  free(node);
  if (queue->head == NULL) {
    queue->tail = NULL;
  }
}

void goldbach_number_queue_clear(goldbach_number_queue_t* queue) {
  assert(queue);
  pthread_mutex_lock(&queue->can_access_queue);
    while (!goldbach_number_queue_is_empty_unsafe(queue)) {
      goldbach_number_queue_remove_first_unsafe(queue);
    }
  pthread_mutex_unlock(&queue->can_access_queue);
}
