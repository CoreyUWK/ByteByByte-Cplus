/*
 * zeroSumSubArray.cpp
 *
 *  Created on: 2019-07-29
 *      Author: ckirsch
 */

#include "zeroSumSubArray.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>

using namespace std;


/* assuming SubArray can contain 1 element and array can contain a 0 *
 * Note: could return index range instead of a new array
 * for performance could return a linked list as can O(1) pop */
template <int N>
vector<int> zeroSumSubArray(array<int, N> arr)
{
	int sum; // running sum to find subArray summing to zero
	/* initially made sum a array, then found usage is only on latest entry so can make single.
	 * Initially made sum[0] = arr[0], but after coding solution found vector copy from start + 1 to end + 1
	 * so if make sum[0]=0, sum[1]=arr[0], sum[2]=arr[1] + sum[1], ... then copy won't have +1 */

	unordered_map<int, int> hash; // to find if sum already occurred and map to array index to find start of range

	if (N == 0)
	{
		return vector<int>{};
	}
	else if (arr[0] == 0)
	{
		return vector<int>{0};
	}

	// Create Sum array
	sum = arr[0];
	hash[sum] = 0;
	for (int i = 1; i < N; ++i)
	{
		sum += arr[i];

		// Check if subarray sum's to zero
		if (hash.find(sum) != hash.end())
		{
			int start = hash[sum] + 1;
			return vector<int>{arr.begin() + start, arr.begin() + i + 1};
		}
		// Check if value is zero
		else if (sum == 0)
		{
			return vector<int>{arr.begin(), arr.begin() + i + 1};
		}

		hash[sum] = i;
	}

	return vector<int>{};
}


int zeroSumSubArrayMain()
{
	bool pass = true;

	// 1
	const int N1 = 6;
	array<int, N1> arr1{1, 2, -5, 1, 2, -1};
	vector<int> subarry1 = zeroSumSubArray<N1>(arr1);
	assert(pass &= (subarry1 == vector<int>{2, -5, 1, 2}));

	// 2
	const int N2 = 8;
	array<int, N2> arr2{9,-7,-5,0,-1,5,8,11};
	vector<int> subarry2 = zeroSumSubArray<N2>(arr2);
	assert(pass &= (subarry2 == vector<int>{0}));

	// 3
	const int N3 = 5;
	array<int, N3> arr3{2,3,-4,-1,6};
	vector<int> subarry3 = zeroSumSubArray<N3>(arr3);
	assert(pass &= (subarry3 == vector<int>{2,3,-4,-1}));

	// 4
	const int N4 = 5;
	array<int, N4> arr4{2,3,-3,-4,5};
	vector<int> subarry4 = zeroSumSubArray<N4>(arr4);
	assert(pass &= (subarry4 == vector<int>{3,-3}));

	cout << "Pass: " << pass << endl;

	return 0;
}
