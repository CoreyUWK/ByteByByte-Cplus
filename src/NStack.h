/*
 * NStack.h
 *
 *  Created on: 2019-07-27
 *      Author: ckirsch
 */

#ifndef NSTACK_H_
#define NSTACK_H_

#include <queue>
#include <memory>
using namespace std;

#define NSTACK_DEBUG_PRINT

template <typename T>
class NStack
{
	unique_ptr<T[]> data;
	unique_ptr<T[]> prev;
	unique_ptr<T[]> topOfStack;
	queue<int> freeSpots;
	int size;
	int nStacks;

public:
	NStack(int numOfStacks, int arrSize);
	void push(int stackId, T newEntry);
	T pop(int stackId);
};


int NStackMain();

#endif /* NSTACK_H_ */
