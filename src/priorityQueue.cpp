/*
 * priorityQueue.cpp
 *
 *  Created on: 2019-09-06
 *      Author: ckirsch
 */
#include "priorityQueue.h"
#include <cassert>
#include <iostream>

using namespace std;


void PriorityQueue::push(int value)
{
	// Add new item
	heap.push_back(value);

	// Bubble up new item if less/greater than parent
	int index = heap.size() - 1;
	while (index > 0)
	{
		int parentIndex = getParentIndex(index);

		if ( (PriorityQueueTypeMin == type && heap[parentIndex] <= heap[index]) ||
			 (PriorityQueueTypeMax == type && heap[parentIndex] >= heap[index])
			)
		{
			break;
		}

		swap(heap[parentIndex], heap[index]);

		// Update
		index = parentIndex;
	}
}


int PriorityQueue::pop()
{
	if (heap.size() == 0)
	{
		throw "Calling pop on empty queue";
	}

	int topToReturn = heap[0];

	// Pop top and move bottom to top
	int endIndex = heap.size() - 1;
	heap[0] = heap[endIndex];
	heap.pop_back();

	// Bubble down top
	endIndex = heap.size() - 1;
	int index = 0;

	int lastParentIndex = getParentIndex(heap.size() - 1);
	while (index <= lastParentIndex)
	{
		int leftChildIndex = getLeftChildIndex(index);
		int rightChildIndex = getRightChildIndex(index);

		if (PriorityQueueTypeMin == type)
		{
			int minChildIndex = leftChildIndex;
			if (rightChildIndex <= endIndex &&
					heap[rightChildIndex] < heap[leftChildIndex])
			{
				minChildIndex = rightChildIndex;
			}

			if (minChildIndex <= endIndex && heap[index] > heap[minChildIndex])
			{
				swap(heap[index], heap[minChildIndex]);

				// Update
				index = minChildIndex;
			}
			else
			{
				break;
			}
		}
		else if (PriorityQueueTypeMax == type)
		{
			int maxChildIndex = leftChildIndex;
			if (rightChildIndex <= endIndex &&
					heap[rightChildIndex] > heap[leftChildIndex])
			{
				maxChildIndex = rightChildIndex;
			}

			if (maxChildIndex <= endIndex && heap[index] < heap[maxChildIndex])
			{
				swap(heap[index], heap[maxChildIndex]);

				// Update
				index = maxChildIndex;
			}
			else
			{
				break;
			}
		}
	}

	return topToReturn;
}


void priorityQueueMain()
{
	bool pass = true;

	PriorityQueue pq(PriorityQueue::PriorityQueueTypeMin);
	pq.push(4);
	pq.push(6);
	pq.push(3);
	pq.push(8);
	pq.push(7);
	pq.push(1);

	assert(pass &= (1 == pq.pop()));
	assert(pass &= (3 == pq.pop()));
	assert(pass &= (4 == pq.pop()));
	assert(pass &= (6 == pq.pop()));
	assert(pass &= (7 == pq.pop()));
	assert(pass &= (8 == pq.pop()));

	cout << "Pass: " << pass << endl;
}
