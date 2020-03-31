#include "stdio.h"
#include <assert.h>
#include <time.h>
#include <string.h>

long f() {
  long iterations = 10;
  struct timespec tspec = {0,0};
  long nanosecs;
  long accumulator = 0;

  clock_gettime(CLOCK_MONOTONIC, &tspec);
  memcpy(&nanosecs, &(tspec.tv_nsec), sizeof(long));

  while (iterations > 0) {
    accumulator = iterations + accumulator;
    iterations--;
  }
    
  clock_gettime(CLOCK_MONOTONIC, &tspec);
  printf("f took about %d nano-seconds\n", tspec.tv_nsec - nanosecs);

  return accumulator;
}


int main(char** argv, int argc) {
  long result = f();
  printf("result == %d\n", result);
  assert(result == 55);
  return 0;
}