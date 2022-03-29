#include <ctype.h>
#include <stdio.h>

#include "frac.h"
#include "string.h"
#include "print.h"
#include "token.h"
#include "debug.h"
#include "common.h"



struct PemdasIntToken *pemdas_parse_int(char *str, int *len) {
  if (!isdigit(*str)) {
    return NULL;
  }
  long long num = 0;
  while (isdigit(*str)) {
    num *= 10;
    num += *str - '0';
    str++;
    (*len)++;
  }
  struct PemdasIntToken* token = pemdas_new_int_token(num);
  return pemdas_new_int_token(num);
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

struct PemdasVarToken *pemdas_parse_var(char *str, int *len) {
  if (isalpha(*str)) {
    char *start = str++;
    while (isalnum(*str) || isdigit(*str)) str++;
    *len = str - start;
    return pemdas_new_var_token(strndup(start, *len),
                                (PemdasToken *)pemdas_new_frac_token(1, 1));
  }
  return NULL;
}
struct PemdasExprToken *pemdas_parse_e(char *str, int *len) {
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

struct PemdasToke *parse_terms(char *str) {

}

struct PemdasToken *parse_expression(char *str) {
  char *strp = str;
  int depth = 1;
  while (*strp) {
    if (*strp == '(') {
      depth++;
    } else if (*strp == ')') {
      if (!--depth) {
        parse_terms(strndup(str, strp - str));
        break;
      }
    }
    strp++;
  }
  cur->next = NULL;
  if (dummy->next) {
    dummy->next->prev = NULL;
  }
  return pemdas_new_expr_token(dummy->next);
}

int get_comparison_operator(char *str) {
  if (strncmp(str, ">=", 2)) {
    return GREATER_THAN_OR_EQUAL_TO;
  } else if (strncmp(str, "<=", 2)) {
    return LESS_THAN_OR_EQUAL_TO;
  } else if (strncmp(str, "=", 1)) {
    return EQUAL_TO;
  } else if (strncmp(str, ">", 1)) {
    return GREATER_THAN;
  } else if (strncmp(str, "<", 1)) {
    return LESS_THAN;
  }
  return 0;
}

struct PemdasToken *parse_equation(char *str) {
  struct PemdasToken *cur = pemdas_new_token();
  struct PemdasToken *dummy = cur;
  cur->type = PEMDAS_DUMMY;
  cur->next = NULL;
  int len = 0;
  char *strp = str;
  enum comparison_operator
  while (*strp) {
    while (!get) {

    }
    skip_blank(strp)
    if (!((cur->next = (PemdasToken *)pemdas_parse_ineq(strp, &len)) ||
        (cur->next = (PemdasToken *)pemdas_parse_expr(strp, &len)))) {
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