/*
 * bigIntModulus.cpp
 *
 *  Created on: 2019-08-28
 *      Author: ckirsch
 */
#include "bigIntModulus.h"
#include <iostream>
#include <cassert>
#include <cstdint>

using namespace std;

/* When performing modules == remainder of division
 * ex. 15 / 3 = 5 r0 so => 15 % 3 = 0
 * for a byte value -> 255 % 7 = 3 as 255 / 7 = 36 r3 since 36*7=252 so 255-252=3
 *
 * when long division is performed after collecting next remainder you shift it to next position of
 * number system by (multiply by 10 for decimal or multiply by 256 for hex==shift by 8bits for hex)
 * and get next remainder till done
 *
 * For this question we are working with hex system and an array of values
 * ex. 0x03 0xED == 0x03ED where (0x03 << 8) | 0xED
 * if you find the remainder for MSByte(0x03) and the shift it by number system as if you were actually working with the combined 0x03ED
 * then moved to the next byte(0xED) and added the shifted previous remainder with the remainder.
 * This could be done one hex digit at a time and multiply remainder by 16 but will get same result when dealing with 2 hex values = 1 byte as thats what array is */
int bigIntModulus(const uint8_t bytes[], int length, int divisor)
{
	int remainder = 0;

	for (int i = 0; i < length; ++i)
	{
		remainder <<= 8; // Same as multiply 255
		remainder += (bytes[i] & 0xFF);
		remainder %= divisor;
	}

	return remainder;
}

int bigIntModulusMain()
{
	bool pass = true;

	int divisor = 10;
	uint8_t bytes[] = {0x03, 0xED};
	int size = sizeof(bytes) / sizeof(bytes[0]);
	assert(pass &= (5 == bigIntModulus(bytes, size, divisor)));

	uint8_t bytes2[] = {0x12, 0x34, 0x56, 0x78};
	size = sizeof(bytes2) / sizeof(bytes2[0]);
	assert(pass &= (6 == bigIntModulus(bytes2, size, divisor)));

	cout << "Pass: " << pass << endl;

	return 0;
}
