#include <math.h>

#define is_num(c) (int) c >= '0' && (int) c <= '9'

int parse_num(char *s, int *r) {
  *r = 0;
  char *c = s;
  while (is_num(*c)) {
    *r *= 10;
    *r += *c - '0';
    c++;
  }
  return c - s; // return number of characters read
}

void itoa(int x, char *r) {
  int i = log10(x)+1;
  r[i] = '\0';
  while (i--) {
    r[i] = (x % 10) + '0';
    x /= 10;
  }
}

int solve(char *q, char *a) {
  char *qp = q;
  int r = 0;
  int *cur;
  int last_op = '+';

  while (*qp) {
    if (is_num(*qp)) {
      qp += parse_num(qp, cur);
      if (last_op == '+') {
        r += *cur;
        last_op == '\0';
      } else {
        printf("Illegal character: %c\n", *qp);
        return 0;
      }
    } else if (*qp == ' ') {
      qp++;
    } else if (*qp == '+') {
      last_op = *qp;
      qp++;
    } else {
      printf("Illegal character: %c\n", *qp);
      return 0;
    }
  }

  itoa(r, a);
  return 1;
}