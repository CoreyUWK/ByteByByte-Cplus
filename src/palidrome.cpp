/*
 * palidrome.cpp
 *
 *  Created on: 2019-07-28
 *      Author: ckirsch
 */
#include "palidrome.h"
#include <iostream>
#include <memory>
#include <queue>
#include <cstring>
#include <cassert>
#include <chrono>
#include <algorithm>
#include <forward_list>
#include <stack>
using namespace std;


bool isPalidrome (forward_list<int> &list)
{
	auto slow = list.begin();
	auto fast = list.begin();
	stack<int> listStack;
	bool result = true;

	// Check if list contain one or two elements
	if (distance(list.begin(), list.end()) <= 2)
	{
		return true;
	}

	// Slow at end will point to mid + one
	while (fast != list.end())
	{
		listStack.push(*slow);
		slow = next(slow);

		if (distance(fast, list.end()) >= 2)
		{
			fast = next(fast, 2);
		}
		else
		{
			fast = list.end();
		}
	}

	// If list is odd pop mid point
	if (listStack.top() != *slow)
	{
		listStack.pop();
	}

	while (slow != list.end())
	{
		if (listStack.empty())
		{
			result = false;
			break;
		}
		else if (listStack.top() != *slow)
		{
			result = false;
			break;
		}
		else
		{
			listStack.pop();
			slow = next(slow);
		}
	}

	if (!listStack.empty())
	{
		result = false;
	}

	return result;
}


int palidromeMain()
{
	bool pass = true;

	forward_list<int> list1;
	forward_list<int> list2 = {1};
	forward_list<int> list3 = {1, 2};
	forward_list<int> list4 = {1, 2, 3};
	forward_list<int> list5 = {1, 2, 1};
	forward_list<int> list6 = {1, 2, 2, 1};
	forward_list<int> list7 = {1, 2, 3, 2, 1};
	forward_list<int> list8 = {1, 2, 3, 3, 2, 1};
	forward_list<int> list9 = {1, 2, 3, 5, 3, 2, 1};
	forward_list<int> list10 = {1, 2, 3, 5, 3, 2, 1, 0};
	forward_list<int> list11 = {6,4,3,5,6,3,6,7,55,654,2,45,65,4};

	assert(pass &= (true == isPalidrome(list1)));
	assert(pass &= (true == isPalidrome(list2)));
	assert(pass &= (true == isPalidrome(list3)));
	assert(pass &= (false == isPalidrome(list4)));
	assert(pass &= (true == isPalidrome(list5)));
	assert(pass &= (true == isPalidrome(list6)));
	assert(pass &= (true == isPalidrome(list7)));
	assert(pass &= (true == isPalidrome(list8)));
	assert(pass &= (true == isPalidrome(list9)));
	assert(pass &= (false == isPalidrome(list10)));
	assert(pass &= (false == isPalidrome(list11)));

	cout << "Pass: " << pass << endl;

	return 0;
}
