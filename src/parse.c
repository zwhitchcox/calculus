#include <ctype.h>
#include <stdio.h>

#include "parse.h"
#include "var.h"
#include "string.h"
#include "print.h"
#include "token.h"
#include "debug.h"


struct PemdasVarToken *pemdas_parse_var(char *str, int *len) {
  if (isalpha(*str)) {
    char *start = str++;
    while (isalnum(*str) || isdigit(*str)) str++;
    *len = str - start;
    return pemdas_new_var_token(strndup(start, *len), 1, 1);
  }
  return NULL;
}

struct PemdasVarToken *pemdas_parse_num(char *str, int *len) {
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
  while (isalpha(*(str+1))) {
    str++;
  }
  (*len) += str - start;
  return pemdas_new_var_token(strndup(start, str - start), num, 1);
}

struct PemdasOpToken *pemdas_parse_op(char *str, int *len) {
  switch (*str) {
    case '+':
      *len = 1;
      return pemdas_new_op_token(PEMDAS_ADD);
    case '-':
      *len = 1;
      return pemdas_new_op_token(PEMDAS_SUB);
    case '/':
      *len = 1;
      return pemdas_new_op_token(PEMDAS_DIV);
    case '*':
      *len = 1;
      return pemdas_new_op_token(PEMDAS_MUL);
  }
  return NULL;
}

struct PemdasIneqToken *pemdas_parse_ineq(char *str, int *len) {
  switch (*str) {
    case '=':
      *len = 1;
      return pemdas_new_ineq_token(PEMDAS_EQ);
    case '>':
      if (*++str != '=') {
        *len = 1;
        return pemdas_new_ineq_token(PEMDAS_GT);
      }
      *len = 2;
      return pemdas_new_ineq_token(PEMDAS_GTE);
    case '<':
      if (*++str != '=') {
        *len = 1;
        return pemdas_new_ineq_token(PEMDAS_LT);
      }
      *len = 2;
      return pemdas_new_ineq_token(PEMDAS_LTE);
  }
  return NULL;
}


struct PemdasExprToken *pemdas_parse_paren(char *str, int *len) {
  char *strp = str;
  struct PemdasExprToken *token;
  if (*strp == '(') {
    token = pemdas_parse_expr(++strp, len);
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

struct PemdasExprToken *pemdas_parse_expr(char *str, int *len) {
  char *strp = str;
  struct PemdasToken *cur = pemdas_new_token();
  struct PemdasToken *dummy = cur;
  cur->type = PEMDAS_DUMMY;
  cur->next = NULL;
  int _len;
  while (*strp) {
    _len = 0;
    while (isblank(*strp)) {
      strp++;
    }
    if (!((cur->next = (pemdas_token_t *)pemdas_parse_paren(strp, &_len)) ||
          (cur->next = (pemdas_token_t *)pemdas_parse_num(strp, &_len)) ||
          (cur->next = (pemdas_token_t *)pemdas_parse_op(strp, &_len)) ||
          (cur->next = (pemdas_token_t *)pemdas_parse_var(strp, &_len)))) {
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
  return pemdas_new_expr_token(dummy->next);
}


struct PemdasToken *pemdas_parse(char *str) {
  struct PemdasToken *cur = pemdas_new_token();
  struct PemdasToken *dummy = cur;
  cur->type = PEMDAS_DUMMY;
  cur->next = NULL;
  int len = 0;
  char *strp = str;
  while (*strp) {
    if (!*strp) {
      break;
    }
    if (!((cur->next = (pemdas_token_t *)pemdas_parse_ineq(strp, &len)) ||
        (cur->next = (pemdas_token_t *)pemdas_parse_expr(strp, &len)))) {
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
  return (struct PemdasToken *)dummy->next;
}