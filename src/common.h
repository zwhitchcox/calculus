#ifndef __PEMDAS_COMMON__
#define __PEMDAS_COMMON__

typedef long long ll_t;

/* debugging */
#define MAX_PEMDAS_ENUM_STR 100*1024
static int count_occurrences(char *str, const char *delim) {
  int delim_len = strlen(delim);
  int count = 0;
  while (*str) {
    if (!strncmp(str, delim, delim_len)) {
      count++;
    }
    str++;
  }
  return count;
}

static char **split(char *str, const char *del, int *len) {
  *len = count_occurrences(str, del);
  char **arr = malloc(sizeof(char*) * (*len));
  char *token = strtok(str, del);
  int i = 0;
  while (token != NULL) {
    arr[i++] = strdup(token);
    token = strtok(NULL, del);
  }
  return arr;
}

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
#endif /* __PEMDAS_COMMON__ */
