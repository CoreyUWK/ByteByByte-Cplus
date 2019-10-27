/*
 * rotateBits.cpp
 *
 *  Created on: 2019-07-28
 *      Author: ckirsch
 */
#include "rotateBits.h"
#include <cstdint>
#include <iostream>
using namespace std;

static const uint32_t BITS_IN_U32 = 32;
enum shiftDirection
{
	shiftDirectionLeft,
	shiftDirectionRight
};

uint32_t rotateBits(uint32_t val, int bits, shiftDirection d)
{
	return (d == shiftDirectionRight) ? (val >> bits) | (val << (BITS_IN_U32 - bits)) :
			(val << bits) | (val >> (BITS_IN_U32 - bits));
}


int rotateBitesMain()
{
	uint32_t val = 0xFFFF0000;
	printf("0x%08x to 0x%08x\n", val, rotateBits(val, 8, shiftDirectionRight));

	val = 0x12345678;
	printf("0x%08x to 0x%08x\n", val, rotateBits(val, 16, shiftDirectionRight));

	return 0;
}
