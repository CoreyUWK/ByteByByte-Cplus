/*
 * kthMostFrequentString.cpp
 *
 *  Created on: 2019-09-10
 *      Author: ckirsch
 */
#include "kthMostFrequentString.h"
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/* Given list of string find kth most frequent string */

/* 1) use hash to get frequencies then partial sort and get kth O(nlogk)
 * 2) use hash to get frequencies then put into log(k) prioity queue O(nlogk)
 * 3) use a hashtree/map which is like a heap but is a binary tree of hashes O(nlogn)
 * unordered_map generally uses more memory. map just has a few house-keeping pointers, and memory
 * for each object. Contrarily, unordered_map has a big array (these can get quite big in some
 * implementations), and then additional memory for each object. If you need to be memory-aware,
 * map should prove better, because it lacks the large array
 * 4) use hash of string->frequency and a inverse frequency->list<string> O(n) */


/* C++ sort is a quick sort.  Quick sort is inline but does require recursive calls taking up stack memory.
 * Merge sort is not inline and does require O(n) extra space for array and is also a recursive algorithm.
 * Quick and merge are both divide and conqure algo's.
 * Quick sort is better than merege sort on large data sets and on linked list based data where data is
 * not local and insertions take O(1) time and space, unlike arrays.
 * Quick sort worst case is O(n^2).
 * Heap sort is good for large data sets as is a binary tree so always log time. Heap sort can also be
 * inplace so memory usage minimal so is better than merge sort (requiring extra space) or quick sort
 * requires more stack space for recurison.
 *
 * Some say quick sort is best, efficieny is good and able to deal with hugh lists, is inplace so small
 * memory usage. But is actually best suited for small arrays, is not efficent for large.
 * Merge sort is consistent for any array type and size.
 * Quick requires min space and merge requires more space.*/

/* Hash setup takes O(n)
   Copy to set takes O(nlogn)
   Getting kth O(1)
   Total=O(nlogn)
   */
string kthFrequent1(const vector<string> &list, uint k)
{
    if (k <= 0)
    {
        throw "K argument must be >= 1";
    }
    else if (list.size() < k)
    {
        throw "List does not contain K elements";
    }

    // Setup hash for word frequency
    unordered_map<string, int> wordFreqHash;
    for (string s : list)
    {
        ++wordFreqHash[s];
    }

    // Get descending ordered hash
    auto compFunction = [](const pair<string, int> &lhs, const pair<string, int> &rhs)
    {
        return rhs.second < lhs.second;
    };

    // Set uses BST
    set<pair<string, int>, decltype(compFunction)> orderedHash (wordFreqHash.begin(), wordFreqHash.end(), compFunction);

    // Get Kth freqent element
    auto itr = orderedHash.begin();
    advance(itr, k - 1);

    return itr->first;
}


/* Hash setup takes O(n)
   partial sort O(nlogk)
   Getting kth O(1)
   Total=O(nlogn)
   */
string kthFrequent2(const vector<string> &list, uint k)
{
    if (k <= 0)
    {
        throw "K argument must be >= 1";
    }
    else if (list.size() < k)
    {
        throw "List does not contain K elements";
    }

    // Setup hash for word frequency
    unordered_map<string, int> wordFreqHash;
    for (string s : list)
    {
        ++wordFreqHash[s];
    }

    // Get descending ordered hash
    auto compFunction = [](const pair<string, int> &lhs, const pair<string, int> &rhs)
    {
        return rhs.second < lhs.second;
    };

    vector<pair<string,int>> freqList(wordFreqHash.begin(), wordFreqHash.end());
    partial_sort (freqList.begin(), freqList.begin() + k, freqList.end(), compFunction);

    return freqList[k - 1].first;
}


/* Hash setup takes O(n)
   make prioty queue/heap O(nlogk)
   Getting kth O(1)
   Total=O(nlogn)
   */
string kthFrequent3(const vector<string> &list, uint k)
{
    if (k <= 0)
    {
        throw "K argument must be >= 1";
    }
    else if (list.size() < k)
    {
        throw "List does not contain K elements";
    }

    // Setup hash for word frequency
    unordered_map<string, int> wordFreqHash;
    for (string s : list)
    {
        ++wordFreqHash[s];
    }

    // Get descending ordered hash
    auto compFunction = [](const pair<string, int> &lhs, const pair<string, int> &rhs)
    {
        return rhs.second < lhs.second;
    };

    // Make a k deep max heap
    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(compFunction)> maxHeap(compFunction);
    auto wordItr = wordFreqHash.begin();
    uint i = 0;
    for (; i < k; ++i)
    {
        maxHeap.push(make_pair(wordItr->first, wordItr->second));
        ++wordItr;
    }

    // Go through all items in hash and ensure heap contains max K so top of heap is the k most frequent
    for (; i < wordFreqHash.size(); ++i)
    {
        auto top = maxHeap.top();
        if (top.second < wordItr->second)
        {
            maxHeap.pop();
            maxHeap.push(make_pair(wordItr->first, wordItr->second));
        }
        ++wordItr;
    }

    return maxHeap.top().first;
}


void kthMostFrequentStringMain()
{
	bool pass = true;

	vector<string> list = {
	  "I", "am", "god",
	  "I", "am", "dog",
	  "I", "found", "home"
	};

	assert(pass &= ("am" == kthFrequent1(list, 2)));
	assert(pass &= ("am" == kthFrequent2(list, 2)));
	assert(pass &= ("am" == kthFrequent3(list, 2)));

	cout << "Pass: " << pass << endl;
}

