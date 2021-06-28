#ifndef GOLDBACH_PTHREAD
#define GOLDBACH_PTHREAD

#include <stddef.h>
#include "array_int64.h"
#include "goldbach_sums_array.h"

// Shared_data
typedef struct goldbach_pthread{
  int64_t thread_count;
  array_int64_t* numbers;
  goldbach_sums_array_t** goldbach_sums;
} goldbach_pthread_t;

typedef struct  {
  int64_t start_index;
  int64_t finish_index;
  int64_t thread_number;
  goldbach_pthread_t* goldbach_pthread;
} private_data_t;

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
int goldbach_pthread_run(goldbach_pthread_t* goldbach_pthread, int argc, char* argv[]);

/**
 * @brief constructs an array with the goldbach sums.
 * @details verifies if the number is even or odd, then calls
 * a conjecture to create the array of goldbach sums.
 * @param data (goldbach_pthread) struct that contains the shared data of the
 * threads.
 * @return null.
 */
void* goldbach_pthread_calculate_goldbach(void* data);

/**
 * @brief constructs an array with the goldbach sums.
 * @details the conjecture for even numbers, the first position of the array
 * is the amount of goldbach sums of the number. the next positions are the
 * numbers that conform the sums (they will be accessed in pairs to print).
 * @param goldbach_pthread struct that contains the shared data of the threads.
 * @param number number whose goldbach sums will be calculated.
 * @return an integer to check errors.
 */
int goldbach_pthread_strong_conjecture(goldbach_pthread_t* goldbach_pthread,
  int64_t number, int64_t thread_number);

/**
 * @brief constructs an array with the goldbach sums
 * @details the conjecture for odd numbers, the first position of the array
 * is the amount of goldbach sums of the number. the next positions are the
 * numbers that conform the sums (they will be accessed int trios to print).
 * @param goldbach_pthread struct that contains the shared data of the threads.
 * @param number number whose goldbach sums will be calculated.
 * @return an integer to check errors.
 */
int goldbach_pthread_weak_conjecture(goldbach_pthread_t* goldbach_pthread, int64_t number,
  int64_t thread_number);

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
#endif  // GOLDBACH_PTHREAD
