/*
 * fibonacci.cpp
 *
 *  Created on: 2019-09-04
 *      Author: ckirsch
 */
#include "fibonacci.h"
#include <cassert>
#include <iostream>
using namespace std;


int fibonacci(int n)
{
	if (n <= 1)
	{
		return n;
	}

	return fibonacci(n - 1) + fibonacci(n - 2);
}


/* Dynamic Programming: Memoization (Top Down)
 * Similar to recursive solution but looks at lookup table for computed solutions, else computes and
 * enteries into lookup */
int fibonacci_Memoization(int lookup[], int n)
{
	if (-1 == lookup[n])
	{
		if (n <= 1)
		{
			lookup[n] = n;
		}
		else
		{
			lookup[n] = fibonacci_Memoization(lookup, n - 1) +
					fibonacci_Memoization(lookup, n - 2);
		}
	}

	return lookup[n];
}


/* Dynamic Programming: Tabulation (Bottom Up)
 * Builds a table bottom up and returns last entry from table. Building up solutions of subproblems
 * bottom up */
int fibonacci_Tabulation(int n)
{
	int lookup[n + 1];

	lookup[0] = 0;
	lookup[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		lookup[i] = lookup[i - 1] + lookup[i - 2];
	}

	return lookup[n];
}


// This takes up less memory than the one above as only need to track previous two values
int fibonacci_Tabulation2(int n)
{
	if (n <= 1)
	{
		return n;
	}

	int a = 0, b = 1;

	for (int i = 2; i <= n; ++i)
	{
		int c = a + b;
		a = b;
		b = c;
	}

	return b;
}


/*
 * Algorithms above aren't the best!
Here's a mathematical trick with matrices:

    [ 1 1 ] n      [ F(n+1) F(n)   ]
    [ 1 0 ]    =   [ F(n)   F(n-1) ]

You can then prove the result above by induction: Let
    A =  [ 1 1 ]
     	 [ 1 0 ]
assume by induction that the equation above is true for some n, multiply both sides by another
power of A using the formula for matrix multiplication, and verify that the terms you get are the
same as the formula defining the Fibonacci numbers.)

The following algorithm initializes a matrix M to the identity matrix (the "zeroth power" of A) and
then repeatedly multiplies M by A to form the (n-1)st power.
Then by the formula above, the top left corner holds F(n), the value we want to return.

Algorithm 4:

    int fib(int n)
    {
		int M[2][2] = {
			{1,0},
			{0,1}
		}

		for (int i = 1; i < n; i++)
			M = M * {
						{1,1},
						{1,0}
					}
		return M[0][0];
    }
This takes time O(n) (so much better than algorithm 1) but is probably somewhat slower than
algorithm 2 or algorithm 3. Like algorithm 3, this uses only O(1) space.

But we can compute M^n more quickly.
The basic idea: if you want to compute e.g. 3^8 you can multiply 8 3's together one at a time (3*3*3*3*3*3*3*3)
or you can repeatedly square: square 3^2 = 9, 9^2 = 3^4 = 81, 81^2 = 3^8 = 6561.
The squaring idea uses many fewer multiplications, since each one doubles the exponent rather than
simply adding one to it. With some care, the same idea works for matrices, and can be extended to
exponents other than powers of two.

Algorithm 5:

    int M[2][2] = {{1,0}{0,1}}

    int fib(int n)
    {
    	matpow(n-1);
    	return M[0][0];
    }

    void matpow(int n)
    {
		if (n > 1) {
			matpow(n/2);
			M = M*M;
		}
		if (n is odd) M = M*{{1,1}{1,0}}
    }
Basically all the time is in matpow, which is recursive: it tries to compute the nth power of A by
squaring the (n/2)th power. However if n is odd, rounding down n/2 and squaring that power of A results
in the (n-1)st power, which we "fix up" by multiplying one more factor of A.
This is a recursive algorithm, so as usual we get a recurrence relation defining time, just by writing
down the time spent in a call to matpow (O(1)) plus the time in each recursive call (only one recursive
call, with argument n/2). So the recurrence is

    time(n) = O(1) + time(n/2)
It turns out that this solves to O(log n).
log n is basically the number of bits needed to write n down in binary.
An equivalent way of defining it is the smallest value of i such that n < 2^i.
But clearly if n < 2^i, n/2 < 2^(i-1) and conversely, so log n satisfies the recurrence log(n) = 1 + log(n/2).
The recurrence defining the time for matpow is basically the same except with O(1) instead of 1.
So the solution to the recurrence is just the sum of log n copies of O(1), which is O(log n).

If n is 1 billion, log n would only be 30, and this algorithm would be better than algorithms 2 and 3
in the same way that they are better than algorithm 1.

(This is actually somewhat cheating: to be able to use this for n equal to a billion you need to be
able to write down the answer which will have O(n) digits, and you need to be able to store variables
with that many digits. Manipulating such large numbers would take more like O(n) steps per operation,
where here we are only counting one step per integer multiplication or addition. But even if you used
a special library for dealing with large numbers, algorithm 4 would be much faster than the other ones.)

Actually you can get the original formula 1.618^n to work using a similar repeated squaring trick, also
with time O(log n). So to tell which is better you have to be more careful and not just use O-notation --
dealing with an integer matrix is somewhat simpler than having to compute floating point square roots so it wins.
*/


void fibonacciMain()
{
	int n = 9;

	// 1
	int result = fibonacci(n);
	cout << "Normal: " << result << endl;
	assert(34 == result);

	// 2
	int lookup[n + 1];
	fill_n(lookup, n + 1, -1);

	result = fibonacci_Memoization(lookup, n);
	cout << "DP_Memoization: " << result << endl;
	assert(34 == result);

	// 3
	result = fibonacci_Tabulation(n);
	cout << "DP Tabulation: " << result << endl;
	assert(34 == result);

	// 4
	// 3
	result = fibonacci_Tabulation2(n);
	cout << "DP Tabulation2: " << result << endl;
	assert(34 == result);
}
