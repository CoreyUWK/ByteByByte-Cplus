/*
 * targetSum.cpp
 *
 *  Created on: 2019-09-21
 *      Author: ckirsch
 */
#include "targetSum.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/* Given an array of integers, nums and a target value T, find the
number of ways that you can add and subtract the values in
nums to add up to T.
eg.
nums = {1, 1, 1, 1, 1}
T = 3
1 + 1 + 1 + 1 - 1
1 + 1 + 1 - 1 + 1
1 + 1 - 1 + 1 + 1
1 - 1 + 1 + 1 + 1
-1 + 1 + 1 + 1 + 1
targetSum(nums, T) = 5 */

/* Space: O(nums.size) as this is max depth of recusrive tree
 * Time: O(2^n) nodes in recursive tree  */
int targetSum_Recursive(vector<int> &nums, int target, uint i, int sum)
{
	// When gone through every item see if reached target
	if (i >= nums.size())
	{
		return (sum == target) ? 1 : 0;
	}

	// Add item
	int numTargetSumAdd = targetSum_Recursive(nums, target, i + 1, sum + nums[i]);

	// Subtract item
	int numTargetSumSub = targetSum_Recursive(nums, target, i + 1, sum - nums[i]);

	// Combine possibilities by adding and subtracting current value
	return numTargetSumAdd + numTargetSumSub;
}


// Returns number of ways arrays equals to Target
int targetSum_Recursive(vector<int> &nums, int target)
{
	if (nums.size() == 0)
	{
		return 0;
	}

	return targetSum_Recursive(nums, target, 0, 0);
}


/* Space: O(nums.size * (2*sum(nums))) = O(nums.size * sum(nums)) cache size
 * Time: O(nums.size * sum(nums)) as only computing <i,sum> once */
int targetSum_RecursiveMemoization(vector<int> &nums, int target, uint i, int sum,
		unordered_map<int, unordered_map<int,int>> cache)
{
	if (cache.find(i) != cache.end())
	{
		if (cache[i].find(sum) != cache[i].end())
		{
			return cache[i][sum];
		}
	}

	// When gone through every item see if reached target
	if (i >= nums.size())
	{
		cache[i][sum] = (sum == target) ? 1 : 0;
		return cache[i][sum];
	}

	// Add item
	int numTargetSumAdd = targetSum_Recursive(nums, target, i + 1, sum + nums[i]);

	// Subtract item
	int numTargetSumSub = targetSum_Recursive(nums, target, i + 1, sum - nums[i]);

	// Combine possibilities by adding and subtracting current value
	cache[i][sum] = numTargetSumAdd + numTargetSumSub;
	return cache[i][sum];
}

int targetSum_RecursiveMemoization(vector<int> &nums, int target)
{
	if (nums.size() == 0)
	{
		return 0;
	}

	unordered_map<int, unordered_map<int, int>> cache;
	return targetSum_RecursiveMemoization(nums, target, 0, 0, cache);
}


/* Space: O(nums.size() + sum(nums))
 * Time: O(nums.size() + sum(nums)) */
int targetSum_DP(vector<int> &nums, int target)
{
	if (nums.size() == 0)
	{
		return 0;
	}

	int sum = 0;

	// Get sum of all elements in nums to know max depth of recursion/if add all up
	for (auto i : nums) sum += i;

	// Check if nums contains any values
	if (sum == 0)
	{
		return 0;
	}

	// Let each entry in cache represent number of paths equaling sum value
	int cache[nums.size() + 1][(2 * sum) + 1]; // 2*sum for both -sum to sum, +1 for zero center
	fill(&cache[0][0], &cache[0][0] + (sizeof(cache) / sizeof(cache[0][0])), 0);

	// Set sum of zero to one so that it can be carried down, hence beginning one path of sum=0
	cache[0][sum] = 1;

	for (uint i = 1; i <= nums.size(); ++i)
	{
		for (int sumLocal = -sum; sumLocal <= sum; ++sumLocal)
		{
			int sumLocalIndex = sumLocal + sum;
			int prev = cache[i - 1][sumLocalIndex];
			if (prev != 0)
			{
				// Include as +
				cache[i][sumLocalIndex + nums[i - 1]] += prev;

				// Include as -
				cache[i][sumLocalIndex - nums[i - 1]] += prev;
			}
		}
	}

	// Print cache
	for (uint i = 0; i <= nums.size(); ++i)
	{
		for (int sumLocal = -sum; sumLocal <= sum; ++sumLocal)
		{
			int sumLocalIndex = sumLocal + sum;
			cout << cache[i][sumLocalIndex] << " ";
		}
		cout << endl;
	}

	// Return number of paths hitting target at bottom of cache (including all elements in path)
	return cache[nums.size()][sum + target];
}


void targetSumMain()
{
	bool pass = true;

	vector<int> nums = {1, 1, 1, 1, 1};
	int target = 3;

	assert(pass &= (5 == targetSum_Recursive(nums, target)));
	assert(pass &= (5 == targetSum_RecursiveMemoization(nums, target)));
	assert(pass &= (5 == targetSum_DP(nums, target)));

	cout << "Pass: " << pass << endl;
}
