/*
 * nthToLastLinkedList.cpp
 *
 *  Created on: 2019-09-08
 *      Author: ckirsch
 */
#include "nthToLastLinkedList.h"
#include <iostream>
#include <cassert>
#include <forward_list>
using namespace std;


forward_list<int>::iterator nthToLastLinkedList(forward_list<int> &list, int n)
{
	auto follower = list.begin();
	auto cur = list.begin();

	for (int i = 0; cur != list.end() && i < n; ++i)
	{
		cur = next(cur);
	}

	if (cur == list.end())
	{
		return list.end();
	}

	while (next(cur) != list.end())
	{
		cur = next(cur);
		follower = next(follower);
	}

	return follower;
}


void nthToLastLinkedListMain()
{
	bool pass = true;

	forward_list<int> list = {1, 2, 3, 4, 5};

	assert(pass &= (5 == *nthToLastLinkedList(list, 0)));
	assert(pass &= (4 == *nthToLastLinkedList(list, 1)));
	assert(pass &= (3 == *nthToLastLinkedList(list, 2)));
	assert(pass &= (2 == *nthToLastLinkedList(list, 3)));
	assert(pass &= (1 == *nthToLastLinkedList(list, 4)));
	assert(pass &= (list.end() == nthToLastLinkedList(list, 5)));

	cout << "Pass: " << pass << endl;
}


