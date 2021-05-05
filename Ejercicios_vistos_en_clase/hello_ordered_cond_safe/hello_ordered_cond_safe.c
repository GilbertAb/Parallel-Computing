// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>
// Avoids race condition (concurrent modification of shared memory) by using
// mutual exclusion (mutex, lock)
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GREET_LEN 50

struct shared_data_t {
  size_t thread_count;
  size_t position;
  char** greets;
};

struct private_data_t {
  size_t thread_number;
  struct shared_data_t* shared_data;
};

int create_threads(struct shared_data_t* shared_data);
void* run(void* data);
void** create_matrix(size_t row_count, size_t col_count, size_t element_size);
void free_matrix(const size_t row_count, void** matrix);

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  
  struct shared_data_t* shared_data = (struct shared_data_t*)
    calloc(1, sizeof(struct shared_data_t));
  
  if (shared_data) {
    shared_data->position = 0;
    shared_data->thread_count = sysconf(_SC_NPROCESSORS_ONLN);
    if (error == EXIT_SUCCESS) {
      if (argc == 2 /*&& sscanf(argv[1], "%zu", &thread_count)*/){
        if(sscanf(argv[1], "%zu", &shared_data->thread_count) != 1) {
          fprintf(stderr,"error: invalid thread count");
          error = 1;
  	    }
      }
      
      if (error == EXIT_SUCCESS) {
		shared_data->greets = (char**) create_matrix(shared_data->thread_count,
		  GREET_LEN, sizeof(char));
		  
        struct timespec start_time;
        clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &start_time);
    
        error = create_threads(shared_data);
    
        struct timespec finish_time;
        clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &finish_time);
    
        double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
          (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;

        printf("Execution time: %.9lf\n", elapsed);
        
        for (size_t index = 0; index < shared_data->thread_count;index++) {
          printf("%s\n", shared_data->greets[index]);
		}
        free_matrix(shared_data->thread_count ,(void**)shared_data->greets);
        //free(shared_data->greets);
      }
    } else { 
      fprintf(stderr,"error: could not init mutex");
    }
    
    free(shared_data);
  }
  return error;
}

int create_threads(struct shared_data_t* shared_data){
  assert(shared_data);
  int error = EXIT_SUCCESS;
  pthread_t* threads = (pthread_t*)calloc(shared_data->thread_count,
   sizeof(pthread_t));
  struct private_data_t* private_data =(struct private_data_t*) 
    calloc(shared_data->thread_count, sizeof(struct private_data_t));
  if (threads && private_data) {
    for (size_t index = 0; index < shared_data->thread_count; ++index) {
      private_data[index].thread_number = index;
      private_data[index].shared_data = shared_data;
      
      if (pthread_create(&threads[index], /*attr*/ NULL, run,
          &private_data[index]) == EXIT_SUCCESS) {
      } else {
        fprintf(stderr, "could not create secundary thread\n");
        error = 21;
        break;
      }
    }
  
    printf("Hello from main thread\n");
  
    for (size_t index = 0; index < shared_data->thread_count; ++index) {
      pthread_join(threads[index], /*value_ptr*/ NULL);
    }
    free(threads);
    free(private_data);
  } else {
    fprintf(stderr, "Could not allocate memory for %zu threads\n"
      , shared_data->thread_count);
    error = 22;
  }
  return error;
}

void** create_matrix(size_t row_count, size_t col_count, size_t element_size) {
  void** matrix = (void**) calloc( row_count, sizeof(void*) );
  if (matrix == NULL){
    return NULL;  
  }
  
  for (size_t row = 0; row < row_count; ++row) {
    if ((matrix[row] = calloc(col_count, element_size)) == NULL){
      return free_matrix(row_count, matrix), NULL;
    }
  }
  return matrix;
}

void free_matrix(const size_t row_count, void** matrix) {
  if (matrix) {
    for (size_t row = 0; row < row_count; ++row){
      free(matrix[row]);
    }
  }
  free(matrix);
}

void* run(void* data) {
  const struct private_data_t* private_data = (struct private_data_t*)data;
  struct shared_data_t* shared_data = private_data->shared_data;
  const size_t my_thread_id = private_data->thread_number;
  const size_t thread_count = shared_data->thread_count;
  
  // Do heavy task
  
  sprintf(shared_data->greets[my_thread_id], "Hello from thread %zu of %zu", 
    my_thread_id, thread_count);

  return NULL;
}
