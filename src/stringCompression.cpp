/*
 * stringCompression.cpp
 *
 *  Created on: 2019-09-10
 *      Author: ckirsch
 */
#include "stringCompression.h"
#include <iostream>
#include <cassert>
using namespace std;

/* Given a string compress by shortening every sequence of same character to character followed
 * by number of repetitions. If compressed string is longer than original should return orignal
 * string */

string stringCompression(string s)
{
	const int maxSequence = 2;
	if (s.size() <= maxSequence)
	{
		return s;
	}

	string smallString;
	int repeat = 1;

	for (uint i = 1; i < s.size(); ++i)
	{
		if (s[i] != s[i-1])
		{
			smallString += s[i-1];
			smallString += std::to_string(repeat);

			// update for current i character
			repeat = 1;
		}
		else
		{
			++repeat;
		}
	}

	// Add Last one
	smallString += s[s.size() - 1];
	smallString += std::to_string(repeat);

	return (smallString.size() < s.size()) ? smallString : s;
}


void stringCompressionMain()
{
	bool pass = true;

	assert(pass &= ("a" == stringCompression("a")));
	assert(pass &= ("a3" == stringCompression("aaa")));
	assert(pass &= ("a3b3" == stringCompression("aaabbb")));
	assert(pass &= ("a3b1c3" == stringCompression("aaabccc")));

	assert(pass &= ("a3b1c2d4e2" == stringCompression("aaabccddddee")));

	cout << "Pass: " << pass << endl;
}
