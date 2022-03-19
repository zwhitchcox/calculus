#include <stdlib.h>
#include <stdio.h>

#include "term.h"
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

struct PemdasTerm *pemdas_term_new(struct PemdasVar *var, struct PemdasCoef *coef) {
  struct PemdasTerm *term = malloc(sizeof(struct PemdasTerm));
  term->var = var;
  term->coef = coef;
}

// void pemdas_term_reduce(struct PemdasTerm *term) {
//   ll_t term_gcd = get_gcd(term->num, term->den);
//   term->num /= term_gcd;
//   term->den /= term_gcd;
// }

void pemdas_term_denominate(struct PemdasTerm *term, ll_t den) {
  ll_t x = den / term->den;
  term->num *= x;
  term->den *= x;
}

void pemdas_term_add(struct PemdasTerm *x, struct PemdasTerm *y) {
  ll_t lcd = get_lcd(x->den, y->den);
  term_denominate(x, lcd);
  term_denominate(y, lcd);
  x->num += y->num;
  term_reduce(x);
  free(y);
}

// void pemdas_term_sub(struct PemdasTerm *x, struct PemdasTerm *y) {
//   ll_t lcd = get_lcd(x->den, y->den);
//   term_denominate(x, lcd);
//   term_denominate(y, lcd);
//   x->num -= y->num;
//   term_reduce(x);
//   free(y);
// }

// void pemdas_term_mul(struct PemdasTerm *x, struct PemdasTerm *y) {
//   x->num *= y->num;
//   x->den *= y->den;
//   term_reduce(x);
//   free(y);
// }

// void pemdas_term_div(struct PemdasTerm *x, struct PemdasTerm *y) {
//   x->num *= y->den;
//   x->den *= y->num;
//   term_reduce(x);
//   free(y);
// }

// void pemdas_term_print(struct PemdasTerm *term) {
//   printf("%lld/%lld\n", term->num, term->den);
// }