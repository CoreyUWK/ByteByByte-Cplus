/*
 * threeSum.cpp
 *
 *  Created on: 2019-07-28
 *      Author: ckirsch
 */
#include "threeSum.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>

using namespace std;


template <int N>
vector<array<int,3>> threeSum(array<int,N> arr)
{
	vector<array<int,3>> results;

	sort(arr.begin(), arr.end());

	for (int start = 0, end = N - 1; start < end && arr[start] < 0;)
	{
		for (int mid = start + 1, end = N - 1; mid < end;)
		{
			int sum = arr[start] + arr[mid] + arr[end];

			if (sum == 0)
			{
				results.push_back({arr[start], arr[mid], arr[end]});
				while (arr[mid] == arr[++mid] && mid < end);
			}
			else if (sum < 0)
			{
				while (arr[mid] == arr[++mid] && mid < end);
			}
			else
			{
				while (arr[end] == arr[--end] && mid < end);
			}
		}

		while (arr[start] == arr[++start] && start < end);
	}

	return results;
}


int threeSumMain()
{
	bool pass = true;
	const int N = 6;
	array<int,N> arr1 = {-1, 0, 1, 2, -1, -4};
	array<int,8> arr2 = {-4, -3, -1, 0, 1, 3, 4, 5};

	// 1
	vector<array<int,3>> result = threeSum<N>(arr1);
	assert(pass &= (2 == result.size()));

	// 2
	result.empty();
	result = threeSum<8>(arr2);
	assert(pass &= (6 == result.size()));

	cout << "Pass: " << pass << endl;

	return 0;
}


