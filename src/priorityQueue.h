/*
 * priorityQueue.h
 *
 *  Created on: 2019-09-06
 *      Author: ckirsch
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_
#include <vector>

using namespace std;


// Priortiy Queue -> with array as base structure
class PriorityQueue
{
public:
	enum PriorityQueueType
	{
		PriorityQueueTypeMin,
		PriorityQueueTypeMax
	};

private:
	PriorityQueueType type;
	vector<int> heap;

	static int getParentIndex(int index)
	{
		// Check if parent exists
		if (0 == index)
		{
			return -1;
		}
		return (index - 1) / 2;
	}

	static int getLeftChildIndex(int index)
	{
		return (index * 2) + 1;
	}

	static int getRightChildIndex(int index)
	{
		return (index * 2) + 2;
	}

public:
	PriorityQueue(PriorityQueueType type) : type(type) {}

	void push(int value);
	int pop();
};


void priorityQueueMain();


#endif /* PRIORITYQUEUE_H_ */
