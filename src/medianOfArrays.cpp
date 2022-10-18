/*
 * medianOfArrays.cpp
 *
 *  Created on: 2019-09-06
 *      Author: ckirsch
 */
#include "medianOfArrays.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

/* Find median of two sorted arrays
 arr1 [1,3,5]
 arr2 [2,4,6]

 median(arr1, arr2) = 3.5

 * arr1 = {1,5,7,10}
 * arr2 = {3,4,8,9}
 *
 * 1) merge arrays into one larger one in sorted order O(n), then take the median of the larger array by taking the middle values
 * 	1,3,4,[5,7],8,9,10 => (5 + 7) / 2 = 6
 * 2) Take total size of all arrays together and then iterate the sorted arrays O(n/2) till you get to size/2 and then take median
 * 	totalSize = 8
 * 	index1 = (totalSize - 1) / 2
 * 	if (totalSize % 2 == 0)
 * 		index2 = index1 + 1;
 * 		got to index's and get median
 * 	els
 * 		got to index1 and get median
 * 3) Reduce arrays based on median
 * Take median of each array and until reduce
 * 4) O(n) have 4 pointer index's to first and last element per each array, and per each iteration move min(first's)+1 and max(last's)-1
 * till hit middle.
 * 5) O(n/2) we know if one of the arrays has size 4, then both together is 4+4=8. And as these are even will have median using 2 values.
 * Hence, 3,2,3 which means we need to move 3 index's to get to middle for median. So,
 *      V
 * [3,4,7,10]  3,4,5,[6,7],8,9,10
 * [5,6,8,9]
 *    ^
 * Keep moving pointer (starting from beginning index) until moved total of 3 spots to get median[6,7].
 * */
double median(vector<int> &arr, int start, int end,
		int &medianIndex1, int &medianIndex2)
{
	double median = 0;

	if (&medianIndex1 == &medianIndex2)
	{
		throw "References were made to same variable";
	}

	int arrSize = end - start + 1;
	if (arrSize % 2 == 0)
	{
		medianIndex1 = (end + start) / 2;
		medianIndex2 = medianIndex1 + 1;
		median = (arr[medianIndex1] + arr[medianIndex2]) / 2;
	}
	else
	{
		medianIndex1 = (end + start) / 2;
		medianIndex2 = -1;
		median = arr[medianIndex1];
	}

	return median;
}

// O(log(n)) cause each time removeing half from each array till get to size of 2
// removing half by comparing median of start-to-end subarray
double medianOfArrays(vector<int> arr1, vector<int> arr2)
{
	if (arr1.size() == 0 || arr1.size() != arr2.size())
	{
		throw "Invalid array arguments";
	}
	else if (arr1.size() == 1)
	{
		return (arr1[0] + arr2[0]) / 2.0;
	}

	int arr1Start = 0,
		arr1End = arr1.size() - 1;
	int arr2Start = 0,
		arr2End = arr2.size() - 1;

	int median1Index1 = 0,
		median1Index2 = 0;
	int median2Index1 = 0,
		median2Index2 = 0;

	int arr1Size = arr1End - arr1Start + 1;
	int arr2Size = arr2End - arr2Start + 1;

	while (arr1Size > 2 && arr2Size > 2)
	{
		double median1 = median(arr1, arr1Start, arr1End, median1Index1, median1Index2);
		double median2 = median(arr2, arr2Start, arr2End, median2Index1, median2Index2);

		if (median1 == median2)
		{
			return median1;
		}
		else if (median1 < median2)
		{
			arr1Start = median1Index1;
			arr2End = (median2Index2 == -1) ? median2Index1 : median2Index2;
		}
		else
		{
			arr1End = (median1Index2 == -1) ? median1Index1 : median1Index2;
			arr2Start = median2Index1;
		}

		arr1Size = arr1End - arr1Start + 1;
		arr2Size = arr2End - arr2Start + 1;
	}

	return (max(arr1[arr1Start], arr2[arr2Start]) +
			min(arr1[arr1End], arr2[arr2End])) / 2.0;
}


//---------------------------------------------------------
// Trying to use class to reduce logic from above
SubArray::SubArray(int arr[], int size)
{
	this->arr = arr;
	this->start = 0;
	this->size = size;
}


void SubArray::updateRange(int start, int end)
{
	this->size = end - start + 1;
	this->start = start;
}


double SubArray::getMedian(int &medianIndex1, int &medianIndex2)
{
	double median = 0;

	if (size % 2 == 0)
	{
		medianIndex1 = (getEnd() + start) / 2;
		medianIndex2 = medianIndex1 + 1;
		median = (arr[medianIndex1] + arr[medianIndex2]) / 2.0;
	}
	else
	{
		medianIndex1 = (getEnd() + start) / 2;
		medianIndex2 = -1;
		median = arr[medianIndex1];
	}

	return median;
}

double medianOfArrays2Helper(SubArray &subArr1, SubArray &subArr2)
{
	int *arr1 = subArr1.getArray();
	int *arr2 = subArr2.getArray();

	if (subArr1.getSize() == 1)
	{
		return (arr1[subArr1.getStart()] + arr2[subArr2.getStart()]) / 2.0;
	}
	else if (subArr1.getSize() == 2)
	{
		return (max(arr1[subArr1.getStart()], arr2[subArr2.getStart()]) +
				min(arr1[subArr1.getEnd()], arr2[subArr2.getEnd()])) / 2.0;
	}

	int subArr1MedianIndex1,
			subArr1MedianIndex2;
	int subArr2MedianIndex1,
			subArr2MedianIndex2;

	int subArr1Median = subArr1.getMedian(subArr1MedianIndex1, subArr1MedianIndex2);
	int subArr2Median = subArr2.getMedian(subArr2MedianIndex1, subArr2MedianIndex2);

	if (subArr1Median == subArr2Median)
	{
		return subArr1Median;
	}
	else if (subArr1Median < subArr2Median)
	{
		subArr1.updateRange(subArr1MedianIndex1, subArr1.getEnd());
		subArr2.updateRange(subArr2.getStart(),
				(subArr2MedianIndex2 == -1) ? subArr2MedianIndex1 : subArr2MedianIndex2);
	}
	else
	{
		subArr1.updateRange(subArr1.getStart(),
				(subArr1MedianIndex2 == -1) ? subArr1MedianIndex1 : subArr1MedianIndex2);
		subArr2.updateRange(subArr2MedianIndex1, subArr2.getEnd());
	}

	return medianOfArrays2Helper(subArr1, subArr2);
}

double medianOfArrays2(vector<int> &arr1, vector<int> &arr2)
{
	if (arr1.size() == 0 || arr1.size() != arr2.size())
	{
		throw "Invalid array arguments";
	}

	SubArray subArr1(arr1.data(), arr1.size());
	SubArray subArr2(arr2.data(), arr2.size());

	return medianOfArrays2Helper(subArr1, subArr2);
}


void medianOfArraysMain()
{
	bool pass = true;

	vector<int> arr1 = {1, 3, 5};
	vector<int> arr2 = {2, 4, 6};

	assert(pass &= (3.5 == medianOfArrays(arr1, arr2)));
	assert(pass &= (3.5 == medianOfArrays2(arr1, arr2)));

	arr1 = {7, 12, 19, 20, 21};
	arr2 = {1, 3, 6, 8, 10};
	assert(pass &= (9 == medianOfArrays(arr1, arr2)));
	assert(pass &= (9 == medianOfArrays2(arr1, arr2)));

	arr1 = {7, 12, 19, 20};
	arr2 = {1, 3, 6, 8};
	assert(pass &= (7.5 == medianOfArrays(arr1, arr2)));
	assert(pass &= (7.5 == medianOfArrays2(arr1, arr2)));

	arr1 = {1, 5, 7, 10};
	arr2 = {2, 4, 8, 9};
	assert(pass &= (6 == medianOfArrays(arr1, arr2)));
	assert(pass &= (6 == medianOfArrays2(arr1, arr2)));

	arr1 = {5};
	arr2 = {2};
	assert(pass &= (3.5 == medianOfArrays(arr1, arr2)));
	assert(pass &= (3.5 == medianOfArrays2(arr1, arr2)));

	arr1 = {1,3};
	arr2 = {2,4};
	assert(pass &= (2.5 == medianOfArrays(arr1, arr2)));
	assert(pass &= (2.5 == medianOfArrays2(arr1, arr2)));

	arr1 = {1,2};
	arr2 = {3,4};
	assert(pass &= (2.5 == medianOfArrays(arr1, arr2)));
	assert(pass &= (2.5 == medianOfArrays2(arr1, arr2)));

	arr1 = {1,2,3};
	arr2 = {4,5,6};
	assert(pass &= (3.5 == medianOfArrays(arr1, arr2)));
	assert(pass &= (3.5 == medianOfArrays2(arr1, arr2)));

	cout << "Pass: " << pass << endl;
}



