/*
 * maxStack.cpp
 *
 *  Created on: 2019-09-08
 *      Author: ckirsch
 */
#include "maxStack.h"
#include <iostream>
#include <cassert>

using namespace std;


void MaxStackOverlay::push(int value)
{
	Node newNode(value);

	if (!maxStack.empty())
	{
		Node *maxNode = nullptr;

		// Check if top is current max
		if (nullptr == maxStack.top().maxNode)
		{
			maxNode = &(maxStack.top());
		}
		else
		{
			maxNode = maxStack.top().maxNode;
		}

		// Set new Nodes max
		if (value < maxNode->value)
		{
			newNode.maxNode = maxNode;
		}
	}

	maxStack.push(newNode);
}


void MaxStackOverlay::pop()
{
	if (maxStack.empty())
	{
		throw "Pop called on empty stack";
	}

	maxStack.pop();
}


int MaxStackOverlay::top()
{
	if (maxStack.empty())
	{
		throw "Top called on empty stack";
	}

	return maxStack.top().value;
}


int MaxStackOverlay::max()
{
	if (maxStack.empty())
	{
		throw "Max called on empty stack";
	}

	return (nullptr == maxStack.top().maxNode) ? maxStack.top().value :
			maxStack.top().maxNode->value;
}


bool MaxStackOverlay::empty()
{
	return maxStack.empty();
}

void maxStackMain()
{
    MaxStackOverlay maxStack;

    for (int i = 1; i < 10; ++i)
    {
        maxStack.push(i);
        cout << maxStack.max() << ", ";
    }
    cout << endl;

    for (int i = 50; i >= 30; i -= 5)
    {
        maxStack.push(i);
        cout << maxStack.max() << ", ";
    }
    cout << endl;

    while (!maxStack.empty())
    {
        cout << maxStack.top() << ", ";
        maxStack.pop();
    }
    cout << endl;
}
