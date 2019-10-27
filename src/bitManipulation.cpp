/*
 * bitManipulation.cpp
 *
 *  Created on: 2019-08-06
 *      Author: ckirsch
 */
#include <iostream>
#include <cassert>
#include <algorithm>
#include <array>
#include <unordered_map>
using namespace std;


int repeatedLogicalShift(int x, int count)
{
	return (x >> count); // Logical right shift
}


/* Want to maintain 1's in shift
-10 = (~10 + 1) = 2's complement
10 = 0000 1010
~10 = 1111 0101
~10 + 1 = 1111 0110 = -10
-10 >> 1 = -5 = 1111 1011

Ex.
xShifted = 1111 0110 >> 4 = 0000 1111
numberOfBitsInX = 8
mask = (0000 1111) << 4 = 1111 0000
result = 1111 1111
*/
int repeatedArithmeticShift(int x, int count)
{
	int xShifted = repeatedLogicalShift(x, count);

	const int numberOfBitsInX = sizeof(x) * 8;
	int mask = ((1 << count) - 1) << (numberOfBitsInX - count);

	return (xShifted | mask);
}


int bitManipulationMain()
{
	bool pass = true;

	assert(pass &= (0 == repeatedArithmeticShift(-93242, 40)));

	return 0;
}
