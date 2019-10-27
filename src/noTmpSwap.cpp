/*
 * noTmpSwap.cpp
 *
 *  Created on: 2019-08-26
 *      Author: ckirsch
 */
#include "noTmpSwap.h"
#include <iostream>
#include <cassert>
using namespace std;


/* Note could also do a += b, b = a-b & a = a-a */
void noTmpSwap(int &a, int &b)
{
	a = a ^ b; // xor
	b = a ^ b; // b = a
	a = a ^ b; // a = b
}

int noTmpSwapMain()
{
	bool pass = true;

	int a = 5;
	int b = 11;

	noTmpSwap(a, b);
	assert(pass &= (a == 11 && b == 5));

	cout << "Pass: " << pass << endl;
	return 0;
}

