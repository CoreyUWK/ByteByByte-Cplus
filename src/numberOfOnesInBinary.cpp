/*
 * numberOfOnesInBinary.cpp
 *
 *  Created on: 2019-09-08
 *      Author: ckirsch
 */
#include "numberOfOnesInBinary.h"
#include <iostream>
#include <cassert>
using namespace std;


int numberOfOnesInBinary(int x)
{
	int count = 0;

	while (x > 0)
	{
		count += (x & 1);
		x >>= 1;
	}

	return count;
}


void numberOfOnesInBinaryMain()
{
	bool pass = true;

	assert(pass &= (4 == numberOfOnesInBinary(58)));

	cout << "Pass: " << pass << endl;
}
