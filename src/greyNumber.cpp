/*
 * greyNumber.cpp
 *
 *  Created on: 2019-08-04
 *      Author: ckirsch
 */
#include <cassert>
#include <cstdint>
#include <iostream>
using namespace std;


bool greyNumber(uint32_t a, uint32_t b)
{
	uint32_t c = a ^ b;
	return (((c - 1) & c) == 0) ? true : false;
}


int greyNumberMain()
{
	bool pass = true;

	assert(pass &= (true == greyNumber(0, 1)));
	assert(pass &= (false == greyNumber(1, 2)));

	cout << "Pass: " << pass << endl;

	return 0;
}
