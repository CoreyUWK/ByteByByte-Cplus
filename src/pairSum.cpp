/*
 * pairSum.cpp
 *
 *  Created on: 2019-08-02
 *      Author: ckirsch
 */
#include "threeSum.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_set>

using namespace std;


bool findPairSumLinear(const vector<int> &list, int sum)
{
	int lowIdx = 0;
	int hiIdx = list.size();

	while (lowIdx < hiIdx)
	{
		int sumCheck = list[lowIdx] + list[hiIdx];
		if (sumCheck == sum)
		{
			return true;
		}
		else if (sumCheck < sum)
		{
			++lowIdx;
		}
		else
		{
			--hiIdx;
		}
	}

	return false;
}


bool findPairSumHash(const vector<int> &list, int sum)
{
	unordered_set<int> hash;

	for (int val : list)
	{
		if (hash.find(val) != hash.end())
		{
			return true;
		}
		else
		{
			hash.insert(sum - val);
		}
	}

	return false;
}


int pairSumMain()
{
	bool pass = true;

	vector<int> list1{1,2,3,9};
	vector<int> list2{1,2,4,4};

	assert(pass &= (false == findPairSumLinear(list1, 8)));
	assert(pass &= (false == findPairSumHash(list1, 8)));

	assert(pass &= (true ==findPairSumHash(list2, 8)));
	assert(pass &= (true ==findPairSumHash(list2, 8)));

	cout << "Pass: " << pass << endl;

	return 0;
}
