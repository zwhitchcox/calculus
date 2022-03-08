#include <math.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_STACK 1000


int parse_num(char *s, int *r) {
  *r = 0;
  char *c = s;
  while (is_digit(*c)) {
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

int illegal(char c, int idx, char *str) {
  printf("Unexpected token at %d: %c\n", idx, c);
  printf("%s\n", str);
  for (int i = 0; i < idx; i++) {
    printf(" ");
  }
  printf("^\n");
  return 0;
}

int solve(char *q, char *a) {
  char op_stack[MAX_STACK];
  char *qp = q;
  int r = 0;
  int *cur;
  int last_op = '\0';
  int first = 1;
  int idx = 0;
  char* qp_start = 0;

  while (*qp) {
    qp_start = qp;
    if (is_digit(*qp)) {
      if (first) {
        last_op = '+';
      }
      qp += parse_num(qp, cur);
      if (last_op == '+') {
        r += *cur;
      } else if (last_op == '-') {
        r -= *cur;
      } else {
        return illegal(*qp, idx, q);
      }
      first = 0;
      last_op = '\0';
    } else if (*qp == ' ') {
      qp++;
    } else if (*qp == '+') {
      if (last_op == '-' || last_op == '+') {
        printf("'+' cannot follow a '%c'\n", last_op);
        return illegal(*qp, idx, q);
      }
      last_op = *qp;
      qp++;
    } else if (*qp == '-') {
      if (last_op == '-') {
        return illegal(*qp, idx, q);
      }
      last_op = *qp;
      qp++;
    } else {
      return illegal(*qp, idx, q);
    }
    idx += qp - qp_start;
  }

  itoa(r, a);
  return 1;
}