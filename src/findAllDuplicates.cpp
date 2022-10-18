/*
 * findAllDuplicates.cpp
 *
 *  Created on: 2019-09-03
 *      Author: ckirsch
 */
#include "findAllDuplicates.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_set>
#include <set>
using namespace std;

/* Given array containing values 1<= x <= len(array) find all duplicated in array */

/* 1) Brute Force method is a O(n^2) loop checking each value against all others to see if duplicate
 * 2) Use hash to track processed values. Time O(n), space O(n)
 * 3) Sort and then iterate and find duplicates, Time O(nlogn), Space O(1)
 * 4) Use a trick method taking fact that array should contain all unqiue values from 1 to array size
 * ex. length = 4 => 1,2,3,4
 * could have 2,4,3,4 (can have any order)
 * In unquie case each value - 1 is an array index
 * Hence, could use the array as the hash by setting the index of the value to a negitive to mark visited
 * Time O(n), Space O(m) < O(n) */
vector<int> findAllDuplicates(vector<int> &list)
{
	vector<int> duplicates;
	unordered_set<int> duplicatesHash;

	// O(n)
	for (uint i = 0; i < list.size(); ++i)
	{
		int positiveListItem = abs(list[i]);
		int index = positiveListItem - 1;
		if (list[index] < 0)
		{
			duplicatesHash.insert(positiveListItem);
		}
		else
		{
			list[index] *= -1;
		}
	}

	// Revert: remove added negatives O(n)
	for (int &i : list)
	{
		i = abs(i);
	}

	// O(m) < O(n)
	duplicates.assign(duplicatesHash.begin(), duplicatesHash.end());

	/*
	duplicates.reserve(duplicatesHash.size()); // not work
	duplicates.resize(duplicatesHash.size()); // works
	copy(duplicatesHash.begin(), duplicatesHash.end(), duplicates.begin()); */

	return duplicates;
}

vector<int> findAllDuplicatesV2(const vector<int> &list) {
    set<int> hash;
    vector<int> dups;
    for (auto i : list) {
        if (hash.find(i) == hash.end()) {
            hash.insert(i);
        }
    }
    
    for (auto i : hash) {
        dups.push_back(i);    
    }
    return dups;
}


void findAllDuplicatesMain()
{
	bool pass = true;

	vector<int> list = {2, 4, 3, 4, 2};

	unordered_set<int> dup;
	dup.insert(2);
	dup.insert(4);

	vector<int> result = findAllDuplicates(list);
	for (auto x : result)
	{
		assert(pass &= (dup.find(x) != dup.end()));
		dup.erase(x);
	}
	assert(pass &= dup.empty());

	cout << "Pass: " << pass << endl;
}
