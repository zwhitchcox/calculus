#include <stdio.h>
#include <assert.h>
#include "fraction.h"

int main() {
  int x, y;
  x = 40;
  y = 40;
  // should be 40
  assert(get_lcd(x,y) == 40);
  printf("lcd(%d, %d): %d\n", x, y, get_lcd(x, y));
  x = 15;
  y = 200;
  printf("lcd(%d, %d): %d\n", x, y, get_lcd(x, y));
  assert(get_lcd(x,y) == 600);
  struct Frac *frac1 = frac_new(x, y);
  struct Frac *frac2 = frac_new(7,40);
  frac_add(frac1, frac2);
  // should be 1/4
  frac_print(frac1);
  assert(frac1->num == 1 && frac1->den == 4);
}