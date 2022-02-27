#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_STR 1024

int is_num(char c) {
  return c >= '0' && c <= '9';
}

int parse_num(char *c) {
  int result = 0;
  while (is_num(*c)) {
    result *= 10;
    result += *c - '0';
    c++;
  }
  return result;
}


void itoa(int num, char *result) {
  int idx = log(num)-1;
  result[idx--] = '\0';
  while (idx >= 0) {
    result[idx] = (num % 10) + '0';
    num /= 10;
    idx--;
  }
}

void solve(char *question, char *result) {
  int cur = 0;
  char *c = question;
  int num = parse_num(question);
  itoa(num, result);
}