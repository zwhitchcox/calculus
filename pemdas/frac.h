#include <stdlib.h>

#ifndef __PEMDAS_FRAC__
#define __PEMDAS_FRAC__
struct Frac {
  int num;
  int den;
};
struct Frac *frac_new(int num, int den);
int get_gcd(int x, int y);
int get_lcd(int x, int y);
void frac_denominate(struct Frac *frac, int den);
void frac_reduce(struct Frac *frac);
void frac_print(struct Frac *frac);
void frac_add(struct Frac *x, struct Frac *y);
void frac_div(struct Frac *x, struct Frac *y);
void frac_sub(struct Frac *x, struct Frac *y);
void frac_mul(struct Frac *x, struct Frac *y);
#endif
