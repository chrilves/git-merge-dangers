#include "stdio.h"
#include <assert.h>

long f() {
  long iterations = 10;
  long accumulator = 0;

  while (iterations > 0) {
    accumulator = iterations + accumulator;
    iterations--;
  }
    
  return accumulator;
}


int main(char** argv, int argc) {
  long result = f();
  printf("result == %d\n", result);
  assert(result == 55);
  return 0;
}