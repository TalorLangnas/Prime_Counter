#include "algorithms.h"

// The naive function for checking if a number is prime 
// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}


// isPrime[] : isPrime[i] is true if number is prime 
// prime[] : stores all prime number less than N
// SPF[] that store smallest prime factor of number
// [for Exp : smallest prime factor of '8' and '16'
// is '2' so we put SPF[8] = 2 , SPF[16] = 2 ]
// bool isprime[MAX_SIZE];
// int prime[MAX_SIZE];
// int SPF[MAX_SIZE];
// int prime_count = 0;

// function generate all prime number less than N in O(n)
int* manipulated_sieve(int N) // prime and prime_count are global variables
{   
    prime = (int *)malloc(sizeof(int) * N);
    if(!prime){
        fprintf(stderr, "Failed to allocate memory for prime\n");
        return NULL;
    }
    int *SPF = (int *)malloc(sizeof(int) * N);
    if(!SPF){
        fprintf(stderr, "Failed to allocate memory for SPF\n");
        return NULL;
    }
    bool *isprime = (bool *)malloc(sizeof(bool) * N);
    if(!isprime){
        fprintf(stderr, "Failed to allocate memory for isprime\n");
        return NULL;
    }
    // 0 and 1 are not prime
    isprime[0] = isprime[1] = false;

    // Initialize the isprime array
    for (int i = 2; i < N; i++)
    {
        isprime[i] = true;
    }

    // Fill rest of the entries
    for (int i = 2; i < N; i++)
    {
        // If isPrime[i] == True then i is
        // prime number
        if (isprime[i])
        {
            // put i into prime array
            prime[(*prime_count)++] = i;

            // A prime number is its own smallest
            // prime factor
            SPF[i] = i;
        }

        // Remove all multiples of i*prime[j] which are
        // not prime by making isPrime[i*prime[j]] = false
        // and put smallest prime factor of i*Prime[j] as prime[j]
        // [ for exp :let i = 5 , j = 0 , prime[j] = 2 [ i*prime[j] = 10 ]
        // so smallest prime factor of '10' is '2' that is prime[j] ]
        // this loop run only one time for number which are not prime
        for (int j = 0; j < *prime_count && i * prime[j] < N && prime[j] <= SPF[i]; j++)
        {
            isprime[i * prime[j]] = false;

            // put smallest prime factor of i*prime[j]
            SPF[i * prime[j]] = prime[j];
        }
    }
    free(SPF);
    free(isprime);
    return prime;
}

bool check_prime(int x){
    int i = 0;

    if(x <= 1){
        return false;
    }
    
    while(i < *prime_count){
        if(x % prime[i] == 0){
            return false;
        }
        if(prime[i] * prime[i] > x){
            return true;
        }
        i++;
    }
    printf("exceed the prime_count, return false as default value\n");
    return false;    
}

