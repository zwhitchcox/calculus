 #ifndef __PEMDAS_PRIME__
 #define __PEMDAS_PRIME__
 struct LLInt {
   int num;
   struct LLInt *next;
 };
struct LLInt *sieve_of_eratosthenes(int max);
// this may change later to use, e.g. sieve of atkin
#define get_primes(max) sieve_of_eratosthenes(max)
 #endif