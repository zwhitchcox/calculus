 #ifndef __PEDMAS_PRIME__
 #define __PEDMAS_PRIME__
 struct LLLinkedList {
   int num;
   struct LLLinkedList *next;
 };
struct LLLinkedList *sieve_of_eratosthenes(int max);
// this may change later to use, e.g. sieve of atkin
#define get_primes(max) sieve_of_eratosthenes(max)
 #endif