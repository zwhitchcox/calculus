#ifndef __PEMDAS_COMMON__
#define __PEMDAS_COMMON__
#define MAX_PEMDAS_ENUM_STR 100*1024

/* UTILS */
char **split(char *str, const char *del, int *len);

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
#define DLL(type, lc_type) typedef struct LL##type { \
  struct type *lc_type; \
  struct LL##type *next; \
  struct LL##type *prev; \
} ##lc_type_t;
/* END UTILS */

typedef long long int ll_t;
#include "frac.h"
printable_enum(TokenType, token_type,
  VAR,
  TERM,
  EXPR,
  FRAC,
  INT,
)

DLL(Var, var)
typedef struct Variable {
  char *name;
} variable_t;

DLL(Term, term)
typedef struct Term {
  struct LLVar *variables;
  struct Frac *coefficient;
} term_t;

typedef struct Expression {
  struct LLTerm *terms;
} expression_t;

union Data {
  struct Expression *expression;
  struct Term *term;
  struct Variable *variable;
};

struct Token {
  enum TokenType type;
  union Data *data;
  struct Token *power;
};

#endif /* __PEMDAS_COMMON__ */