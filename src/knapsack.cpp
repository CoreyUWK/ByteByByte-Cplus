/*
 * knapsack.cpp
 *
 *  Created on: 2019-09-03
 *      Author: ckirsch
 */
#include "knapsack.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <chrono>
using namespace std;
using namespace std::chrono;


/* Given list of items with values and weights and max weight, find maximum value can generate from
 * items where sum of weights is less than or equal to max
 *
 * ex. weights = {10, 20, 30}
 *     values = {60, 100, 120}
 *     max weights = 50
 * => 220
 * */


/* This solution creates a binary decision tree so Time = O(2^n)
 * Could think of time complexity to two ways
 * 1) have n items {0, 0, 0} where we can choose that item to be in or not or binary 1 or 0
 * so the options are
 * 1-000
 * 2-001
 * 3-010
 * 4-011
 * 5-100
 * 6-101
 * 7-110
 * 8-111
 * Or max value + 1 = (2^n - 1) + 1 = 2^n
 * 2) Other way of thinking is for every chose two paths get created, so for n choses we have 2^n paths or nodes in tree
 * 3) greedy solution select max viable weighted item till done.
 * Item: [30, 120], [20, 100] => spent the max weight=50 and value=120+100=220
 *  */
int knapsack(int index, const vector<int> &weights, const vector<int> &values, const int maxWeight)
{
	if ((index >= (int)weights.size()) || maxWeight <= 0)
	{
		return 0;
	}

	int maxValueInclude = 0,
		maxValueExclude = 0;
	int newMaxWeight = maxWeight - weights[index];
	if (newMaxWeight >= 0)
	{
		// Include item in knapsack
		maxValueInclude = knapsack(index + 1, weights, values, newMaxWeight) + values[index];
	}

	// Don't include item in knapsack
	maxValueExclude = knapsack(index + 1, weights, values, maxWeight);

	return max(maxValueInclude, maxValueExclude);
}


int knapsack(const vector<int> &weights, const vector<int> &values, const int maxWeight)
{
	return knapsack(0, weights, values, maxWeight);
}


struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};


int knapsack_DpTopDown1(int index, const vector<int> &weights, const vector<int> &values, const int maxWeight,
		unordered_map<pair<int,int>, int, pair_hash> &cache)
{
	if ((index >= (int)weights.size()) || maxWeight <= 0)
	{
		return 0;
	}

	int maxValueInclude = 0,
		maxValueExclude = 0;
	int newMaxWeight = maxWeight - weights[index];
	if (newMaxWeight >= 0)
	{
		// Include item in knapsack
		if (cache.find(make_pair(index + 1, newMaxWeight)) == cache.end())
		{
			cache[make_pair(index + 1, newMaxWeight)] = knapsack(index + 1, weights, values, newMaxWeight);
		}

		maxValueInclude = values[index] + cache[make_pair(index + 1, newMaxWeight)];
	}

	// Don't include item in knapsack
	if (cache.find(make_pair(index + 1, maxWeight)) == cache.end())
	{
		cache[make_pair(index + 1, maxWeight)] = knapsack(index + 1, weights, values, maxWeight);
	}

	maxValueExclude = cache[make_pair(index + 1, maxWeight)];

	return max(maxValueInclude, maxValueExclude);
}


int knapsack_DpTopDown2(int index, const vector<int> &weights, const vector<int> &values, const int maxWeight,
		unordered_map<pair<int,int>, int, pair_hash> &cache)
{
	if ((index >= (int)weights.size()) || maxWeight <= 0)
	{
		return 0;
	}

	auto cacheKey = make_pair(index, maxWeight);

	if (cache.find(cacheKey) != cache.end())
	{
		return cache[cacheKey];
	}

	int maxValueInclude = 0,
		maxValueExclude = 0;
	int newMaxWeight = maxWeight - weights[index];
	if (newMaxWeight >= 0)
	{
		// Include item in knapsack
		maxValueInclude = knapsack(index + 1, weights, values, newMaxWeight);
	}

	// Don't include item in knapsack
	maxValueExclude = knapsack(index + 1, weights, values, maxWeight);

	cache[cacheKey] = max(maxValueInclude, maxValueExclude);

	return cache[cacheKey];
}


int knapsack_DpTopDown(const vector<int> &weights, const vector<int> &values, const int maxWeight)
{
	unordered_map<pair<int,int>, int, pair_hash> cache;
	return knapsack_DpTopDown2(0, weights, values, maxWeight, cache);
}


// Time: O(n*W) and Space: O(n*W) n=# of items, W=max weight
int knapsack_DpBottomUp(const vector<int> &weights, const vector<int> &values, const uint maxWeight,
		vector<int> &knapsackItems)
{
	/* W=5
	 * w's={1,2,3}
	 * v's={6,10,12}
	 *
	 *    0 1 2  3  4  5 W
	 * 0 [0 0 0  0  0  0
	 * 1 [0 6 6  6  6  6
	 * 2 [0 6 10 16 16 16
	 * 3 [0 6 10 16 18 22
	 * i
	 * */
	int cache[values.size() + 1][maxWeight + 1] = {}; //Cache for dynamic programming tabular bottom up build up

	// Iterate over cache - skip first index as it will be zero's using for initial row/col equation, could remove to reduce
	// memory but increase complexity of code as need to skip
	for (uint itemIdx = 1; itemIdx <= values.size(); ++itemIdx) // Row
	{
		for (uint weight = 1; weight <= maxWeight; ++weight) // Column
		{
			// Check if current weight is less than itermediate max weight (column) - hence if less
			// than can try to include value item
			if ((int)weight >= weights[itemIdx - 1])
			{
				cache[itemIdx][weight] = max(cache[itemIdx - 1][weight], // Not seleting current item
						values[itemIdx - 1] + // seleting current item
							cache[itemIdx - 1][weight - weights[itemIdx - 1]]); // max value with what's weight is left
			}
			else
			{
				// Just use previous value as can't add current since not enough weight space left
				cache[itemIdx][weight] = cache[itemIdx - 1][weight];
			}

#ifdef KNAPSACK_DEBUGPRINT
			cout << cache[itemIdx][weight] << " ";
#endif
		}
#ifdef KNAPSACK_DEBUGPRINT
		cout << endl;
#endif
	}

	// Get knapsack items
	int weight = maxWeight;
	int itemIdx = values.size();

	while (weight > 0 && itemIdx > 0)
	{
		// Check if current valueIdx included in knapsack
		if (cache[itemIdx][weight] != cache[itemIdx - 1][weight])
		{
			int index = itemIdx - 1;

			// Add Item
			knapsackItems.push_back(index);

			// Move to next possible item in knapsack
			weight -= weights[index];
			itemIdx -= 1;
		}
		else
		{
			// Move to next possible item in knapsack
			itemIdx -= 1;
		}
	}

	return cache[values.size()][maxWeight];
}


/* Can't get knapsack items from this solution
 * Same as solution knapsack_DpBottomUp above but with reduced memory */
int knapsack_DpBottomUpMin(const vector<int> &weights, const vector<int> &values, const uint maxWeight)
{
	int cachePrev[maxWeight + 1] = {0}; //Cache for dynamic programming tabular bottom up build up
	int cacheCur[maxWeight + 1] = {0};

	// Iterate over cache - skip first index as it will be zero's using for initial row/col equation
	for (uint itemIdx = 1; itemIdx <= values.size(); ++itemIdx) // Row
	{
		for (uint weight = 1; weight <= maxWeight; ++weight) // Column
		{
			// Check if current weight is less than itermediate max weight (column) - hence if less
			// than can try to include value item
			if ((int)weight >= weights[itemIdx - 1])
			{
				cacheCur[weight] = max(cachePrev[weight], // Not seleting current item
						values[itemIdx - 1] + // seleting current item
							cachePrev[weight - weights[itemIdx - 1]]); // max value with what's weight is left
			}
			else
			{
				// Just use previous value as can't add current since not enough weight space left
				cacheCur[weight] = cachePrev[weight];
			}
		}
		copy(cacheCur, cacheCur + maxWeight + 1, cachePrev);
	}

	return cacheCur[maxWeight];
}


void knapsackMain()
{
	vector<int> weights = {10, 20, 30};
	vector<int> values = {60, 100, 120};
	int maxWeight = 50;

	auto start = high_resolution_clock::now();
	cout << "Recursive: " << knapsack(weights, values, maxWeight) << endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: "
		 << duration.count() << " microseconds" << endl;

	// Seems to perform worse
	start = high_resolution_clock::now();
	cout << "Recursive + DP: " << knapsack_DpTopDown(weights, values, maxWeight) << endl;
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: "
		 << duration.count() << " microseconds" << endl;

	//weights = {1, 3, 4, 5};
	//values = {1, 4, 5, 7};
    //maxWeight = 7;
    vector<int> knapsackItems;
	start = high_resolution_clock::now();
    cout << "knapsack Max Value: " << knapsack_DpBottomUp(weights, values, maxWeight, knapsackItems) << endl;
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: "
		 << duration.count() << " microseconds" << endl;

    for (auto itemIdx : knapsackItems)
    {
    	cout << "Value: " << values[itemIdx] << " Weight: " << weights[itemIdx] << endl;
    }

	start = high_resolution_clock::now();
    cout << "DP Min memory: " << knapsack_DpBottomUpMin(weights, values, maxWeight) << endl;
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: "
		 << duration.count() << " microseconds" << endl;
}

/*

// If can have multiple of each item in knapsack
int knapsack(const vector<int> &weights, const vector<int> &values, const int maxWeight, unordered_map<int, int> &cache) {
    if (maxWeight == 0) {
        return 0;
    }
    else if (cache.find(maxWeight) != cache.end()) {
        return cache[maxWeight];
    }
    
    int maxValue = 0;
    for (int i = 0; i < weights.size(); ++i) {
        int leftWeight = maxWeight - weights[i];
        
        if (leftWeight >= 0) {
            int value = values[i] + knapsack(weights, values, leftWeight, cache);
            if (maxValue < value) {
                maxValue = value;
            }
        }
    }
    cache[maxWeight] = maxValue;
    
    return maxValue;
}
 
 */