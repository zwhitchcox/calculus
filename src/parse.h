#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fraction.h"

#ifndef __PARSE__
#define __PARSE__
struct Token      *parse(char *str);
struct Expression *parse_expression(char *str, int *len);
struct Statement  *parse_statement(char *str, int *len);
struct Term       *parse_term(char *str, int *len);
struct Variable   *parse_variable(char *str, int *len);
#endif