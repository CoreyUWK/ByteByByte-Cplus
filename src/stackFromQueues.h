/*
 * stackFromQueues.h
 *
 *  Created on: 2019-08-04
 *      Author: ckirsch
 */
#ifndef STACKFROMQUEUES_H_
#define STACKFROMQUEUES_H_

#include <queue>
using namespace std;

template <typename T>
class QStack
{
	// Note: Could make the queue's pointers and just swap them after each push
	queue<T> pingQueue;
	queue<T> pongQueue;
public:
	void push(T value);
	T pop();
};


int stackFromQueuesMain();


#endif /* STACKFROMQUEUES_H_ */
