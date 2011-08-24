## Implementation of the Sieve of Eratosthenes

Here we've implemented a Sieve of Eratosthenes using bit-strings. Each
bit in the bit string represents it's index-1 *(the 3rd bit represents the number 2)*.
If it is 0, then it's prime, else it's composite.

We start off with 2, mark each multiple of 2 with a 1. Then we move to the next non-1 
element in the list, set that bit's index-1 as our currentIndex, and mark off all multiples of that.

In this implementation we've used integers, but if you want to go above INT_MAX, change
the datatypes from int to something like long.

The program requires **O(N) space**. Max = 10^9 will require (10^9/8) bytes, or around 125 MegaBytes.
Similarly, Max = 10^12 would require 125 GigaBytes of space. 

The running time of this algorithm is:

n/2 + n/3 + n/5 + ... + n/lastPrimeOf(n)

n*(1/2 + 1/3 + 1/5 + ... + 1/lastPrimeOf(n))

This is defined as the prime harmonic series. This implies the complexity, in a machine which 
has constant time access to memory (such as RAM), n * (ln(ln(n+1)) -ln(pi^2/6). Or,
**O(n*ln*ln(n))**.