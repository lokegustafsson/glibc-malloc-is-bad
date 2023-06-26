#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* stuff(void* arg) {
  puts("Child before");
  for(int i = 0; i < 1*1000*1000; i++) {
    volatile char* ptr = malloc(256);
    *ptr = (char)i;
  }
  puts("Child after");
  return NULL;
}

int main() {
  puts("Main before");
  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;
  pthread_create(&thread1, NULL, stuff, NULL);
  pthread_create(&thread2, NULL, stuff, NULL);
  pthread_create(&thread3, NULL, stuff, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);
  puts("Main after");
}
