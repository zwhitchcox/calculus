#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

#include "fraction.h"
#include "string.h"
#include "print.h"
#include "token.h"
#include "debug.h"
#include "common.h"



struct Token *new_token(enum TokenType type, void *data) {
  struct Token *token = malloc(sizeof(struct Token));
  token->type = type;
  switch (type) {
    case TOKEN_OPERATOR:
      token->operator = data;
      break;
    case TOKEN_INTEGER:
      token->integer = data;
      break;
    case TOKEN_FUNCTION:
      token->function = data;
      break;
    case TOKEN_COMPARISON:

    default:
      fprintf(stderr, "Unrecognized token type: %d", type);
      exit(1);
  }
  return token;
}

void *get_token(char *str) {
  while (isblank(*str)) {
    str++;
  }
  switch (*str) {
    case '/':
      struct Token *token = new_token(TOKEN_OPERATOR, *str);
      token->operator = *str;
      return token;
  }
}

long long *parse_int(char *str, int *len) {
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
  return num;
}


union Node *parse_variable(char *str, int *len) {
  if (isalpha(*str)) {
    union Node *node = malloc(sizeof(union Node));
    node->node->type = VARIABLE;
    struct Variable *var = malloc(sizeof(struct Variable));
    *len += 1;
    return var;
  }
  return NULL;
}

union Node *parse_term(char *str, int *len) {
  while (isblank(*str)) {
    str++;
    *len++;
  }
  int cur_len = 0;
  union Node *node = malloc(sizeof(union Node));
  node->term->type = TERM;
  node->term->coefficient = frac_new(1, 1);
  while (true) {
    if (parse_int(str, len)) {

    }
  }
}

struct Token *parse_expression(char *str, int *len) {
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

struct PemdasToken *parse_terms(char *str) {

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