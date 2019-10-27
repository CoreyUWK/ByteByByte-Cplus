/*
 * NStack.cpp
 *
 *  Created on: 2019-07-27
 *      Author: ckirsch
 */

#include "NStack.h"
#include <iostream>
#include <memory>
#include <queue>
#include <cstring>
#include <cassert>
using namespace std;


template<typename T>
NStack<T>::NStack(int numOfStacks, int arrSize)
{
	if (numOfStacks > arrSize)
	{
		throw std::invalid_argument("Array size " + to_string(arrSize) +
				"must be able to contain number of stacks " + to_string(numOfStacks));
	}

	// Initialize
	nStacks = numOfStacks;
	size = arrSize;
	data = std::make_unique<T[]>(size);
	prev = std::make_unique<T[]>(size);
	topOfStack = std::make_unique<T[]>(nStacks);

	// Set to -1 for no previous entry
	memset(&prev[0], -1, size * sizeof(prev[0]));
	memset(&topOfStack[0], -1, nStacks * sizeof(topOfStack[0]));

	// Setup free spots
	for (int i = 0; i < size; ++i)
	{
		freeSpots.push(i);
	}

	#ifdef NSTACK_DEBUG_PRINT
	cout << "Data: ";
	for (int i = 0; i < size; ++i)
	{
		cout << data[i] << " ";
	}
	cout << "\n";

	cout << "Prev: ";
	for (int i = 0; i < size; ++i)
	{
		cout << prev[i] << " ";
	}
	cout << "\n";

	cout << "Top: ";
	for (int i = 0; i < nStacks; ++i)
	{
		cout << topOfStack[i] << " ";
	}
	cout << "\n";
	#endif
}

template<typename T>
void NStack<T>::push(int stackId, T newEntry)
{
	int arrStackId = stackId - 1;
	if (stackId <= 0 || stackId > nStacks)
	{
		throw std::invalid_argument("Stack ID argument not valid");
	}

	// Get free spot
	if (freeSpots.empty())
	{
		throw std::overflow_error("NStack is full");
	}

	int spot = freeSpots.front();
	freeSpots.pop();
	int top = topOfStack[arrStackId];

	prev[spot] = top;
	topOfStack[arrStackId] = spot;

	// Set Stack entry
	data[spot] = newEntry;
}


template<typename T>
T NStack<T>::pop(int stackId)
{
	int arrStackId = stackId - 1;
	if (stackId <= 0 || stackId > nStacks)
	{
		throw std::invalid_argument("Stack ID argument not valid");
	}

	int top = topOfStack[arrStackId];

	// Check if stack is empty
	if (top == -1)
	{
		throw std::invalid_argument("Stack ID is empty");
	}

	int newTop = prev[top];
	topOfStack[arrStackId] = newTop;
	freeSpots.push(top); // Add back free spot

	return data[top];
}


void testPopArg(NStack<int> &nStack)
{
	/* Check exception thrown on empty pop */
	bool popException = false;
	try
	{
		int n = nStack.pop(1);
		cout << "Empty Pop=" << n << "\n";
	}
	catch (const exception &e)
	{
		cout << "Exception: " << e.what() << "\n";
		popException = true;
	}

	assert(popException);
}

void testPushArg(NStack<int> &nStack, int stackId, int value)
{
	bool fullException = false;

	try
	{
		nStack.push(stackId, value);
	}
	catch (const exception &e)
	{
		cout << "Exception: " << e.what() << "\n";
		fullException = true;
	}

	assert(fullException);
}

void testFullStack(NStack<int> &nStack, int size)
{
	for (int i = 0; i < size; ++i)
	{
		nStack.push(1, i);
	}

	testPushArg(nStack, 1, 5);

	for (int i = size - 1; i >= 0; --i)
	{
		assert(nStack.pop(1) == i);
	}
}

void testStack(NStack<int> &nStack)
{
	/* 1 2 3
	 * 5 7
	 * 6 */
	nStack.push(1, 5); // 1
	nStack.push(1, 6); // 2
	nStack.push(2, 7); // 3

	/* 1 2 3
	 * 5 7 */
	assert(6 == nStack.pop(1)); // 2

	/* 1 2 3
	 * 5 7 10
	 * 8 9    */
	nStack.push(1, 8); // 3
	nStack.push(2, 9); // 4
	nStack.push(3, 10); // 5

	/* 1 2 3
	 * 5 7
	 * 8   */
	assert(9 == nStack.pop(2)); // 4
	assert(10 == nStack.pop(3)); // 3

	/* 1 2 3
	 * 5 7 11
	 * 8 13 12 */
	nStack.push(3, 11);  // 4
	nStack.push(3, 12); // 5
	nStack.push(2, 13); // 6

	/* 1 2 3
	 * 5 7 11
	 *   13 12 */
	assert(8 == nStack.pop(1)); // 5

	/* 1   2  3
	 * 5   7  11
	 * 14  13 12
	 * 15  16    */
	nStack.push(1, 14); // 6
	nStack.push(1, 15); // 7
	nStack.push(2, 16); // 8

	testPushArg(nStack, 1, 5);

	/* 1   2  3
	 * 5   7  11
	 * 14  13 12
	 * 15  16    */
	assert(15 == nStack.pop(1)); // 7
	assert(14 == nStack.pop(1)); // 6
	assert(5 == nStack.pop(1)); // 5
	assert(12 == nStack.pop(3)); // 4
	assert(11 == nStack.pop(3)); // 3
	assert(16 == nStack.pop(2)); // 2
	assert(13 == nStack.pop(2)); // 1
	assert(7 == nStack.pop(2)); // 0

	testPopArg(nStack);
}


int NStackMain()
{
	int numOfStack = 3;
	int stackSize = 8;
	NStack<int> nStack(numOfStack, stackSize);

	// Test empty pop
	testPopArg(nStack);

	// Test push to full stack
	testFullStack(nStack, stackSize);

	// Test pushing and popping
	testStack(nStack);

	return 0;
}


