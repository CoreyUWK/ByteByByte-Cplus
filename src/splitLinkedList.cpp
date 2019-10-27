/*
 * splitLinkedList.cpp
 *
 *  Created on: 2019-09-14
 *      Author: ckirsch
 */
#include "splitLinkedList.h"
#include <iostream>
#include <cassert>
#include <forward_list>
using namespace std;


forward_list<int> splitLinkedList(forward_list<int> &list)
{
	forward_list<int> secondHalf;

	if (list.empty())
	{
		return secondHalf;
	}

	auto slow = list.begin();
	auto fast = list.begin();

	// Get Slow pointing one before middle
	while (next(fast) != list.end() &&
			next(next(fast)) != list.end())
	{
		slow = next(slow);
		fast = next(next(fast));
	}

	secondHalf.splice_after(secondHalf.before_begin(), list, slow, list.end());
	return secondHalf;
}


void splitLinkedListMain()
{
	bool pass = true;

	// 1
	forward_list<int> list1 = {1,2,3,4};
	forward_list<int> list1SecondHalf = splitLinkedList(list1);

	assert(pass &= (forward_list<int>{1,2} == list1));
	assert(pass &= (forward_list<int>{3,4} == list1SecondHalf));

	// 2
	forward_list<int> list2 = {1,2,3};
	forward_list<int> list2SecondHalf = splitLinkedList(list2);

	assert(pass &= (forward_list<int>{1,2} == list2));
	assert(pass &= (forward_list<int>{3} == list2SecondHalf));

	// 3
	forward_list<int> list3 = {1,2};
	forward_list<int> list3SecondHalf = splitLinkedList(list3);

	assert(pass &= (forward_list<int>{1} == list3));
	assert(pass &= (forward_list<int>{2} == list3SecondHalf));

	cout << "Pass: " << pass << endl;
}
