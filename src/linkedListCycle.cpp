/*
 * linkedListCycle.cpp
 *
 *  Created on: 2019-09-02
 *      Author: ckirsch
 */
#include "linkedListCycle.h"
#include <iostream>
#include <cassert>
#include <unordered_set>
using namespace std;

/* Given a linked list, determine whether or not it contains a cycle.
E.g.
1->2->3->4
   ^     |
   |_____|
return true

1->2->3->4->3->4->null
return false

1) Slow and fast 2x pointers, if they every equal then has loop. To get start of loop, iterate from head and where loop detected.
When the two equal is point of intersection.
2) Track nodes in map and if ever at same address then loop. Extra memory no good. 
*/

struct Node {
	int value;
	Node *next;

	Node (int value, Node *next = nullptr) : value(value), next(next) {}
};


// Time: O(n), Space: O(n)
bool linkedListCycle_Hash(Node *n)
{
	bool isCycle = false;
	unordered_set<Node *> hash;

	for (Node *cur = n; cur != nullptr; cur = cur->next)
	{
		if (hash.find(cur) != hash.end())
		{
			return true;
		}
		hash.insert(cur);
	}

	return isCycle;
}


// Time: O(n), Space: O(1)
bool linkedListCycle_floiedAlgo(Node *n)
{
	if (nullptr == n)
	{
		return false;
	}

	Node *slow = n;
	Node *fast = n;

	while (nullptr != fast->next && nullptr != fast->next->next)
	{
		if (slow == fast)
		{
			return true;
		}

		slow = slow->next;
		fast = fast->next->next;
	}

	return false;
}


void linkedListCycleMain()
{
	bool pass = true;

	Node *root = new Node(1, new Node(2, new Node (3, new Node(4))));
	root->next->next->next->next = root->next;

	assert(pass &= (true == linkedListCycle_Hash(root)));
	assert(pass &= (true == linkedListCycle_floiedAlgo(root)));

	cout << "Pass: " << pass << endl;
}

