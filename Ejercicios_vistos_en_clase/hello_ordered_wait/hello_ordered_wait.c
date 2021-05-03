// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>
// Creates an arbitrary amount of threads that greet in stdout
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct shared_data_t {
  size_t thread_count;
  size_t next_thread; 
};

struct private_data_t {
  size_t thread_number;
  struct shared_data_t* shared_data;
};

int create_threads(struct shared_data_t* shared_data);
void* run(void* data);

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  
  struct shared_data_t* shared_data = (struct shared_data_t*)
    calloc(1, sizeof(struct shared_data_t));
  
  if (shared_data) {
    shared_data->next_thread = 0;
    shared_data->thread_count = sysconf(_SC_NPROCESSORS_ONLN);
    if (argc == 2 /*&& sscanf(argv[1], "%zu", &thread_count)*/){
      if(sscanf(argv[1], "%zu", &shared_data->thread_count) != 1) {
        fprintf(stderr,"error: invalid thread count");
        return EXIT_FAILURE;
  	  }
    }
    
    struct timespec start_time;
    clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &start_time);
    
    error = create_threads(shared_data);
    
    struct timespec finish_time;
    clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &finish_time);
    
    double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
      (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
    
    printf("Execution time: %.9lf\n", elapsed);
    
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

void* run(void* data) {
  const struct private_data_t* private_data = (struct private_data_t*)data;
  const size_t my_thread_id = private_data->thread_number;
  const size_t thread_count = private_data->shared_data->thread_count;
  
  // Wait until it is my turn
  while ( private_data->shared_data->next_thread < my_thread_id ){
    // busy waiting  
  }
  
  // Do the ordered-task here
  printf("Hello from secundary thread %zu of %zu\n", my_thread_id,
         thread_count);
  // Allow subsequent thread to do the task
  ++private_data->shared_data->next_thread;
  

  return NULL;
}
