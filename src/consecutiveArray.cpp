/*
 * consecutiveArray.cpp
 *
 *  Created on: 2019-08-30
 *      Author: ckirsch
 */
#include "consecutiveArray.h"
#include <iostream>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

/* Given unsorted array, find longest sequence of consecutive numbers, order does not matter.
[4,2,1,6,5] = 3 [4,5,6]
[5,5,3,1] = 1 [1], [3], or [5]
 */


/* 1) sort and search for consecutive numbers in order, O(nlogn)
 * 2) hash and search in O(n) -> takes up more space than n and only works for positive numbers */
int consecutiveArray_HashArray(const vector<int> &arr)
{
	int maxVal = INT_MIN;
	for (auto i : arr)
	{
		if (maxVal < i)
		{
			maxVal = i;
		}
	}

	vector<bool> hash;
	hash.resize(maxVal + 2, false); // +1 for shift from zero, +1 for extra space for below loop

	for (auto i : arr)
	{
		hash[i] = true;
	}

	int max = 0;
	int localMax = 0;
	bool prevInChain = false;
	for (uint i = 0; i < hash.size() + 1; ++i)
	{
		if (!prevInChain && hash[i])
		{
			localMax = 1;
			prevInChain = true;
		}
		else if (prevInChain && hash[i])
		{
			++localMax;
		}

		if (!hash[i])
		{
			if (max < localMax)
			{
				max = localMax;
			}

			// reset
			localMax = 0;
			prevInChain = false;
		}
	}

	return max;
}


/* 3) Try to use a hashset instead of an array hash to reduce space and work for any values
 * This could be O(n) as really only processing each node once */
int consecutiveArray_HashSet(const vector<int> &arr)
{
	unordered_set<int> hash;
	for (auto i : arr)
	{
		hash.insert(i);
	}

	int max = 0;

	// Go through hash values to find length
	for (auto i : hash)
	{
		// Only process from start on a consecutive sequence, so skip if not at start
		if (hash.find(i - 1) != hash.end())
		{
			continue;
		}

		int localMax = 1;

		// Else process sequence
		while (hash.find(++i) != hash.end())
		{
			++localMax;
		}

		if (max < localMax)
		{
			max = localMax;
		}
	}

	return max;
}


int consecutiveArrayMain()
{
	bool pass = true;

	vector<int> arr = {4, 2, 1, 6, 5};

	assert(pass &= (3 == consecutiveArray_HashArray(arr)));
	assert(pass &= (3 == consecutiveArray_HashSet(arr)));

	cout << "Pass: " << pass << endl;

	return 0;
}

//-------------------------------------
int consecutiveArray_Latest(const vector<int> &arr) {
    int maxConsecutive = 1;
    unordered_map<int, int> hashSet;
    for (auto i : arr) {
        hashSet[i] = 1;
    }
    
    for (auto i : arr) {
        if (hashSet.find(i - 1) != hashSet.end()) {
            hashSet[i] += hashSet[i-1];
            
            if (maxConsecutive < hashSet[i]) {
                maxConsecutive = hashSet[i];
            }
        }
    }
    return maxConsecutive;
}


