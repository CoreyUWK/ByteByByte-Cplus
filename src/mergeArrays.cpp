/*
 * mergeArrays.cpp
 *
 *  Created on: 2019-08-03
 *      Author: ckirsch
 */

#include "mergeArrays.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>

using namespace std;

template<int N1, int N2>
bool mergeArrays(array<int,N1> &arr1, int arr1NumElem,
		const array<int,N2> &arr2)
{
	int totalSize = arr1.size();
	int arr2NumElem = arr2.size();
	if (totalSize != arr1NumElem + arr2NumElem)
	{
		cout << "Array 1 size should be total of array 1 + 2" << endl;
		return false;
	}
	else if (arr2.size() != arr2NumElem)
	{
		cout << "Array 2 size should be same as array 2" << endl;
		return false;
	}
	else if (arr1.size() < arr1NumElem)
	{
		cout << "Array 1 size should be >= arr1Size param" << endl;
		return false;
	}

	int arr1Idx = arr1NumElem - 1;
	int arr2Idx = arr2NumElem - 1;
	for (int i = totalSize - 1; i >= 0; --i)
	{
		if (arr1Idx < 0)
		{
			// Just copy whats left of arr2
			arr1[i] = arr2[arr2Idx];
			--arr2Idx;
		}
		else if (arr2Idx < 0)
		{
			// Just copy whats left of arr1
			arr1[i] = arr1[arr1Idx];
			--arr1Idx;
		}
		else // Compare array's data
		{
			if (arr1[arr1Idx] >= arr2[arr2Idx])
			{
				arr1[i] = arr1[arr1Idx];
				--arr1Idx;
			}
			else
			{
				arr1[i] = arr2[arr2Idx];
				--arr2Idx;
			}
		}
	}

	return true;
}


/* Given two sorted arrays where one is large enough to hold contents of both, write function
 * to copy one into the other without extra buffer or memory */
int mergeArraysMain()
{
	bool pass = true;

	// 1
	array<int,6> arr1{1,3,5,0,0,0};
	array<int,3> arr2{2,4,6};
	assert(pass &= (mergeArrays<6,3>(arr1, 3, arr2)));
	assert(pass &= (arr1 == array<int,6>{1,2,3,4,5,6}));

	// 2
	array<int,6> arr3{4,5,6,0,0,0};
	array<int,3> arr4{1,2,3};
	assert(pass &= (mergeArrays<6,3>(arr3, 3, arr4)));
	assert(pass &= (arr3 == array<int,6>{1,2,3,4,5,6}));

	// 3
	array<int,3> arr5{0,0,0};
	array<int,3> arr6{4,6,8};
	assert(pass &= (mergeArrays<3,3>(arr5, 0, arr6)));
	assert(pass &= (arr5 == array<int,3>{4,6,8}));

	// 4
	array<int,6> arr7{1,2,3,0,0,0};
	array<int,3> arr8{4,6,8};
	assert(pass &= (mergeArrays<6,3>(arr7, 3, arr8)));
	assert(pass &= (arr7 == array<int,6>{1,2,3,4,6,8}));

	cout << "Pass: " << pass << endl;

	return 0;
}
