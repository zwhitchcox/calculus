#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "var.h"

#ifndef __PEMDAS_PARSE__
#define __PEMDAS_PARSE__


// parsers
struct PemdasToken *pemdas_parse(char *str);
struct PemdasExprToken *pemdas_parse_expr(char *str, int *len);
struct PemdasExprToken *pemdas_parse_paren(char *str, int *len);
struct PemdasOpToken *pemdas_parse_op(char *str, int *len);
struct PemdasIntToken *pemdas_parse_int(char *str, int *len);
struct PemdasVarToken *pemdas_parse_var(char *str, int *len);
struct PemdasIneqToken *pemdas_parse_Ineq(char *str, int *len);

#endif