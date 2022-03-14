#include <ctype.h>
#include <stdio.h>

#include "parse.h"
#include "frac.h"
#include "string.h"
#include "print.h"


/* debugging */
int count_occurrences(char *str, const char *delim) {
  int delim_len = strlen(delim);
  int count = 0;
  while (*str) {
    if (!strncmp(str, delim, delim_len)) {
      count++;
    }
    str++;
  }
  return count;
}

char **split(char *str, const char *del, int *len) {
  *len = count_occurrences(str, del);
  char **arr = malloc(sizeof(char*) * (*len));
  char *token = strtok(str, del);
  int i = 0;
  while (token != NULL) {
    arr[i++] = strdup(token);
    token = strtok(NULL, del);
  }
  return arr;
}

struct PemdasToken *pemdas_new_token() {
  return malloc(sizeof(struct PemdasToken));
}

struct PemdasFracToken *pemdas_new_frac_token(int num, int den) {
  struct PemdasFracToken *token = (struct PemdasFracToken *)pemdas_new_token();
  token->type = PEMDAS_FRAC;
  token->data = frac_new(num, den);
  return token;
}

struct PemdasVarToken *pemdas_new_var_token(char *name,
                                            struct PemdasToken *coef) {
  struct PemdasVarToken *token = (struct PemdasVarToken *)pemdas_new_token();
  struct PemdasVar *var = malloc(sizeof(struct PemdasVar));
  var->name = name;
  var->coefficient = coef;
  token->type = PEMDAS_VAR;
  token->data = var;
  return token;
}

struct PemdasOpToken *pemdas_new_op_token(enum PemdasOp op) {
  struct PemdasOpToken *token = (struct PemdasOpToken *)pemdas_new_token();
  token->type = PEMDAS_OP;
  token->data = op;
  return token;
}

struct PemdasIneqToken *pemdas_new_ineq_token(enum PemdasIneq ineq_type) {
  struct PemdasIneqToken *token = (struct PemdasIneqToken *)pemdas_new_token();
  token->type = PEMDAS_INEQ;
  token->data = ineq_type;
  return token;
}

struct PemdasIntToken *pemdas_new_int_token(int data) {
  struct PemdasIntToken *token = (struct PemdasIntToken *)pemdas_new_token();
  token->type = PEMDAS_INT;
  token->data = data;
  return token;
}

struct PemdasExprToken *pemdas_new_expr_token(struct PemdasToken *chain) {
  struct PemdasExprToken *token = (struct PemdasExprToken *)pemdas_new_token();
  token->type = PEMDAS_EXPR;
  token->data = chain;
  return token;
}

struct PemdasIntToken *pemdas_parse_int(char *str, int *len) {
  if (!isdigit(*str)) {
    return NULL;
  }
  int num = 0;
  while (isdigit(*str)) {
    num *= 10;
    num += *str - '0';
    str++;
    (*len)++;
  }
  printf("parsed int: %d\n", num);
  return pemdas_new_int_token(num);
}

struct PemdasOpToken *pemdas_parse_op(char *str, int *len) {
  switch (*str) {
    case '+':
      *len = 1;
      printf("parsed op: %c\n", *str);
      return pemdas_new_op_token(PEMDAS_ADD);
    case '-':
      *len = 1;
      printf("parsed op: %c\n", *str);
      return pemdas_new_op_token(PEMDAS_SUB);
    case '/':
      *len = 1;
      printf("parsed op: %c\n", *str);
      return pemdas_new_op_token(PEMDAS_DIV);
    case '*':
      *len = 1;
      printf("parsed op: %c\n", *str);
      return pemdas_new_op_token(PEMDAS_MUL);
  }
  return NULL;
}

struct PemdasSubToken *pemdas_parse_sub(char *str, int *len) {}

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
                                (pemdas_token_t *)pemdas_new_frac_token(1, 1));
  }
  return NULL;
}
struct PemdasExprToken *pemdas_parse_paren(char *str, int *len) {
  char *strp = str;
  struct PemdasExprToken *token;
  if (*strp == '(') {
    token = pemdas_new_expr_token((pemdas_token_t *) pemdas_parse_expr(++strp, len));
    strp+= *len;
    if (*strp != ')') {
      fprintf(stderr, "unexpected token\n");
      return NULL;
    }
    strp++;
    *len = strp - str;
    return token;
  }
  return NULL;
}
#define skip_blank(var) while (isblank(*var)) var++;
struct PemdasExprToken *pemdas_parse_expr(char *str, int *len) {
  printf("parsing expression: %s\n", str);
  char *strp = str;
  struct PemdasToken *cur = pemdas_new_token();
  struct PemdasToken *dummy = cur;
  cur->type = PEMDAS_DUMMY;
  cur->next = NULL;
  *len = 0;
  int _len;
  while (*strp) {
    skip_blank(strp)
    _len = 0;
    if (!((cur->next = (pemdas_token_t *)pemdas_parse_paren(strp, &_len)) ||
          (cur->next = (pemdas_token_t *)pemdas_parse_int(strp, &_len)) ||
          (cur->next = (pemdas_token_t *)pemdas_parse_op(strp, &_len)) ||
          (cur->next = (pemdas_token_t *)pemdas_parse_var(strp, &_len)))) {
      break;
    }
    cur->next->prev = cur;
    cur = cur->next;
    strp += _len;
    *len += _len;
    // char s[1000];
    // print_chain(s, dummy->next);
  }

  cur->next = NULL;
  if (dummy->next) {
    dummy->next->prev = NULL;
  }
  return (struct PemdasExprToken *)dummy->next;
}


struct PemdasToken *pemdas_parse(char *str) {
  struct PemdasToken *cur = pemdas_new_token();
  struct PemdasToken *dummy = cur;
  cur->type = PEMDAS_DUMMY;
  cur->next = NULL;
  int len = 0;
  char *strp = str;
  while (*strp) {
    skip_blank(strp)
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