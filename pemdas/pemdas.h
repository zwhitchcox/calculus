#include <stdio.h>
#include <stdlib.h>

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
  struct PemdasFrac *data;
} pemdas_frac_token_t;

typedef struct PemdasFrac {
  int numerator;
  int denominator;
} pemdas_frac_t;

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

struct PemdasSubexprToken *new_subexpr_token();
struct PemdasToken *parse(char *str);
struct PemdasOpToken *parse_op(char *str, int *len);
struct PemdasIntToken *parse_int(char *str, int *len);
#endif