#include <stdlib.h>

#ifndef __PEMDAS_FRAC__
#define __PEMDAS_FRAC__
#include "common.h"
struct Frac {
  long long num;
  long long den;
};
struct Frac *frac_new(long long num, long long den);
long long get_gcd(long long x, long long y);
long long get_lcd(long long x, long long y);
void frac_denominate(struct Frac *frac, long long den);
void frac_reduce(struct Frac *frac);
void frac_print(struct Frac *frac);
void frac_add(struct Frac *x, struct Frac *y);
void frac_div(struct Frac *x, struct Frac *y);
void frac_sub(struct Frac *x, struct Frac *y);
void frac_mul(struct Frac *x, struct Frac *y);
#endif
