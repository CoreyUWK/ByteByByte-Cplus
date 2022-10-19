/*
 * randomBinaryTree.cpp
 *
 *  Created on: 2019-08-29
 *      Author: ckirsch
 */
#include "randomBinaryTree.h"
#include <iostream>
#include <cassert>
#include <queue>
//#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <random>
#include <chrono>

using namespace std;

/* Implement a binary tree with a method getRandomNode() that returns a random node. */

/* 1) convert tree into array (inorder traverse), generate a random number and pull from array O(n) unless makes tree represented by array
 * 2) generate random number and then traverse tree BFS so that we jump n times to get random node O(n)
 * 3) To reduce the time of searching the tree from O(n) to O(logn) could add a why of checking node index in O(1).
 * Hard to make index in O(1) during creation of tree since just having a count would not be correct if nodes can
 * be added anywhere in tree. Could create index's in getRandNode call but will be O(n) same as 1).
 * If you add #children to node then can search where (indexL < indexR) < indexTop so a BFS level order and search only
 * height of tree O(logn) for randNode */

namespace RandomBinaryTree
{
struct Node
{
	int value;
	Node *left;
	Node *right;
	int numChildren;

	Node (int value) : value(value), left(nullptr), right(nullptr), numChildren(0) {}
	Node (int value, Node *left, Node *right) : value(value), left(left), right(right), numChildren(0)
	{
		if (nullptr != left)
		{
			numChildren += left->numChildren + 1;
		}

		if (nullptr != right)
		{
			numChildren += right->numChildren + 1;
		}
	}

	~Node()
	{
		if (nullptr != left)
		{
			delete left;
			left = nullptr;
		}
		if (nullptr != right)
		{
			delete right;
			right = nullptr;
		}
	}
};


Node * randomBinaryTreeGet(Node *root, std::default_random_engine &generator)
{
	if (nullptr == root)
	{
		return nullptr;
	}

	int randomCount = 0;

	/* generate secret number between 1 and 10: */
	//randomCount = (rand() % (root->numChildren + 1)) + 1; ** not using bad

	std::uniform_int_distribution<int> distribution(1, root->numChildren + 1);
	randomCount = distribution(generator);

	//cout << "Count: " << randomCount << " ";

	// Perform log(n) search for random node
	Node *randomNode = root;
	while (nullptr != randomNode)
	{
		if (randomCount == (randomNode->numChildren + 1))
		{
			break;
		}
		else if (randomCount <= (randomNode->left->numChildren + 1))
		{
			randomNode = randomNode->left;
		}
		else
		{
			randomCount -= (randomNode->left->numChildren + 1); // Remove left count to reset a count of 1 == left most from current(right)
			randomNode = randomNode->right;
		}
	}

	//cout << "Val: " << randomNode->value << endl;

	return randomNode;
}


void randomBinaryTreePrint(Node *root)
{
	if (nullptr == root)
	{
		return;
	}

	queue<Node *> bfsQueue;
	bfsQueue.push(root);
	bfsQueue.push(nullptr);

	while (!bfsQueue.empty())
	{
		auto top = bfsQueue.front();
		bfsQueue.pop();

		if (nullptr == top)
		{
			cout << endl;

			// Only add null if more children exist to be processed
			if (!bfsQueue.empty())
			{
				bfsQueue.push(nullptr);
			}
			continue;
		}

		cout << "[" << top->value << ", " << top->numChildren << "] ";

		if (nullptr != top->left)
		{
			bfsQueue.push(top->left);
		}
		if (nullptr != top->right)
		{
			bfsQueue.push(top->right);
		}
	}
}
}

int randomBinaryTreeMain()
{
	typedef RandomBinaryTree::Node Node;
	Node *root = new Node(4,
			new Node(2,
					new Node(1), new Node(3)),
			new Node(6,
					new Node(5), new Node(7)));

	randomBinaryTreePrint(root);

	/* initialize random seed: */
	// srand (time(NULL)); ** bad not using
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);

	cout << "Random Nodes: ";
	for (int i = 0; i < root->numChildren * 2; ++i)
	{
		Node *randNode = randomBinaryTreeGet(root, generator);
		cout << randNode->value << " ";
	}
	cout << endl;

	delete root;

	return 0;
}

