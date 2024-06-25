#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#define SIEVE_NUM 100001 // the Number for sieve algorithm - generate 9,592 prime numbers - size: 880.0 kb


extern int *prime;
extern int *prime_count;

int* manipulated_sieve(int N);
bool check_prime(int x);
bool isPrime(int n);


#endif