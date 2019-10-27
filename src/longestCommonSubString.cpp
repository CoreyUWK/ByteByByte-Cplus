/*
 * longestCommonSubString.cpp
 *
 *  Created on: 2019-08-18
 *      Author: ckirsch
 */
#include "longestCommonSubString.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_set>

using namespace std;


// This is an O(n^2) algo
string longestCommonSubString(const string s1, const string s2)
{
	unordered_set<string> hash;
	string maxSubString = "";

	// Pre-compute s1 substrings
	for (uint i = 0; i < s1.size(); ++i)
	{
		for (uint j = i; j < s1.size(); ++j)
		{
			string subString = s1.substr(i, (j - i) + 1);
			hash.insert(subString);
		}
	}

	// Find matching
	for (uint i = 0; i < s2.size(); ++i)
	{
		for (uint j = i; j < s2.size(); ++j)
		{
			string subString = s2.substr(i, (j - i) + 1);
			if (hash.find(subString) != hash.end())
			{
				if (maxSubString.size() < subString.size())
				{
					maxSubString = subString;
				}
			}
		}
	}

	return maxSubString;
}


// Dynamic programming option O(n*m)
string longestCommonSubStringDynamic(const string s1, const string s2)
{
	string maxSubString = "";
	const string *horizontal = NULL;
	const string *vertical = NULL;

	if (s1.size() == 0 || s2.size() == 0)
	{
		return maxSubString;
	}

	if (s1.size() >= s2.size())
	{
		horizontal = &s1;
		vertical = &s2;
	}
	else
	{
		horizontal = &s2;
		vertical = &s1;
	}

	uint matrix[vertical->size()][horizontal->size()] = {};

	for (uint i = 0; i < vertical->size(); ++i)
	{
		for (uint j = 0; j < horizontal->size(); ++j)
		{
#ifdef LONGEST_COMMON_SUBSTRING_DEBUG_PRINT
			cout << horizontal->at(j) << " " << vertical->at(i) << endl;
#endif
			// Check if value match at index
			if (horizontal->at(j) == vertical->at(i))
			{
				if (i == 0 || j == 0)
				{
					matrix[i][j] = 1;
				}
				else
				{
					matrix[i][j] = matrix[i - 1][j - 1] + 1;
				}

				// Update longest substring
				if (maxSubString.size() < matrix[i][j])
				{
					maxSubString = horizontal->substr(j - matrix[i][j] + 1, matrix[i][j]);
				}
			}
		}
	}

	return maxSubString;
}


int longestCommonSubStringMain()
{
	bool pass = true;
	const string s1 = "ABAB";
	const string s2 = "BABA";
	string out = "";

	out = longestCommonSubString(s1,s2);
	assert(pass &= ("ABA" == out || "BAB" == out));
	cout << out << endl;

	out = longestCommonSubStringDynamic(s1,s2);
	assert(pass &= ("ABA" == out || "BAB" == out));
	cout << out << endl;

	cout << "Pass: " << pass << endl;
	return 0;
}
