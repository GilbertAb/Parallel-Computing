// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>

#ifndef TAREAS_GOLDBACH_PTHREAD_GOLDBACH_PTHREAD_H_
#define TAREAS_GOLDBACH_PTHREAD_GOLDBACH_PTHREAD_H_

#include <assert.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "array_int64.h"
#include "common.h"
#include "consumer.h"
#include "goldbach_calculator.h"
#include "goldbach_sums_array.h"
#include "producer.h"

/**
 * @brief creates and initialize the goldbach_sums_array struct.
 * @details initialize the goldbach_sums_array struct.
 * @param numbers the numbers which goldbach sums will be calculated.
 * @return a pointer to goldbach_pthread.
*/
goldbach_pthread_t* goldbach_pthread_create(array_int64_t* numbers);

/**
 * @brief prepares execution of program does the things
 * @details verifies if number of threads was given by the user, creates the 
 * matrix for conditionally safe and calls to create threads and continue the
 * execution of the program.
 * @param goldbach_pthread struct that contains the shared data of the threads.
 * @param argc amount of arguments given in console.
 * @param argv arguments given in console.
 * @return an integer to check errors.
 */
int goldbach_pthread_run(goldbach_pthread_t* goldbach_pthread, int argc,
  char* argv[]);

int create_consumers_producers(goldbach_pthread_t* goldbach_pthread);
pthread_t* create_threads(size_t count, void*(*subroutine)(void*), goldbach_pthread_t* data);
int wait_threads(size_t count, pthread_t* threads);
/**
 * @brief creates the threads and puts them to do the calculations.
 * @details creates the threads, puts them to do the calculations, joins the
 * threads and prints the results.
 * @param goldbach_pthread struct that contains the shared data of the threads.
 * @return an integer to check errors.
 */
int goldbach_pthread_create_threads(goldbach_pthread_t* goldbach_pthread);

/**
 * @brief destroys the goldbach_pthread struct.
 * @details destroys the goldbach_pthread struct.
 * @param goldbach_pthread pointer to the struct to be destroyed.
 * @return an integer to check errors.
 */
int goldbach_pthread_destroy(goldbach_pthread_t* goldbach_pthread);

#endif  // TAREAS_GOLDBACH_PTHREAD_GOLDBACH_PTHREAD_H_
