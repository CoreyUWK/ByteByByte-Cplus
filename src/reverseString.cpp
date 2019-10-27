/*
 * reverseString.cpp
 *
 *  Created on: 2019-09-01
 *      Author: ckirsch
 */
#include "reverseString.h"
#include <cassert>
#include <stack>
#include <iostream>
using namespace std;


/* Loop over all characters in O(n) and string concating would be in total 1 + 2 + 3 + ... + n = (n*(n+1)) / 2
 * => O(n + n*(n+1)/2 ) = O(n^2) */
string reverseString1(string s)
{
	string output = "";
	for (char c : s)
	{
		output = c + output; // This will create a new temporary buffer of (c + output) and put to output
	}

	return output;
}


string reverseString2(string s)
{
	string output = "";
	output.reserve(s.size());

	stack<char> st;
	for (char c : s)
	{
		st.push(c);
	}

	while (!st.empty())
	{
		char top = st.top();
		st.pop();

		output += top;
	}

	return output;
}


string reverseString3(string s)
{
	string output = s;
	for (int i = 0, j = output.size()- 1; i < j; ++i, --j)
	{
		int tmp = output[i];
		output[i] = output[j];
		output[j] = tmp;
	}

	return output;
}


void reverseStringMain()
{
	bool pass = true;

	assert(pass &= ("dcba" == reverseString1("abcd")));
	assert(pass &= ("dcba" == reverseString2("abcd")));
	assert(pass &= ("dcba" == reverseString3("abcd")));

	cout << "Pass: " << pass << endl;
}


