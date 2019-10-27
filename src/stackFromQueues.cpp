/*
 * stackFromQueues.cpp
 *
 *  Created on: 2019-08-04
 *      Author: ckirsch
 */
#include "stackFromQueues.h"
#include <cassert>
#include <cstdint>
#include <iostream>
using namespace std;


template <typename T>
void QStack<T>::push(T value)
{
	queue<T> *emptyQueue;
	queue<T> *fullQueue;

	if (pingQueue.empty())
	{
		emptyQueue = &pingQueue;
		fullQueue = &pongQueue;
	}
	else
	{
		emptyQueue = &pongQueue;
		fullQueue = &pingQueue;
	}

	emptyQueue->push(value);
	while (!fullQueue->empty())
	{
		emptyQueue->push(fullQueue->front());
		fullQueue->pop();
	}
}


template <typename T>
T QStack<T>::pop()
{
	queue<T> *fullQueue;

	if (pingQueue.empty())
	{
		fullQueue = &pongQueue;
	}
	else
	{
		fullQueue = &pingQueue;
	}

	if (fullQueue->empty())
	{
		throw "Can't pop() from empty stack";
	}

	T value = fullQueue->front();
	fullQueue->pop();

	return value;
}


int stackFromQueuesMain()
{
	bool pass = true;
	QStack<int> qStack;

	qStack.push(1);
	qStack.push(2);
	qStack.push(3);
	qStack.push(4);
	qStack.push(5);
	qStack.push(6);
	qStack.push(7);
	qStack.push(8);

	assert(pass &= (8 == qStack.pop()));
	assert(pass &= (7 == qStack.pop()));
	assert(pass &= (6 == qStack.pop()));
	assert(pass &= (5 == qStack.pop()));
	assert(pass &= (4 == qStack.pop()));
	assert(pass &= (3 == qStack.pop()));
	assert(pass &= (2 == qStack.pop()));
	assert(pass &= (1 == qStack.pop()));

	cout << "Pass: " << pass << endl;

	return 0;
}
