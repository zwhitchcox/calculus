#include <string.h>

#ifndef __PEMDAS_TOKEN__
#define __PEMDAS_TOKEN__
#include "common.h"

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
  ll_t data;
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
#endif /*__PEMDAS_TOKEN__*/