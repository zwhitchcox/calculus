#include <stdlib.h>
#include <stdio.h>

#include "frac.h"
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

struct LLInt *primes;
ll_t max_prime = 0;

ll_t get_lcd(ll_t x, ll_t y) {
  ll_t max = x > y ? x : y;
  if (!(primes && max_prime < max)) {
    primes = get_primes(max);
  }
  struct LLInt *primep = primes;
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

struct Frac *frac_new(ll_t num, ll_t den) {
  struct Frac *frac = malloc(sizeof(struct Frac));
  frac->num = num;
  frac->den = den;
}

void frac_reduce(struct Frac *frac) {
  ll_t frac_gcd = get_gcd(frac->num, frac->den);
  frac->num /= frac_gcd;
  frac->den /= frac_gcd;
}

void frac_denominate(struct Frac *frac, ll_t den) {
  ll_t x = den / frac->den;
  frac->num *= x;
  frac->den *= x;
}

void frac_add(struct Frac *x, struct Frac *y) {
  ll_t lcd = get_lcd(x->den, y->den);
  frac_denominate(x, lcd);
  frac_denominate(y, lcd);
  x->num += y->num;
  frac_reduce(x);
  free(y);
}

void frac_sub(struct Frac *x, struct Frac *y) {
  ll_t lcd = get_lcd(x->den, y->den);
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

void frac_print(struct Frac *frac) {
  printf("%lld/%lld\n", frac->num, frac->den);
}