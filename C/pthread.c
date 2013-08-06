#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

struct params {
  int id;
  pthread_mutex_t *m;
};

void * thread_function(void *args) {
  //pthread_t self = pthread_self();
  int self = ((struct params *) args)->id;
  pthread_mutex_t *m = ((struct params *) args)->m;
  
  for (int i = 0; i < 100; ++i) {
    pthread_mutex_lock(m);
    printf("0. %d %d\n", (int)self, i);
    printf("1. %d %d\n", (int)self, i);
    pthread_mutex_unlock(m);
  }

  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t threadIDs[10];
  struct params * params[10];

  pthread_mutex_t mutex;  
  pthread_mutex_init(&mutex, NULL);

  for (int i = 0; i < 10; ++i) {
    params[i] = malloc(sizeof(struct params));
    params[i]->id = i;
    params[i]->m = &mutex;
    if (pthread_create(threadIDs+i, NULL, thread_function, params[i])) {
      fprintf(stderr, "MAIN: error creating thread %d\n", i);
      perror("main");
      break;
    }
  }

  for (int i = 0; i < 10; ++i) {
    if (pthread_join(threadIDs[i], NULL)) {
      perror("main");
      break;
    }
  }
}
