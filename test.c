#include <stdio.h>
#include "solve.c"

#define MAX_RESULT 1000

int main() {
  char result[MAX_RESULT];
  solve("100", result);
  printf("result: %s\n", result);
}