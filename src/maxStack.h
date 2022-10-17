/*
 * maxStack.h
 *
 *  Created on: 2019-09-08
 *      Author: ckirsch
 */

#ifndef MAXSTACK_H_
#define MAXSTACK_H_
#include <stack>
using namespace std;

/* Q: Design a stack with a push, pop, and max function which returns max value in stack.
All operations run in O(1) time. */

/* Or could also have had instead of a maxNode pointer make it an oldMax pointer
 * then in the class have a variable for maxNode pointer 
 
 Or could have just stored in stack (value, max) and take max to be max(top, value). Need to track so 
 when pop from stack still have max. */
class MaxStackOverlay
{
	/* other way - will have easyier logic */
	struct NodeOther
	{
		int value;
		NodeOther *oldMaxNode;
	};
	NodeOther *maxNode;

	struct Node
	{
		int value;
		Node *maxNode;

		Node(int value, Node *maxNode = nullptr) :
			value(value), maxNode(maxNode) {}
	};

	stack<Node> maxStack;

public:
	void push(int value);
	void pop();
	int top();
	int max();
	bool empty();
};


void maxStackMain();


#endif /* MAXSTACK_H_ */
