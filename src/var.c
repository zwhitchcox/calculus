#include <stdlib.h>
#include <stdio.h>

#include "var.h"
#include "prime.h"


ll_t get_gcd(ll_t x, ll_t y) {
  x = x > 0 ? x : -x;
  y = y > 0 ? y : -y;
  while (x != y) {
    if (x > y) {
      x -= y;
    } else {
      y -= x;
    }
  }
  return x;
}

struct LLLinkedList *primes;
ll_t max_prime = 0;

ll_t get_lcd(ll_t x, ll_t y) {
  ll_t max = x > y ? x : y;
  if (!(primes && max_prime < max)) {
    primes = get_primes(max);
  }
  struct LLLinkedList *primep = primes;
  ll_t cur_lcd = 1;
  while (primep->num <= max && primep->num <= x && primep->num <= y) {
    while (x % primep->num == 0 && y % primep->num == 0) {
      x /= primep->num;
      y /= primep->num;
      cur_lcd *= primep->num;
    }
    primep = primep->next;
  }
  return cur_lcd*x*y;
}

struct PemdasVar *var_new(ll_t num, ll_t den) {
  struct PemdasVar *var = malloc(sizeof(struct PemdasVar));
  var->num = num;
  var->den = den;
}

void var_reduce(struct PemdasVar *var) {
  ll_t var_gcd = get_gcd(var->num, var->den);
  var->num /= var_gcd;
  var->den /= var_gcd;
}

void var_denominate(struct PemdasVar *var, ll_t den) {
  ll_t x = den / var->den;
  var->num *= x;
  var->den *= x;
}

void var_add(struct PemdasVar *x, struct PemdasVar *y) {
  ll_t lcd = get_lcd(x->den, y->den);
  var_denominate(x, lcd);
  var_denominate(y, lcd);
  x->num += y->num;
  var_reduce(x);
  free(y);
}

void var_sub(struct PemdasVar *x, struct PemdasVar *y) {
  ll_t lcd = get_lcd(x->den, y->den);
  var_denominate(x, lcd);
  var_denominate(y, lcd);
  x->num -= y->num;
  var_reduce(x);
  free(y);
}

void var_mul(struct PemdasVar *x, struct PemdasVar *y) {
  x->num *= y->num;
  x->den *= y->den;
  var_reduce(x);
  free(y);
}

void var_div(struct PemdasVar *x, struct PemdasVar *y) {
  x->num *= y->den;
  x->den *= y->num;
  var_reduce(x);
  free(y);
}

void var_print(struct PemdasVar *var) {
  printf("%lld/%lld\n", var->num, var->den);
}