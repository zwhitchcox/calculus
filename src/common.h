#ifndef __PEMDAS_COMMON__
#define __PEMDAS_COMMON__
#include "fraction.h"
#include "stdbool.h"

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
  struct type *##lc_type; \
  struct LL##type *next; \
  struct LL##type *prev; \
} lc_type;
/* END UTILS */

enum NodeType {
  #define _S(node_type) node_type,
  #include "strnodetype.h"
  #undef _S
};

char *nt_to_str(enum NodeType nt) {
  #define _S(node_type) if (nt == node_type) return #node_type
  #include "strnodetype.h"
  #undef _S
  return NULL;
}

DLL(Variable, variable)
struct Variable {
  enum NodeType type;
  char *name;
  struct Expression *power;
};

DLL(Term, term)
struct Term {
  enum NodeType type;
  struct LLVar *variables;
  struct Fraction *coefficient;
  struct Expression *power;
};

struct Expression {
  enum NodeType type;
  struct LLTerm *terms;
  struct Expression *power;
};


struct Statement {
  enum NodeType type;
  enum Comparison cmp;
  struct Expression *left;
  struct Expression *right;
};

struct GenericNode {
  enum NodeType type;
};

// TODO: Compound Statement

union Node {
  struct GenericNode *node;
  struct Statement *statement;
  struct Expression *expression;
  struct Term *term;
  struct Variable *variable;
};

enum TokenType {
#define _S(token) TOKEN_##token,
#include "strtokentype.h"
#undef _S
};

char *tt_to_str(enum TokenType tt) {
#define _S(token_type) if (tt == TOKEN_##token_type) return #token_type;
#include "strtokentype.h"
#undef _S
};

enum Operator {
#define _S(operator) OPERATOR_##operator,
#include "stroperator.h"
#undef _S
};

enum Operator char_to_op(char c) {
#define _S(operator, ch) if (c == ch) return OPERATOR_##operator;
#include "stroperator.h"
#undef _S
  return NULL;
}

char *op_to_str(enum Operator tt) {
#define _S(operator) if (tt == TOKEN_##operator) return #operator;
#include "stroperator.h"
#undef _S
  return NULL;
};

enum Comparison {
#define _S(cmp, cmpstr) COMPARISON_##cmp,
#include "strcomparison.h"
#undef _S
};

enum Comparison str_to_cmp(char *str) {
#define _S(cmp, cmpstr) if (!strcmp(str, cmpstr)) return COMPARISON_##cmp;
#include "strcomparison.h"
#undef _S
  return NULL;
}

char *cmp_to_str(enum Comparison comparison) {
#define _S(cmp, cmpstr) if (cmp == comparison) return "COMPARISON_" #cmp;
#include "strcomparison.h"
#undef _S
  return NULL;
}

struct Token {
  enum TokenType type;
  char *variable;
  char *function;
  long long integer;
  char operator;
  char parenthesis;
};

#endif /* __PEMDAS_COMMON__ */