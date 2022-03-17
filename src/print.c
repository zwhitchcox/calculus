#include "print.h"

#include <stdio.h>

#include "debug.h"
#include "var.h"
#include "math.h"
#include "token.h"

int pemdas_sprint_op(char *str, struct PemdasOpToken *op_token) {
  switch (op_token->data) {
    case PEMDAS_ADD:
      return sprintf(str, "+");
    case PEMDAS_SUB:
      return sprintf(str, "-");
    case PEMDAS_MUL:
      return sprintf(str, "*");
    case PEMDAS_DIV:
      return sprintf(str, "/");
    default:
      fprintf(stderr, "unrecognized token %s", str);
      return 0;
  }
}

int pemdas_sprint_var(char *str, struct PemdasVarToken *var_token) {
  char *start = str;
  struct PemdasVar *var = var_token->data;
  int len = 0;
  if (var->num != var->den || !strlen(var->name)) {
    long long num = var->num;
    long long den = var->den;
    if (abs(num) >= abs(den)) {
      long long remainder = num % den;
      long long quotient = num / den;
      if (remainder) {
        str += sprintf(str, "%lld %lld/%lld", quotient, remainder, den);
      } else {
        str += sprintf(str, "%lld", quotient);
      }
    } else {
      str += sprintf(str, "%lld/%lld", num, den);
    }
  }
  str += sprintf(str, "%s", var->name);
  return str - start;
}

int pemdas_sprint_ineq(char *str, struct PemdasIneqToken *ineq_token) {
  switch (ineq_token->data) {
    case PEMDAS_EQ:
      return sprintf(str, "=");
    case PEMDAS_GT:
      return sprintf(str, ">");
    case PEMDAS_GTE:
      return sprintf(str, ">=");
    case PEMDAS_LT:
      return sprintf(str, "<");
    case PEMDAS_LTE:
      return sprintf(str, "<=");
    default:
      fprintf(stderr, "unrecognized token %s", str);
      return 0;
  }
}
int pemdas_sprint_expr(char *str, struct PemdasToken *token) {
  char *start = str;
  while (token) {
    switch (token->type) {
      case PEMDAS_EXPR:
          *str++ = '(';
        str += pemdas_sprint_expr(str, token->data);
          if (*(str - 1) == ' ') {
            *(str - 1) = ')';
            *str++ = ' ';
          } else {
            *str++ = ')';
          }
        break;
      case PEMDAS_OP:
        str += pemdas_sprint_op(str, (struct PemdasOpToken *)token);
        break;
      case PEMDAS_VAR:
        str += pemdas_sprint_var(str, (struct PemdasVarToken *)token);
        break;
      default:
        fprintf(stderr, "pemdas_sprint: Invalid token: %s\n",
                get_pemdas_token_type_str(token->type));
        exit(1);
    }
    if (token->type != PEMDAS_EXPR) {
      *str++ = ' ';
    }
    token = token->next;
  }
  *str = '\0';
  return str - start;
}

int pemdas_sprint(char *str, struct PemdasToken *token) {
  char *start = str;
  while (token) {
    switch (token->type) {
      case PEMDAS_EXPR:
        str += pemdas_sprint_expr(str, token->data);
        break;
      case PEMDAS_INEQ:
        str += pemdas_sprint_ineq(str, (struct PemdasIneqToken *)token);
        break;
      default:
        fprintf(stderr, "pemdas_sprint: Invalid token\n");
        exit(1);
        break;
    }
    if (token->type != PEMDAS_EXPR) {
      *str++ = ' ';
    }
    token = token->next;
  }
  *str = '\0';
  return str - start;
}
