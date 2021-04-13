#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* run(void* data);

int main(void){
  pthread_t thread; //a register is created to control the thread
  if(pthread_create(&thread, /*attribute*/ NULL, run, (void*)13) == EXIT_SUCCESS){
    printf("Hello from main thread\n");
    pthread_join(thread, /*value_ptr*/ NULL);
    return EXIT_SUCCESS;
  }else{
    fprintf(stderr,"could not create secundary thread\n");
    return EXIT_FAILURE;
  }

}

void* run(void* data){
  printf("Hello from secundary thread\n");
  printf("data = %p\n", data);
  return NULL;
}
