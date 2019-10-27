/*
 * printReversedLinkedList.cpp
 *
 *  Created on: 2019-08-24
 *      Author: ckirsch
 */
#include "printReversedLinkedList.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <forward_list>

using namespace std;

void printReversedLinkedListHelper(forward_list<int>::iterator iter, forward_list<int>::iterator end)
{
	if (iter == end)
	{
		return;
	}

	printReversedLinkedListHelper(next(iter), end);
	cout << *iter << " ";
}

// 1) Reverse the list by reversing the pointers (this modifies the original linked list) O(n)
// 2) use stack to reverse list (with stack or recursion) O(n) and extra space, might take less space with stack
void printReversedLinkedList(forward_list<int> list)
{
	printReversedLinkedListHelper(list.begin(), list.end());
	cout << endl;
}


int printReversedLinkedListMain()
{
	forward_list<int> list = {1, 2, 3};

	printReversedLinkedList(list);

	return 0;
}
