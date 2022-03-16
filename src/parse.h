#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "frac.h"

#ifndef __PEMDAS__
#define __PEMDAS__

#define MAX_PEMDAS_DEBUG_STR 100*1024

char **split(char *str, const char *del, int *len);

#define printable_enum(type, type_camel, vars...) enum type {vars}; \
  static long enum_##type_camel##_nums[] = {vars}; \
  static char *get_##type_camel##_str(enum type _enum) { \
    const char pemdas_debug_enum_delim[3] = ", "; \
    int len = 0; \
    static char s[MAX_PEMDAS_DEBUG_STR]; \
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
  PEMDAS_INT,
  PEMDAS_FRAC,
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

/* token - numbers */
typedef struct PemdasIntToken {
  enum PemdasTokenType type;
  struct PemdasToken *prev;
  struct PemdasToken *next;
  int data;
} pemdas_int_token_t;

typedef struct PemdasFracToken {
  enum PemdasTokenType type;
  struct PemdasToken *prev;
  struct PemdasToken *next;
  struct Frac *data;
} pemdas_frac_token_t;

/* token - var */
typedef struct PemdasVarToken {
  enum PemdasTokenType type;
  struct PemdasToken *prev;
  struct PemdasToken *next;
  struct PemdasVar *data;
} pemdas_var_token_t;

typedef struct PemdasVar {
  char *name;
  struct PemdasToken *coefficient;
} pemdas_var_t;

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
struct PemdasIntToken *pemdas_new_int_token();
struct PemdasExprToken *pemdas_new_expr_token();
struct PemdasFracToken *pemdas_new_frac_token(int num, int den);
struct PemdasVarToken *pemdas_new_var_token(char *name, struct PemdasToken *coef);
struct PemdasIneqToken *pemdas_new_ineq_token(enum PemdasIneq);

// parsers
struct PemdasToken *pemdas_parse(char *str);
struct PemdasExprToken *pemdas_parse_expr(char *str, int *len);
struct PemdasExprToken *pemdas_parse_paren(char *str, int *len);
struct PemdasOpToken *pemdas_parse_op(char *str, int *len);
struct PemdasIntToken *pemdas_parse_int(char *str, int *len);
struct PemdasVarToken *pemdas_parse_var(char *str, int *len);
struct PemdasIneqToken *pemdas_parse_Ineq(char *str, int *len);

#endif