/*
 * randomLinkedList.cpp
 *
 *  Created on: 2019-08-29
 *      Author: ckirsch
 */
#include "randomLinkedList.h"
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <queue>
using namespace std;

/* Given a linked list where each node has two pointers 
one to the next node and one to random node in list,
write function to clone list.
eg.
1->2->3->4->null
v  v  v  v
3  1  3  2 

*/

struct Node
{
	int value;
	Node *next;
	Node *random;

	//Node () : value(0), next(nullptr), random(nullptr) {}
	Node(int value, Node *next = nullptr, Node *random = nullptr) : value(value), next(next), random(random) {}
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


// Time: O(n) Space: O(2n)=O(n)
Node * randomLinkedListCopy_hash(Node *root)
{
	if (nullptr == root)
	{
		return nullptr;
	}

	unordered_map<Node *, Node *> hash; // Map Orig Current -> Copy Current
	queue<pair<Node *, Node *>> pendingTasks; // Pair of Copy Current -> Orig Random

	Node *copyRoot = nullptr; // Root to copy list

	// Copy Nodes
	Node *curOrigNode = root;
	Node *curCopyNode = copyRoot;
	do
	{
		// Handle initial condition of copy pointing to null list
		if (nullptr == copyRoot)
		{
			curCopyNode = copyRoot = new Node(root->value);
		}
		else
		{
			curCopyNode = curCopyNode->next = new Node(curOrigNode->value);
		}

		// Update hash
		hash[curOrigNode] = curCopyNode; // {A, A'}
		if (hash.find(curOrigNode->random) != hash.end())
		{
			curCopyNode->random = hash[curOrigNode->random];
		}
		else
		{
			pendingTasks.push(make_pair(curCopyNode, curOrigNode->random)); // {A', C}
		}

		// Handle pending tasks for random pointers that pointed to future nodes, where we just reached one
		while (!pendingTasks.empty())
		{
			auto top = pendingTasks.front();

			if (hash.find(top.second) != hash.end())
			{
				top.first->random = hash[top.second];
				pendingTasks.pop();
			}
			else
			{
				break;
			}
		}

		// Update original next
		curOrigNode = curOrigNode->next;
	} while (nullptr != curOrigNode);

	return copyRoot;
}

Node * randomLinkedListCopy_HashSimple(Node *root) {
    if (root == nullptr) return nullptr;
    
    Node *head = nullptr;
    Node *cur = nullptr;
    
    unordered_map<Node*,Node*> origToCopy;

    Node *orig = root;
    while (orig != nullptr) {
        if (cur == nullptr) {
            head = new Node(orig->value);
            cur = head;
        }
        else {
            cur->next = new Node(orig->value);
            cur = cur->next;
        }
        
        origToCopy[orig] = cur;
        orig = orig->next;
    }
    
    orig = root;
    cur = head;
    while (orig != nullptr) {
        cur->random = origToCopy[orig->random];
        orig = orig->next;
        cur = cur->next;
    }
    
    return head;
}

// Time: O(n) Space: O(1)
Node * randomLinkedListCopy_inplace(Node *root)
{
	if (nullptr == root)
	{
		return nullptr;
	}

	// 1) O(n) inject copy nodes into original
	Node *curOrigNode = root;
	while (nullptr != curOrigNode)
	{
		Node *copy = new Node(curOrigNode->value, curOrigNode->next);
		curOrigNode->next = copy;

		// Update
		curOrigNode = curOrigNode->next->next;
	}
	Node * copyRoot = root->next;

	// 2) Update copy nodes random pointers
	curOrigNode = root;
	while (nullptr != curOrigNode)
	{
		curOrigNode->next->random = curOrigNode->random->next;

 		// Update to next
 		curOrigNode = curOrigNode->next->next;
	}

	// 3) Separate original and copy
	Node * copyCur = nullptr;
	curOrigNode = root;
	while (nullptr != curOrigNode)
	{
		copyCur = curOrigNode->next;
		curOrigNode->next = curOrigNode->next->next;
		copyCur->next = (nullptr == copyCur->next) ? copyCur->next : copyCur->next->next;

		// Update
		curOrigNode = curOrigNode->next;
	}

	return copyRoot;
}


int randomLinkedListMain()
{
	bool pass = true;

	Node *root = new Node(1, new Node(2, new Node(3, new Node(4))));
	root->random = root->next->next;
	root->next->random = root;
	root->next->next->random = root->next->next;
	root->next->next->next->random = root->next;

	unordered_map<int, int> hash({
			{1,3},
			{2,1},
			{3,3},
			{4,2}
		});

	Node * copyHash = randomLinkedListCopy_hash(root); // 1
	Node * copyInPlace = randomLinkedListCopy_inplace(root); // 2

	Node *ptrCopy = nullptr;

	// 1
	assert(pass &= (nullptr != copyHash));
	ptrCopy = copyHash;
	while (nullptr != ptrCopy)
	{
		assert(pass &= (hash.find(ptrCopy->value) != hash.end()));
		assert(pass &= (hash[ptrCopy->value] == ptrCopy->random->value));
		ptrCopy = ptrCopy->next;
	}

	// 2
	assert(pass &= (nullptr != copyInPlace));
	ptrCopy = copyInPlace;
	while (nullptr != ptrCopy)
	{
		assert(pass &= (hash.find(ptrCopy->value) != hash.end()));
		assert(pass &= (hash[ptrCopy->value] == ptrCopy->random->value));
		ptrCopy = ptrCopy->next;
	}

	cout << "Pass: " << pass << endl;

	return 0;
}

