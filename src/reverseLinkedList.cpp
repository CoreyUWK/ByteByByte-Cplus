/*
 * reverseLinkedList.cpp
 *
 *  Created on: 2019-09-14
 *      Author: ckirsch
 */
#include "reverseLinkedList.h"
#include <iostream>
#include <cassert>

using namespace std;


struct Node
{
	int value;
	Node *next;

	//Node () : value(0), next(nullptr) {}
	Node(int value, Node *next = nullptr) : value(value), next(next) {}
	~Node()
	{
		Node *tmpNext = next;
		Node *tmpNextNext = nullptr;
		while (nullptr != tmpNext)
		{
			tmpNextNext = tmpNext->next;
			delete tmpNext;
			tmpNext = tmpNextNext;
		}
	}
};


Node * reverseLinkedList(Node *node)
{
	if (nullptr == node)
	{
		return nullptr;
	}

	Node *prev = nullptr;
	Node *cur = node;
	Node *next = node->next;

	while (nullptr != next)
	{
		cur->next = prev;
		prev = cur;
		cur = next;
		next = next->next;
	}

	// Update last as loop above is checking next != null
	cur->next = prev;

	return cur;
}


void reverseLinkedListMainHelper(Node *linkedList)
{
	Node *revLinkedList = reverseLinkedList(linkedList);

	Node *cur = revLinkedList;
	while (nullptr != cur)
	{
		cout << cur->value << " ";
		cur = cur->next;
	}
	cout << endl;
}


void reverseLinkedListMain()
{
	Node *linkedList1 = new Node(1, new Node(2, new Node(3, new Node(4))));
	reverseLinkedListMainHelper(linkedList1);

	Node *linkedList2 = new Node(1);
	reverseLinkedListMainHelper(linkedList2);

	Node *linkedList3 = new Node(1, new Node(2));
	reverseLinkedListMainHelper(linkedList3);
}
