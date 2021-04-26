// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>
// Creates an arbitrary amount of threads that greet in stdout

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int create_threads(size_t thread_count);
void* run(void* data);

struct private_data_t {
  size_t thread_number;
  size_t thread_count;
};

int main(int argc, char* argv[]) {
  size_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  if (argc == 2 /*&& sscanf(argv[1], "%zu", &thread_count)*/){
    if(sscanf(argv[1], "%zu", &thread_count) != 1) {
      fprintf(stderr,"error: invalid thread count");
      return EXIT_FAILURE;
	}
  }
  
  int error = create_threads(thread_count);
  return error;
}

int create_threads(size_t thread_count){
  int error = EXIT_SUCCESS;
  pthread_t* threads = (pthread_t*)calloc(thread_count, sizeof(pthread_t));
  struct private_data_t* private_data =(struct private_data_t*) 
    calloc(thread_count, sizeof(struct private_data_t));
  if (threads && private_data) {
    for (size_t index = 0; index < thread_count; ++index) {
      private_data[index].thread_number = index;
      private_data[index].thread_count = thread_count;
      if (pthread_create(&threads[index], /*attr*/ NULL, run,
          &private_data[index]) == EXIT_SUCCESS) {
      } else {
        fprintf(stderr, "could not create secundary thread\n");
        error = 21;
        break;
      }
    }
  
    printf("Hello from main thread\n");
  
    for (size_t index = 0; index < thread_count; ++index) {
      pthread_join(threads[index], /*value_ptr*/ NULL);
    }
    free(threads);
    free(private_data);
  } else {
    fprintf(stderr, "Could not allocate memory for %zu threads\n"
      , thread_count);
    error = 22;
  }
  return error;
}

void* run(void* data) {
  struct private_data_t* private_data = (struct private_data_t*)data;
  printf("Hello from secundary thread %zu of %zu\n", private_data->thread_number,
         private_data->thread_count);

  return NULL;
}
