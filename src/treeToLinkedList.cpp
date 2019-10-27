/*
 * treeToLinkedList.cpp
 *
 *  Created on: 2019-08-26
 *      Author: ckirsch
 */
#include "treeToLinkedList.h"
#include <iostream>

using namespace std;

namespace TreeToLinkedList
{
struct Node
{
	int value;
	Node *left;
	Node *right;

	Node(int value) : value(value), left(nullptr), right(nullptr) {}
	Node(int value, Node *left, Node *right) : value(value), left(left), right(right) {}

	~Node() {
		Node *tmp = nullptr;

		if (left != nullptr)
		{
			tmp = left;
			left = nullptr;
			delete tmp;
			tmp = nullptr;
		}

		// Only delete right if tree, if list will cause memory leaks
		/*if (right != nullptr)
		{
			tmp = right;
			right = nullptr;
			delete right;
			tmp = nullptr;
		}*/
	}
};


Node * concatenate(Node *a, Node *b)
{
	if (a == nullptr) return b;
	if (b == nullptr) return a;

	Node * aEnd = a->left; // Last node in linked list a
	Node * bEnd = b->left; // Last node in linked list b

	a->left = bEnd; // wrap
	aEnd->right = b; // inside

	b->left = aEnd; // inside
	bEnd->right = a; // wrap

	return a;
}

Node * treeToLinkedList(Node * root)
{
	if (root == nullptr) return root;
	Node *leftList = treeToLinkedList(root->left);
	Node *rightList = treeToLinkedList(root->right);

	// setup
	root->left = root;
	root->right = root;

	root = concatenate(leftList, root);
	root = concatenate(root, rightList);

	return root;
}
}

int treeToLinkedListMain()
{
	typedef TreeToLinkedList::Node Node;
	Node *root = new Node(1, new Node(2, new Node(4), new Node(5)), new Node(3, new Node(6), new Node(7)));
	Node *head = treeToLinkedList(root);

	Node *ptr = head;
	while (ptr != nullptr)
	{
		cout << ptr->value << " ";
		ptr = ptr->right;

		if (ptr == head)
		{
			cout << endl;
			break;
		}
	}

	//delete root;

	return 0;
}
