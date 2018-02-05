#include "lcg.h"

unsigned long getNextRandomValue(struct 
	LinearCongruentialGenerator* lcg);
struct LinearCongruentialGenerator makeLCG(unsigned long m, 
	unsigned long c);

long findPrimes(unsigned long n, int test, long product);

/***************************************************************/
/* Initialize an LCG with modulus m and increment c.           */
/* Calculate multiplier a such that:                           */
/*        a = 1+2p, if 4 is a factor of m, otherwise, a = 1+p. */
/*        p = (product of m’s unique prime factors).           */
/* Seed value x is same as increment c.                        */
/***************************************************************/
struct LinearCongruentialGenerator makeLCG(unsigned long m,
	unsigned long c)
{	
	struct LinearCongruentialGenerator myStruct;
	unsigned long p;

	if ((m > 0) && (c < m) && (c >= 0))
	{
		p = findPrimes(m, 2, 1);
		myStruct.m = m;
		myStruct.c = c;
		myStruct.x = myStruct.c;

		if (m % 4 == 0)
		{	
			myStruct.a = 1+2*p;
		}
		else
		{
			myStruct.a = 1+p;
		}
	}
	else
	{
		myStruct.m = 0;
		myStruct.x = 0;
		myStruct.c = 0;
		myStruct.a = 0;
	}

	if (myStruct.a > m || myStruct.a < 0)
	{
		myStruct.m = 0;
		myStruct.x = 0;
		myStruct.c = 0;
		myStruct.a = 0;
	}
	return myStruct;
}

/* Update lcg and return next value in the sequence. */
unsigned long getNextRandomValue(struct 
	LinearCongruentialGenerator* lcg)
{
	unsigned long tempX = lcg -> x;
	lcg->x = ((lcg->a)*(tempX) + lcg->c)%(lcg->m);
	return tempX;
}

/***************************************************************/
/* Helper functions used to find product of unique primes of M */
/* Parameters: modulus m, divisor, initia product 	  		   */
/* returns: product of unique primes                           */
/***************************************************************/
long findPrimes(unsigned long n, int test, long product)
{
	if (test*test > n) return product*n;

	if (n % test == 0)
	{
		product *= test;
		while(n % test == 0)
		{
			n /= test;
		}
	}
	test++;
	return findPrimes(n, test, product);
}
