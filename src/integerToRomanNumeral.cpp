/*
 * integerToRomanNumeral.cpp
 *
 *  Created on: 2019-09-03
 *      Author: ckirsch
 */
#include "integerToRomanNumeral.h"
#include <cassert>
#include <iostream>
#include <array>
using namespace std;


const array<int, 13> romanNumeralValue =     {1,   4,    5,   9,    10,  40,   50,  90,   100, 400,
	    500, 900,  1000};
const array<string, 13> romanNumeralString = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD",
		"D", "CM", "M"};

/* Could have done this with a recurisve method trying out all combinations as can't have more than
 * three of the same roman numerial, or could just use a loop to perform an O(n) lookup */
string integerToRomanNumeral(uint num)
{
	string numeral = "";
	int i = romanNumeralValue.size() - 1;
	while (num > 0 && i >= 0)
	{
		int newNum = num - romanNumeralValue[i];
		if (newNum >= 0)
		{
			numeral += romanNumeralString[i];
			num = newNum;
		}
		else
		{
			--i;
		}
	}

	return numeral;
}

void integerToRomanNumeralMain()
{
	bool pass = true;

	assert(pass &= ("I" == integerToRomanNumeral(1)));
	assert(pass &= ("IV" == integerToRomanNumeral(4)));
	assert(pass &= ("XLIX" == integerToRomanNumeral(49)));
	assert(pass &= ("MMXVII" == integerToRomanNumeral(2017)));

	cout << "Pass: " << pass << endl;
}
