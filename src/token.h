#include <string.h>
#include <stdlib.h>


#ifndef __PEMDAS_TOKEN__
#define __PEMDAS_TOKEN__

#include "common.h"
#include "var.h"

#define MAX_PEMDAS_ENUM_STR 100*1024

/* debugging */
static int count_occurrences(char *str, const char *delim) {
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

static char **split(char *str, const char *del, int *len) {
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

#define printable_enum(type, type_camel, vars...) enum type {vars}; \
  static long enum_##type_camel##_nums[] = {vars}; \
  static char *get_##type_camel##_str(enum type _enum) { \
    const char pemdas_debug_enum_delim[3] = ", "; \
    int len = 0; \
    static char s[MAX_PEMDAS_ENUM_STR]; \
    strcpy(s, #vars); \
    char **strs = split(s, pemdas_debug_enum_delim, &len); \
    int i = 0; \
    while (enum_##type_camel##_nums[i] != _enum && i < len) { \
      i++; \
    } \
    return strs[i]; \
  }



printable_enum(PemdasTokenType, pemdas_token_type,
  PEMDAS_DUMMY, // used internally
  PEMDAS_OP,
  PEMDAS_VAR,
  PEMDAS_EXPR,
  PEMDAS_INEQ,
)

typedef struct PemdasToken {
  enum PemdasTokenType type;
  struct PemdasToken *prev;
  struct PemdasToken *next;
  void *data;
} pemdas_token_t;

/* token - operations */
printable_enum(PemdasOp, pemdas_op,
  PEMDAS_ADD,
  PEMDAS_SUB,
  PEMDAS_MUL,
  PEMDAS_DIV,
)
typedef struct PemdasOpToken {
  enum PemdasTokenType type;
  struct PemdasToken *prev;
  struct PemdasToken *next;
  enum PemdasOp data;
} pemdas_op_token_t;

/* token - inequalities */
printable_enum(PemdasIneq, pemdas_ineq,
  PEMDAS_EQ,
  PEMDAS_GT,
  PEMDAS_GTE,
  PEMDAS_LT,
  PEMDAS_LTE,
);

typedef struct PemdasIneqToken {
  enum PemdasTokenType type;
  struct PemdasToken *prev;
  struct PemdasToken *next;
  enum PemdasIneq data;
} pemdas_ineq_token_t;

/* token - var */
typedef struct PemdasVarToken {
  enum PemdasTokenType type;
  struct PemdasToken *prev;
  struct PemdasToken *next;
  struct PemdasVar *data;
} pemdas_var_token_t;


/* token - expr */
typedef struct PemdasExprToken {
  enum PemdasTokenType type;
  struct PemdasToken *prev;
  struct PemdasToken *next;
  struct PemdasToken *data;
} pemdas_expr_token_t;

// token creators TODO: refactor
struct PemdasToken *pemdas_new_token();
struct PemdasOpToken *pemdas_new_op_token();
struct PemdasExprToken *pemdas_new_expr_token();
struct PemdasVarToken *pemdas_new_var_token(char *name, ll_t num, ll_t den);
struct PemdasIneqToken *pemdas_new_ineq_token(enum PemdasIneq);
#endif /*__PEMDAS_TOKEN__*/