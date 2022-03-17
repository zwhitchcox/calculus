#include "parse.h"

#ifndef __PEDMAS_DEBUG__
#define __PEDMAS_DEBUG__
#define debug printf
void debug_token_o(struct PedmasToken *token, char *str, int nl);
void debug_token(char *str, struct PedmasToken *token);
#endif /* __PEDMAS_DEBUG__ */

// #include <string.h>

// #ifndef __PEDMAS_DEBUG__
// #define __PEDMAS_DEBUG__

// #define MAX_PEDMAS_DEBUG_STR 100*1024

// char **split(char *str, const char *del, int *len);
// #define printable_enum(type, type_camel, vars...) enum type {vars}; \
//   long enum_##type_camel##_nums[] = {vars}; \
//   char *get_##type_camel##_str(enum type _enum) { \
//     const char pedmas_debug_enum_delim[3] = ", "; \
//     int len = 0; \
//     static char s[MAX_PEDMAS_DEBUG_STR]; \
//     strcpy(s, #vars); \
//     char **strs = split(s, pedmas_debug_enum_delim, &len); \
//     int i = 0; \
//     while (enum_##type_camel##_nums[i] != _enum && i < len) { \
//       i++; \
//     } \
//     return strs[i]; \
//   }
// #endif