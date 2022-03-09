#include <stdlib.h>
#include "prime.h"

struct LLInt *new_llint(int num) {
  struct LLInt *llint = malloc(sizeof(struct LLInt));
  llint->num = num;
}


struct LLInt *sieve_of_eratosthenes(int max) {
  int arr[max+1];
  for (int i = 2; i <= max; i++) {
    arr[i] = 1;
  }
  int cur_start = 1;
  while (cur_start <= max) {
    while (!arr[++cur_start])
      ;
    int cur_multiple = cur_start;
    while ((cur_multiple+=cur_start) < max) {
      arr[cur_multiple] = 0;
    }
  }
  struct LLInt *head = new_llint(2);
  struct LLInt *cur = head;
  for (int i = 3; i <= max; i++) {
    if (arr[i]) {
      cur = cur->next = new_llint(i);
    }
  }
  return head;
}

