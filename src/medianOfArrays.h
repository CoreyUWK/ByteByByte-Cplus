/*
 * medianOfArrays.h
 *
 *  Created on: 2019-09-06
 *      Author: ckirsch
 */

#ifndef MEDIANOFARRAYS_H_
#define MEDIANOFARRAYS_H_
#include <vector>
using namespace std;


class SubArray
{
	int *arr;
	int start;
	int size;

public:
	SubArray(int arr[], int size);
	void updateRange(int start, int end);
	double getMedian(int &medianIndex1, int &medianIndex2);

	int *getArray()
	{
		return arr;
	}

	int getSize()
	{
		return size;
	}

	int getStart()
	{
		return start;
	}

	int getEnd()
	{
		return start + size - 1;
	}
};


void medianOfArraysMain();


#endif /* MEDIANOFARRAYS_H_ */
