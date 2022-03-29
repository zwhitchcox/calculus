#include <stdlib.h>
#include <stdio.h>

#include "fraction.h"
#include "prime.h"


long long get_gcd(long long x, long long y) {
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
long long max_prime = 0;

long long get_lcd(long long x, long long y) {
  long long max = x > y ? x : y;
  if (!(primes && max_prime < max)) {
    primes = get_primes(max);
  }
  struct LLInt *primep = primes;
  long long cur_lcd = 1;
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

struct Frac *frac_new(long long num, long long den) {
  struct Frac *frac = malloc(sizeof(struct Frac));
  frac->num = num;
  frac->den = den;
}

void frac_reduce(struct Frac *frac) {
  long long frac_gcd = get_gcd(frac->num, frac->den);
  frac->num /= frac_gcd;
  frac->den /= frac_gcd;
}

void frac_denominate(struct Frac *frac, long long den) {
  long long x = den / frac->den;
  frac->num *= x;
  frac->den *= x;
}

void frac_add(struct Frac *x, struct Frac *y) {
  long long lcd = get_lcd(x->den, y->den);
  frac_denominate(x, lcd);
  frac_denominate(y, lcd);
  x->num += y->num;
  frac_reduce(x);
  free(y);
}

void frac_sub(struct Frac *x, struct Frac *y) {
  long long lcd = get_lcd(x->den, y->den);
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