/*
 * mergeKSortArrays.cpp
 *
 *  Created on: 2019-08-27
 *      Author: ckirsch
 */
#include "mergeKSortedArrays.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator> // for back_inserter
#include <queue>
using namespace std;

/* Given K sorted arrays, merge them into a single sorted array. 
{1,4,7}
{2,5,8} = {1,2,3,4,5,6,7,8,9}
{3,6,9}

1) copy all elements into an array O(kn) then sort array O(kn logkn)
2) pointer tracking first/smallest element in K arrays, so O(k) space.
And then per each O(kn) element select smallest in array O(k) and insert itn new sorted array.
Takes O(kn*k) = O(k^2 n)
3) To get ride of k^2 or O(k) search for smallest could use min heap to get min.
Per each kn element, push onto min heap of size k O(kn * (logk + logk)) = O(knlogk)
*/

template<class Iter>
void merge_sort(Iter first, Iter last) // Expect O(logn * nlogn) bu expect O(logn * n)=O(nlogn)
{
    if (last - first > 1) {
        Iter middle = first + (last - first) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last); // O(nlogn) but expect O(n)
    }
}


// O(N*M*log(N*M))
vector<int> mergeKSortArrays1(const vector<vector<int>> &arrays)
{
	vector<int> merged;

	int size = 0;

	for (auto array : arrays)
	{
		size += array.size();
	}

	merged.reserve(size);

	size = 0;
	// O(N)
	for (auto array : arrays)
	{
		// O(M)
		copy(array.begin(), array.end(), back_inserter(merged));
	}

	// O((N*M)log(N*M))
	merge_sort(merged.begin(), merged.end());

	return merged;
}


// O(N * (M + NM)) = O(N^2 * M)
vector<int> mergeKSortArrays2(const vector<vector<int>> &arrays)
{
	vector<int> merged;

	int size = 0;

	for (auto array : arrays)
	{
		size += array.size();
	}

	merged.reserve(size);

	size = 0;
	// O(N)
	for (auto array : arrays)
	{
		vector<int> meregedTmp;

		size += array.size();

		// O(M + N*M)
		merge(array.begin(), array.end(), merged.begin(), merged.end(), meregedTmp.begin());

		// O(N*M)
		merged = meregedTmp;
		//copy(meregedTmp.begin(), meregedTmp.end(), back_inserter(merged));
		//merged.assign(meregedTmp.begin(), meregedTmp.end());
	}

	return merged;
}


// O((N*M)log(N*M))
vector<int> mergeKSortArrays3(const vector<vector<int>> &arrays)
{
	vector<int> merged;

	int size = 0;

	for (auto array : arrays)
	{
		size += array.size();
	}

	merged.reserve(size);

	size = 0;
	// O(N)
	for (auto array : arrays)
	{
		// O(M)
		copy(array.begin(), array.end(), back_inserter(merged));
	}

	// O((N*M)log(N*M))
	sort(merged.begin(), merged.end());

	return merged;
}


/* If not using c++ sort/merge library:
 * 1) keep array of index's (N) to perform O(N) compares for NM elements, therefore O(N * NM), which is
 * worse than the copy and sort or mergeSort
 * 2) Create a min queue of N, then while queue not empty pop() and insert next
 * O(NM * log(N)) this is best performance */
vector<int> mergeKSortArrays4(const vector<vector<int>> &arrays)
{
	struct Node
	{
		uint arrayIndex;
		vector<int>::const_iterator ptr;

		Node (uint arrayIndex, vector<int>::const_iterator ptr) : arrayIndex(arrayIndex), ptr(ptr) {}

		bool operator ()(const Node &lhs, const Node &rhs) const
		{
			return *(lhs.ptr) < *(rhs.ptr);
		}

		bool operator < (const Node &rhs) const
		{
			return *(this->ptr) < *(rhs.ptr);
		}

		bool operator > (const Node &rhs) const
		{
			return *(this->ptr) > *(rhs.ptr);
		}
	};

	vector<int> merged;
	priority_queue<Node, vector<Node>, std::greater<Node>> minHeap;
	for (uint i = 0; i < arrays.size(); ++i)
	{
		if (0 < arrays[i].size())
		{
			minHeap.push(Node(i, arrays[i].begin()));
		}
	}

	while (!minHeap.empty())
	{
		Node top = minHeap.top();
		minHeap.pop();

		merged.push_back(*(top.ptr));

		auto ptrNext = next(top.ptr);
		if (ptrNext != arrays[top.arrayIndex].end())
		{
			minHeap.push(Node(top.arrayIndex, ptrNext));
		}
	}

	return merged;
}

vector<int> mergeKSortArraysMinHeap(const vector<vector<int>> &arrays) {
    struct Node {
        int value;
        int arrayNum;
        int pos;
        
        Node(int value, int arrayNum, int pos) : value(value), arrayNum(arrayNum), pos(pos) {}
    };
    
    // This comparator will be used to build minheap.
    auto comp = [](const Node &a, const Node &b) -> bool {
        return a.value > b.value;
    };
    
    priority_queue<Node, vector<Node>, decltype(comp)> minHeap(comp);
    
    // Push the fist k elements onto heap
    for (int i = 0; i < arrays.size(); ++i) {
        minHeap.push(Node(arrays[i][0], i, 0));
    }
    
    vector<int> final;
    while (!minHeap.empty()) {
        auto top = minHeap.top();
        minHeap.pop();
        
        int val = top.value;
        int arrayNum = top.arrayNum;
        int pos = top.pos;
        cout << val << endl;
        
        final.push_back(val);
        if (pos + 1 < arrays[arrayNum].size()) {
            minHeap.push(Node(arrays[arrayNum][pos+1], arrayNum, pos+1));
        }
    }
    
    return final;
}


int mergeKSortArraysMain()
{
	vector<vector<int>> arrays = {
			{1,4,7},
			{2,5,8},
			{3,6,9}
	};

	vector<int> merged = mergeKSortArrays1(arrays);
	for (auto i : merged)
	{
		cout << i << " ";
	}
	cout << endl;

	merged = mergeKSortArrays1(arrays);
	for (auto i : merged)
	{
		cout << i << " ";
	}
	cout << endl;

	merged = mergeKSortArrays3(arrays);
	for (auto i : merged)
	{
		cout << i << " ";
	}
	cout << endl;

	merged = mergeKSortArrays4(arrays);
	for (auto i : merged)
	{
		cout << i << " ";
	}
	cout << endl;

	return 0;
}

