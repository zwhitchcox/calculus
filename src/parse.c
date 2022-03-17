#include <ctype.h>
#include <stdio.h>

#include "parse.h"
#include "var.h"
#include "string.h"
#include "print.h"
#include "token.h"
#include "debug.h"


struct PedmasVarToken *pedmas_parse_var(char *str, int *len) {
  if (isalpha(*str)) {
    char *start = str++;
    while (isalnum(*str) || isdigit(*str)) str++;
    *len = str - start;
    return pedmas_new_var_token(strndup(start, *len), 1, 1);
  }
  return NULL;
}

struct PedmasVarToken *pedmas_parse_num(char *str, int *len) {
  char *start = str;
  if (!isdigit(*str)) {
    return NULL;
  }
  int num = 0;
  while (isdigit(*str)) {
    num *= 10;
    num += *str - '0';
    str++;
  }
  while (isblank(*str)) {
    str++;
  }
  (*len) = str - start;
  start = str;
  while (isalpha(*str)) {
    str++;
  }
  (*len) += str - start;
  return pedmas_new_var_token(strndup(start, str - start), num, 1);
}

struct PedmasOpToken *pedmas_parse_op(char *str, int *len) {
  switch (*str) {
    case '+':
      *len = 1;
      return pedmas_new_op_token(PEDMAS_ADD);
    case '-':
      *len = 1;
      return pedmas_new_op_token(PEDMAS_SUB);
    case '/':
      *len = 1;
      return pedmas_new_op_token(PEDMAS_DIV);
    case '*':
      *len = 1;
      return pedmas_new_op_token(PEDMAS_MUL);
  }
  return NULL;
}

struct PedmasIneqToken *pedmas_parse_ineq(char *str, int *len) {
  switch (*str) {
    case '=':
      *len = 1;
      return pedmas_new_ineq_token(PEDMAS_EQ);
    case '>':
      if (*++str != '=') {
        *len = 1;
        return pedmas_new_ineq_token(PEDMAS_GT);
      }
      *len = 2;
      return pedmas_new_ineq_token(PEDMAS_GTE);
    case '<':
      if (*++str != '=') {
        *len = 1;
        return pedmas_new_ineq_token(PEDMAS_LT);
      }
      *len = 2;
      return pedmas_new_ineq_token(PEDMAS_LTE);
  }
  return NULL;
}


struct PedmasExprToken *pedmas_parse_paren(char *str, int *len) {
  char *strp = str;
  struct PedmasExprToken *token;
  if (*strp == '(') {
    token = pedmas_parse_expr(++strp, len);
    strp+= *len;
    if (*strp != ')') {
      fprintf(stderr, "unexpected token at %s\n", str);
      return NULL;
    }
    strp++;
    *len = strp - str;
    return token;
  }
  return NULL;
}

struct PedmasExprToken *pedmas_parse_expr(char *str, int *len) {
  char *strp = str;
  struct PedmasToken *cur = pedmas_new_token();
  struct PedmasToken *dummy = cur;
  cur->type = PEDMAS_DUMMY;
  cur->next = NULL;
  int _len;
  while (*strp) {
    _len = 0;
    while (isblank(*strp)) {
      strp++;
    }
    if (!((cur->next = (pedmas_token_t *)pedmas_parse_paren(strp, &_len)) ||
          (cur->next = (pedmas_token_t *)pedmas_parse_num(strp, &_len)) ||
          (cur->next = (pedmas_token_t *)pedmas_parse_op(strp, &_len)) ||
          (cur->next = (pedmas_token_t *)pedmas_parse_var(strp, &_len)))) {
      break;
    }
    cur->next->prev = cur;
    cur = cur->next;
    strp += _len;
  }
  *len = strp - str;

  cur->next = NULL;
  if (dummy->next) {
    dummy->next->prev = NULL;
  }
  return pedmas_new_expr_token(dummy->next);
}


struct PedmasToken *pedmas_parse(char *str) {
  struct PedmasToken *cur = pedmas_new_token();
  struct PedmasToken *dummy = cur;
  cur->type = PEDMAS_DUMMY;
  cur->next = NULL;
  int len = 0;
  char *strp = str;
  while (*strp) {
    if (!*strp) {
      break;
    }
    if (!((cur->next = (pedmas_token_t *)pedmas_parse_ineq(strp, &len)) ||
        (cur->next = (pedmas_token_t *)pedmas_parse_expr(strp, &len)))) {
      strp += len;
      fprintf(stderr, "unexpected token at %s\n", strp);
      return NULL;
    }
    cur->next->prev = cur;
    cur = cur->next;
    strp += len;
  }
  cur->next = NULL;
  if (dummy->next) {
    dummy->next->prev = NULL;
  }
  return (struct PedmasToken *)dummy->next;
}