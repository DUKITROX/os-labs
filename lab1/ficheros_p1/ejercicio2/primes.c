/* 
 * Program: Sum of the first n prime numbers. 
 * Reads an optional command-line argument n (defaults to 10), allocates an
 * array with the first n primes, and prints their sum.
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * This function takes an array of integers and returns the sum of its n elements.
 */
int sum(int *arr, int n);

/**
 * This function fills an array with the first n prime numbers.
 */
void compute_primes(int* result, int n);

/**
 * This function returns 1 if the integer provided is a prime, 0 otherwise.
 */
int is_prime(int x);

int main(int argc, char **argv) {

  int n = 10; // by default the first 10 primes
  if(argc == 2) {
    n = atoi(argv[1]); // replace default if user provided a value
  }
  // Reserve space for the list of primes we will generate.
  int* primes = (int*)malloc(n*sizeof(int));
  // Populate the array with the first n prime numbers.
  compute_primes(primes, n);

  // Sum and report the primes that were generated.
  int s = sum(primes, n);
  printf("The sum of the first %d primes is %d\n", n, s);

  free(primes);
  return 0;
}

int sum(int *arr, int n) {
  int i;
  int total=0;
  for(i=0; i<n; i++) {
    // Accumulate the running total of the array elements.
    total += arr[i];
  }
  return total;
}

void compute_primes(int* result, int n) {
  int i = 0;
  int x = 2;
  while(i < n) {
    // Only store numbers that pass the primality test.
    if(is_prime(x)) {
      result[i] = x;
      i++;
    }
    // Check the next integer candidate.
    x++;
    
  }
  return;
}

int is_prime(int x) {
  if(x < 2) {
    // 0 and 1 are not primes by definition.
    return 0;
  }
  for(int i=2; i<x; i++) {
    // If x is divisible by any number other than 1 and itself, it is not prime.
    if(x % i == 0) {
      return 0;
    }
  }
  return 1;
}
