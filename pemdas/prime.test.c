#include <stdio.h>
#include "prime.h"

int main() {
  struct LLInt *primes = sieve_of_eratosthenes(100);
  for (struct LLInt *cur = primes; cur; cur = cur->next) {
    printf("%d ", cur->num);
  }
  printf("\n");
}