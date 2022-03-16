#include "parse.h"

#ifndef __PEMDAS_DEBUG__
#define __PEMDAS_DEBUG__
#define debug printf
void debug_token_o(struct PemdasToken *token, char *str, int nl);
void debug_token(struct PemdasToken *token, char *str);
#endif /* __PEMDAS_DEBUG__ */

// #include <string.h>

// #ifndef __PEMDAS_DEBUG__
// #define __PEMDAS_DEBUG__

// #define MAX_PEMDAS_DEBUG_STR 100*1024

// char **split(char *str, const char *del, int *len);
// #define printable_enum(type, type_camel, vars...) enum type {vars}; \
//   long enum_##type_camel##_nums[] = {vars}; \
//   char *get_##type_camel##_str(enum type _enum) { \
//     const char pemdas_debug_enum_delim[3] = ", "; \
//     int len = 0; \
//     static char s[MAX_PEMDAS_DEBUG_STR]; \
//     strcpy(s, #vars); \
//     char **strs = split(s, pemdas_debug_enum_delim, &len); \
//     int i = 0; \
//     while (enum_##type_camel##_nums[i] != _enum && i < len) { \
//       i++; \
//     } \
//     return strs[i]; \
//   }
// #endif