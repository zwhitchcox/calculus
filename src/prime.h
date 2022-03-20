 #ifndef __PEMDAS_PRIME__
 #define __PEMDAS_PRIME__
 #include "common.h"
 struct LLInt {
   ll_t num;
   struct LLInt *next;
 };
struct LLInt *sieve_of_eratosthenes(ll_t max);
struct LLInt *new_llint(ll_t num);
// this may change later to use, e.g. sieve of atkin
#define get_primes(max) sieve_of_eratosthenes(max)
 #endif