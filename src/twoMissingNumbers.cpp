/*
 * twoMissingNumbers.cpp
 *
 *  Created on: 2019-08-29
 *      Author: ckirsch
 */
#include "twoMissingNumbers.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;


// 1) sort list O(nlogn) and then search for missing O(n) => Time O(nlogn), Space O(1)
// 2) hash array O(n) and then go through all expected values i to N and check if exists in hash O(n) => Time O(n), Space O(n)
// Could subtract two hash's with .erase()
// 3) (Chosen) xor array O(n), xor expected i to N O(n), then xor the two together to get missing => time O(n), space O(1)
int oneMissingNumber(vector<int> arr)
{
	int arrXor = 0;
	int totalXor = 0;

	// Xor all in array => ex. 1 ^ 2 ^ 4
	for (auto i : arr)
	{
		arrXor ^= i;
	}

	// Xor all in expected range => ex. 1 ^ 2 ^ 3 ^ 4
	for (uint i = 1; i <= (arr.size() + 1); ++i)
	{
		totalXor ^= i;
	}

	// return (1 ^ 2 ^ 4) ^ (1 ^ 2 ^ 3 ^ 4) = 3
	return arrXor ^ totalXor;
}


// Could do like above 1) or 2)
// Solving with XOR idea, if using addition could have overflows => O(n)
pair<int, int> twoMissingNumbers(vector<int> arr)
{
	// 1) Find point where one missing number on one side (less than) and second missing on other side (greater than)

	int totalSize = arr.size() + 2;
	// Sum of expected range = arr.size + 2 => 1 + 2 + 3 + 4 + ... + N + (N + 1) + (N + 2) = [(N + 2) * ((N + 2) + 1)] / 2
	long totalSum = (totalSize * (totalSize + 1)) / 2;
	long arrSum = 0;
	for (auto i : arr)
	{
		arrSum += i;
	}

	// Therefore, have totalSum, arrSum => totalSum - arrSum = missing sum
	int missingSum = totalSum - arrSum;
	int pivotPoint = missingSum / 2;  // Will have first missing <= pivot, and second > pivot

	// Xor for <= pivot to find missing number
	int firstTotalXor = 0;
	int secondTotalXor = 0;
	for (int i = 1; i <= totalSize; ++i)
	{
		if (i <= pivotPoint)
		{
			firstTotalXor ^= i;
		}
		else
		{
			secondTotalXor ^= i;
		}
	}

	int firstXor = 0;
	int secondXor = 0;
	for (auto i : arr)
	{
		if (i <= pivotPoint)
		{
			firstXor ^= i;
		}
		else
		{
			secondXor ^= i;
		}
	}

	int firstMissing = firstTotalXor ^ firstXor;
	int secondMissing = secondTotalXor ^ secondXor;

	return make_pair(firstMissing, secondMissing);
}


int twoMissingNumbersMain()
{
	bool pass = true;

	vector<int> arr = {3,4,5};
	assert(pass &= ((make_pair(1,2) == twoMissingNumbers(arr))));

	arr = {2,3,4};
	assert(pass &= ((make_pair(1,5) == twoMissingNumbers(arr))));

	arr = {1,2,3};
	assert(pass &= ((make_pair(4,5) == twoMissingNumbers(arr))));

	cout << "Pass: " << pass << endl;

	return 0;
}
