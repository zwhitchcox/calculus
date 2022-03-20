#include <stdlib.h>

#ifndef __PEMDAS_FRAC__
#define __PEMDAS_FRAC__
#include "common.h"
struct Frac {
  ll_t num;
  ll_t den;
};
struct Frac *frac_new(ll_t num, ll_t den);
ll_t get_gcd(ll_t x, ll_t y);
ll_t get_lcd(ll_t x, ll_t y);
void frac_denominate(struct Frac *frac, ll_t den);
void frac_reduce(struct Frac *frac);
void frac_print(struct Frac *frac);
void frac_add(struct Frac *x, struct Frac *y);
void frac_div(struct Frac *x, struct Frac *y);
void frac_sub(struct Frac *x, struct Frac *y);
void frac_mul(struct Frac *x, struct Frac *y);
#endif
