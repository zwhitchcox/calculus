#include <stdio.h>
#include <stdlib.h>

#include "frac.h"

#ifndef __PEMDAS__
#define __PEMDAS__

/* token types */
enum PemdasTokenType {
  PEMDAS_DUMMY, // used internally
  PEMDAS_OP,
  PEMDAS_INT,
  PEMDAS_FRAC,
  PEMDAS_VAR,
  PEMDAS_SUBEXPR,
  PEMDAS_INEQ,
};

typedef struct PemdasToken {
  enum PemdasTokenType type;
  struct PemdasToken *prev;
  struct PemdasToken *next;
  void *data;
} pemdas_token_t;

/* token - operations */
enum PemdasOp {
  PEMDAS_ADD,
  PEMDAS_SUB,
  PEMDAS_MUL,
  PEMDAS_DIV,
};
typedef struct PemdasOpToken {
  enum PemdasTokenType type;
  struct PemdasToken *prev;
  struct PemdasToken *next;
  enum PemdasOp data;
} pemdas_op_token_t;

/* token - inequalities */
enum PemdasIneq {
  PEMDAS_EQ,
  PEMDAS_GT,
  PEMDAS_GTE,
  PEMDAS_LT,
  PEMDAS_LTE,
};

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
  char *data;
} pemdas_var_token_t;

/* token - subexpr */
typedef struct PemdasSubexprToken {
  enum PemdasTokenType type;
  struct PemdasToken *prev;
  struct PemdasToken *next;
  struct PemdasToken *data;
} pemdas_subexpr_token_t;

struct PemdasToken *pemdas_new_token();
struct PemdasOpToken *pemdas_new_op_token();
struct PemdasIntToken *pemdas_new_int_token();
struct PemdasSubexprToken *pemdas_new_subexpr_token();
struct PemdasFracToken *pemdas_new_frac_token(int num, int den);
struct PemdasVarToken *pemdas_new_var_token(char *str);
struct PemdasIneqToken *pemdas_new_ineq_token(enum PemdasIneq);

struct PemdasToken *pemdas_parse(char *str);
struct PemdasOpToken *pemdas_parse_op(char *str, int *len);
struct PemdasIntToken *pemdas_parse_int(char *str, int *len);
struct PemdasVarToken *pemdas_parse_var(char *str, int *len);
struct PemdasIneqToken *pemdas_parse_Ineq(char *str, int *len);
#endif