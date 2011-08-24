/*
Created by David Killmon on August 24th, 2011.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	/*
		Here we've implemented a Sieve of Eratosthenes using bit-strings. Each
		bit in the array represents a number. If it is 0, then it's prime, else it's composite.
		
		We start off with 2, mark each multiple of 2 with a 1. Then we move to the next non-1 
		element in the list, set that as our currentIndex, and mark off all multiples of that.
		
		In this implementation we've used integers, but if you want to go above INT_MAX, change
		the datatypes from int to something like long.
		
		The program requires O(N) space. Max = 10^9 will require (10^9/8) bytes, or around 125 MegaBytes
		of space. Similarly, Max = 10^12 would require 125 GigaBytes of space. 
		
		The running time of this algorithm is:
		
		n/2 + n/3 + n/5 + ... + n/lastPrimeOf(n)
		
		n*(1/2 + 1/3 + 1/5 + ... + 1/lastPrimeOf(n))
		
		This is defined as the prime harmonic series. This implies the complexity, in a machine which 
		has constant time access to memmory (such as RAM), n * (ln(ln(n+1)) -ln(pi^2/6). Or,
		O(n*ln*ln(n)).
	*/
	
	
	// Generate all prime numbers up to, and including max.
	int max = 1000000000;
	
	// Computes the number of bytes we'll need to allocate for our bitstring.
	int bytes = ceil(max/8.0);
	char *bitArray = malloc(bytes*sizeof(char));
	
	// Zero all the bytes. By default, we assume every number is 'prime'. It'll eventually be 1'd out if it's composite.
	int i;
	for(i=0; i<bytes; i++)
	{
		bitArray[i] = 0;
	}
	
	int currentIndex = 2;
	printf("2");
	
	// Current Index is the current prime number. We'll 1 out all multiples of this number
	// up to max.
	while (currentIndex < max)
	{
		for(i = 2; i*currentIndex <= max; i++)
		{
			// Set all multiples of the currentIndex to 1
			int currentTarget = currentIndex*i;
			// Get the current byte we're working on and set the local bit (currentTArget%8) corresponding
			// to the global bit, currentTarget, to 1.
			bitArray[currentTarget/8] = bitArray[currentTarget/8] | (1 << currentTarget%8);
		}
		// Find new index
		int oldIndex = currentIndex;
		for(i= currentIndex+1; i<=max; i++)
		{		
			// If the current candidate, i, is a zero, it is prime. We make it our next index.
			if(!(bitArray[i/8] & (1 << i%8)))
			{
				printf(", %d",i);
				currentIndex = i;
				break;
			}
		}
		// If we don't find any zero's, that means there are no prime numbers. We quit.
		if (currentIndex == oldIndex) break;
	}
	return 0;
	
}