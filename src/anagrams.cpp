/*
 * anagrams.cpp
 *
 *  Created on: 2019-09-10
 *      Author: ckirsch
 */
#include "anagrams.h"
#include <iostream>
#include <cassert>
#include <bits/stdc++.h>

using namespace std;

/* An anagram is a word or phrase formed by rearranging the letters of a different word
 * or phrase, typically using all the original letters exactly once */

// Assuming lower case and only alphbet characters O(m+n)
bool isAnagram(string s1, string s2)
{
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

    if (s1.size() != s2.size())
	{
		return false;
	}

	const int asciiTableSize = 256; // 1 << 8 = 1 byte
	int hash[asciiTableSize] = {0};

	// Go through string 1 and increament
	for (char c : s1)
	{
		++hash[(int)c];
	}

	// Go through string 2 and decreament
	for (char c : s2)
	{
		--hash[(int)c];
	}

	// Go through and check nothing left in hash, so all characters match
	for (int i = 0; i < asciiTableSize; ++i)
	{
		if (hash[i] != 0)
		{
			return false;
		}
	}

	return true;
}


void anagramsMain()
{
	bool pass = true;

	assert(pass &= isAnagram("hello", "lohel"));
	assert(pass &= (false == isAnagram("hello world", "lohelorwld")));

	cout << "Pass: " << pass << endl;
}
