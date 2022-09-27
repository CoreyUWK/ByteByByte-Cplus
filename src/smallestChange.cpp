/*
 * smallestChange.cpp
 *
 *  Created on: 2019-09-08
 *      Author: ckirsch
 */
#include "smallestChange.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <limits>
using namespace std;


/* Function will taking in amount in coin value/cents
 * If curreny coins are in multiples of each other than won't run into situation where
 * can have less coins when using lower coin value
 * 1) using coin values that are multiples
 *    Just remove is able the max amount from value
 * ex. 1,5,10,25 => all are multiples
 * 2) If need to check different arrangments of the coin values
 * ex. 1,3,4 => 3 and 4 are not multiples
 * 6 => 4 + 1 + 1 = 3 coins
 *      3 + 3 = 2 coins
 * hence need to try different combinations and paths
 * 3) Use dynamic programming tabular method O(coin value) space */

// Tree where each node could have n = curreny.size() children, C = value
// exponential? - I think O(n^C) but found online said < O(C^n)
int smallestChange_Recursive(const vector<int> &curreny, int value)
{
	int minChange = value; // Assumes curreny contains a 1 cent value
	for (auto coin : curreny)
	{
		int newValue = value - coin;
		if (newValue >= 0)
		{
			int newMinChange = smallestChange_Recursive(curreny, newValue) + 1;
			if (minChange > newMinChange)
			{
				minChange = newMinChange;
			}
		}
		else
		{
			break;
		}
	}

	return minChange; // Handles base case value == 0
}


// Memoization
int smallestChange_RecursiveDP(const vector<int> &curreny, int value, int cache[])
{
	if (-1 != cache[value])
	{
		return cache[value];
	}

	int minChange = value; // Assumes curreny contains a 1 cent value
	for (auto coin : curreny)
	{
		int newValue = value - coin;
		if (newValue >= 0)
		{
			int newMinChange = smallestChange_RecursiveDP(curreny, newValue, cache) + 1;
			if (minChange > newMinChange)
			{
				minChange = newMinChange;
			}
		}
		else
		{
			break;
		}
	}

	cache[value] = minChange;

	return minChange; // Handles base case value == 0
}


// Memoization
// Think is Time: O(n) and Space O(n) as cacheing each value only once
int smallestChange_RecursiveDP(const vector<int> &curreny, int value)
{
	int cache[value + 1]; // +1 so hashing is direct

	// Setup cache
	cache[0] = 0;
	fill_n(cache + 1, value, -1);

	return smallestChange_RecursiveDP(curreny, value, cache);
}


// Tabulation
int smallestChange_DP(const vector<int> &curreny, int value)
{
	int cache[value + 1]; // +1 so hashing is direct

	// Setup cache
	cache[0] = 0;
	fill_n(cache + 1, value, std::numeric_limits<int>::max());

	// Iterate cache array
	for (int amount = 1; amount <= value; ++amount)
	{
		// Go through all coins and find min number of coins with cache
		for (auto coin : curreny)
		{
			// check if can use coin goes into amount
			if (coin <= amount)
			{
				// since cache tracking min number of coins for a value amount
				// don't need recursion, just compare cache
				cache[amount] = min(cache[amount - coin] + 1, cache[amount]);
			}
		}
	}

	return cache[value];
}


void smallestChangeMain()
{
	bool pass = true;

	vector<int> curreny = {1,3,4};
	assert(pass &= (2 == smallestChange_Recursive(curreny, 6)));
	assert(pass &= (2 == smallestChange_RecursiveDP(curreny, 6)));
	assert(pass &= (2 == smallestChange_DP(curreny, 6)));

	curreny = {1,5,10,25};
	assert(pass &= (4 == smallestChange_Recursive(curreny, 32)));
	assert(pass &= (4 == smallestChange_RecursiveDP(curreny, 32)));
	assert(pass &= (4 == smallestChange_DP(curreny, 32)));

	cout << "Pass: " << pass << endl;
}

