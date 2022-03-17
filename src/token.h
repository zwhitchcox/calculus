#include <string.h>
#include <stdlib.h>


#ifndef __PEDMAS_TOKEN__
#define __PEDMAS_TOKEN__

#include "common.h"
#include "var.h"

#define MAX_PEDMAS_ENUM_STR 100*1024

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
    const char pedmas_debug_enum_delim[3] = ", "; \
    int len = 0; \
    static char s[MAX_PEDMAS_ENUM_STR]; \
    strcpy(s, #vars); \
    char **strs = split(s, pedmas_debug_enum_delim, &len); \
    int i = 0; \
    while (enum_##type_camel##_nums[i] != _enum && i < len) { \
      i++; \
    } \
    return strs[i]; \
  }



printable_enum(PedmasTokenType, pedmas_token_type,
  PEDMAS_DUMMY, // used internally
  PEDMAS_OP,
  PEDMAS_VAR,
  PEDMAS_EXPR,
  PEDMAS_INEQ,
)

typedef struct PedmasToken {
  enum PedmasTokenType type;
  struct PedmasToken *prev;
  struct PedmasToken *next;
  void *data;
} pedmas_token_t;

/* token - operations */
printable_enum(PedmasOp, pedmas_op,
  PEDMAS_ADD,
  PEDMAS_SUB,
  PEDMAS_MUL,
  PEDMAS_DIV,
)
typedef struct PedmasOpToken {
  enum PedmasTokenType type;
  struct PedmasToken *prev;
  struct PedmasToken *next;
  enum PedmasOp data;
} pedmas_op_token_t;

/* token - inequalities */
printable_enum(PedmasIneq, pedmas_ineq,
  PEDMAS_EQ,
  PEDMAS_GT,
  PEDMAS_GTE,
  PEDMAS_LT,
  PEDMAS_LTE,
);

typedef struct PedmasIneqToken {
  enum PedmasTokenType type;
  struct PedmasToken *prev;
  struct PedmasToken *next;
  enum PedmasIneq data;
} pedmas_ineq_token_t;

/* token - var */
typedef struct PedmasVarToken {
  enum PedmasTokenType type;
  struct PedmasToken *prev;
  struct PedmasToken *next;
  struct PedmasVar *data;
} pedmas_var_token_t;


/* token - expr */
typedef struct PedmasExprToken {
  enum PedmasTokenType type;
  struct PedmasToken *prev;
  struct PedmasToken *next;
  struct PedmasToken *data;
} pedmas_expr_token_t;

// token creators TODO: refactor
struct PedmasToken *pedmas_new_token();
struct PedmasOpToken *pedmas_new_op_token();
struct PedmasExprToken *pedmas_new_expr_token();
struct PedmasVarToken *pedmas_new_var_token(char *name, ll_t num, ll_t den);
struct PedmasIneqToken *pedmas_new_ineq_token(enum PedmasIneq);
#endif /*__PEDMAS_TOKEN__*/