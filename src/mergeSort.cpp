/*
 * mergeSort.cpp
 *
 *  Created on: 2019-08-27
 *      Author: ckirsch
 */
#include "mergeSort.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>
using namespace std;


void mergeHalves(int arr[], int tmp[], int length)
{
	int left = 0;
	int middle = length / 2;
	int right = middle;
	int index = 0;

#ifdef MERGESORT_DEBUGPRINT
	cout << "Data: ";
	for (int i = 0; i < length; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
#endif

	while (left < middle && right < length)
	{
		if (arr[left] < arr[right])
		{
			tmp[index] = arr[left];
			++left;
		}
		else
		{
			tmp[index] = arr[right];
			++right;
		}

		++index;
	}

	copy(arr + left, arr + middle, tmp + index); // copy remaining of left half
	index += middle - left;
#ifdef MERGESORT_DEBUGPRINT
	cout << "index: " << index << endl;
#endif
	copy(arr + right, arr + length, tmp + index); // copy remaining of right half

#ifdef MERGESORT_DEBUGPRINT
	for (int i = 0; i < length; ++i)
	{
		cout << tmp[i] << " ";
	}
	cout << endl;
#endif
	copy(tmp, tmp + length, arr); // copy back to array
}


void mergeSortHelper(int arr[], int tmp[], uint length)
{
	if (length <= 1)
	{
		return;
	}

	int middle = length / 2;
	mergeSortHelper(arr, tmp, middle);
	mergeSortHelper(arr + middle, tmp, length - middle);
	mergeHalves(arr, tmp, length);
}


void mergeSort(int arr[], uint length)
{
	if (length <= 1)
	{
		return;
	}

	mergeSortHelper(arr, new int[length], length);
}


template<class Iter>
void merge_sort(Iter first, Iter last)
{
    if (last - first > 1) {
        Iter middle = first + (last - first) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }
}


int mergeSortMain()
{
	// 1
	int arr[] = {38, 27, 43, 3, 9, 82, 10};
	int size = sizeof(arr) / sizeof(arr[0]);

	mergeSort(arr, size);

	for (const auto &i : arr)
	{
		cout << i << " ";
	}
	cout << endl;

	// 2
	int arr2[] = {38, 27, 43, 3, 9, 82, 10};

	mergeSort(arr2, size);

	for (const auto &i : arr2)
	{
		cout << i << " ";
	}
	cout << endl;

	return 0;
}

