#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "frac.h"
#include "prime.h"
#include "common.h"


int get_gcd(int x, int y) {
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

struct LLInt *primes;
ll_t max_prime = 0;

ll_t get_lcd(ll_t x, ll_t y) {
  ll_t max = x > y ? x : y;
  if (!primes || max_prime < max) {
    free_ll(primes);
    primes = get_primes(max*2);
    max_prime = max*2;
  }
  struct LLInt *primep = primes;
  int cur_lcd = 1;
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

void free_ll(struct LLInt *ll) {
  struct LLInt *cur_prime = ll;
  struct LLInt *last;
  while(cur_prime) {
    last = cur_prime;
    cur_prime = cur_prime->next;
    free(cur_prime);
  }
}

struct LLInt *factor(ll_t num) {
  if (!primes || max_prime < num) {
    free_ll(primes);
    primes = get_primes(num*2);
    max_prime = num*2;
  }
  struct LLInt *factorization = new_llint(1);
  struct LLInt *cur_factor = factorization;
  struct LLInt *cur_prime = primes;
  while (num && cur_prime && cur_prime->num < num) {
    while ((num % cur_prime->num) == 0) {
      num /= cur_prime->num;
      cur_factor->next = new_llint(cur_prime->num);
      cur_factor = cur_factor->next;
      cur_factor->num = cur_prime->num;
    }
    cur_prime = cur_prime->next;
  }
  return factorization->next;
}


struct Frac *frac_new(int num, int den) {
  struct Frac *frac = malloc(sizeof(struct Frac));
  frac->num = num;
  frac->den = den;
}

void frac_reduce(struct Frac *frac) {
  int frac_gcd = get_gcd(frac->num, frac->den);
  frac->num /= frac_gcd;
  frac->den /= frac_gcd;
}

void frac_denominate(struct Frac *frac, int den) {
  int x = den / frac->den;
  frac->num *= x;
  frac->den *= x;
}

void frac_add(struct Frac *x, struct Frac *y) {
  int lcd = get_lcd(x->den, y->den);
  frac_denominate(x, lcd);
  frac_denominate(y, lcd);
  x->num += y->num;
  frac_reduce(x);
  free(y);
}

void frac_sub(struct Frac *x, struct Frac *y) {
  int lcd = get_lcd(x->den, y->den);
  frac_denominate(x, lcd);
  frac_denominate(y, lcd);
  x->num -= y->num;
  frac_reduce(x);
  free(y);
}

void frac_mul(struct Frac *x, struct Frac *y) {
  x->num *= y->num;
  x->den *= y->den;
  frac_reduce(x);
  free(y);
}

void frac_div(struct Frac *x, struct Frac *y) {
  x->num *= y->den;
  x->den *= y->num;
  frac_reduce(x);
  free(y);
}



void frac_pow(struct Frac *x, struct Frac *y) {
  x->num = pow(x->num, y->num);
  struct LLInt *fx;
  struct LLInt *fy;
  if (y->num != 1) {
    struct LLInt *fx = factor(x);
    struct LLInt *fy = factor(y);
  }
  frac_reduce(x);
  free(y);
}

void frac_print(struct Frac *frac) {
  printf("%d/%d\n", frac->num, frac->den);
}