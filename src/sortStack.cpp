/*
 * sortStack.cpp
 *
 *  Created on: 2019-08-24
 *      Author: ckirsch
 */
#include "sortStack.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <stack>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 1) push items to vector/array and then sort and put back to stack O(n + nlogn + n)
// 2) or below implementation O(n^2)
void sortStack1(stack<int> &st)
{
	stack<int> st2;

	if (st.empty())
	{
		return;
	}

	while (!st.empty())
	{
		// 1) pop from stack while top > prev
		while (!st.empty() && (st2.empty() || st.top() > st2.top()))
		{
			st2.push(st.top());
			st.pop();
		}

		if (st.empty())
		{
			break;
		}

		// 2) Pull off top and then push back previous, and then add back top to sort
		bool addedSmall = false;
		int smallTop = st.top();
		st.pop();
		while(!st2.empty())
		{
			st.push(st2.top());
			st2.pop();

			if ((!addedSmall && !st2.empty() && st2.top() < smallTop) ||
				(!addedSmall && st2.empty()))
			{
				st.push(smallTop);
				addedSmall = true;
			}
		}
	}

	while (!st2.empty())
	{
		st.push(st2.top());
		st2.pop();
	}
}


stack<int> sortStack2(stack<int> st)
{
	stack<int> newStack;
	int tmp;

	if (st.empty())
	{
		return newStack;
	}

	newStack.push(st.top());
	st.pop();

	while (!st.empty())
	{
		tmp = st.top();
		st.pop();

		while (!newStack.empty() && tmp > newStack.top())
		{
			st.push(newStack.top());
			newStack.pop();
		}

		newStack.push(tmp);
	}

	return newStack;
}


int sortStackMain()
{
	bool pass = true;
	stack<int> st;
	vector<int> data = {8,13,1,7,5,11,10,2,100,15,32,33,24,25,75,64,76,66,77,67,78,68};

	for (int i : data)
	{
		st.push(i);
	}

	// 1
	auto start = high_resolution_clock::now();
	stack<int> st2 = sortStack2(st);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: "
		 << duration.count() << " microseconds" << endl;

	while (!st2.empty())
	{
		int top = st2.top();
		int next;

		cout << top << " ";

		st2.pop();
		if (!st2.empty())
		{
			next = st2.top();
			assert(pass &= (top <= next));
		}
	}
	cout << endl;

	// 2
	start = high_resolution_clock::now();
	sortStack1(st);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
   		 << duration.count() << " microseconds" << endl;

	while (!st.empty())
	{
		int top = st.top();
		int next;

		cout << top << " ";

		st.pop();
		if (!st.empty())
		{
			next = st.top();
			assert(pass &= (top <= next));
		}
	}
	cout << endl;

	cout << "Pass: " << pass << endl;
	return 0;
}


