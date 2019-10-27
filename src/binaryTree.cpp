/*
 * binaryTree.cpp
 *
 *  Created on: 2019-08-03
 *      Author: ckirsch
 */
#include "binaryTree.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <array>
#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;


template<typename T>
void BTree<T>::insertLevelOrder(T value)
{
	queue<BTreeNode *> insertionFifo;

	if (!root) // Then empty tree and root = nullptr
	{
		root = make_unique<BTreeNode>(value);
 	}
	else
	{
		insertionFifo.push(root.get());

		while (!insertionFifo.empty())
		{
			BTreeNode * lastNode = insertionFifo.front();
			insertionFifo.pop();

			if (!lastNode->left)
			{
				lastNode->left = make_unique<BTreeNode>(value);
				break;
			}
			else if (!lastNode->right)
			{
				lastNode->right = make_unique<BTreeNode>(value);
				break;
			}
			else
			{
				insertionFifo.push(lastNode->left.get());
				insertionFifo.push(lastNode->right.get());
			}
		}
	}
}


template<typename T>
void BTree<T>::insertLevelOrder(const vector<T>& values)
{
	for (auto value : values)
	{
		insertLevelOrder(value);
	}
}


template<typename T>
void BTree<T>::insert(T value, uint position)
{
	// Note: Could add parent pointer into queueNode so that when finding position can enter nullptr
	// into tree and check the position to add.  When parent is nullptr then don't add to queue, so
	// queue will decrease in size
	struct queueNode
	{
		BTreeNode * node;
		uint position;
	};

	if (position == 0)
	{
		throw "Position must start from 1 to spot";
	}
	else if (!root && position > 0)
	{
		throw "Position does not exist in tree";
	}
	else if (!root && 1 == position)
	{
		root = make_unique<BTreeNode>(value);
	}
	else
	{
		queue<queueNode> fifo;
		bool addedNode = false;

		fifo.push({root.get(), 1});
		while (!fifo.empty())
		{
			auto top = fifo.front();
			fifo.pop();

			uint childPositionLeft = top.position * 2;
			uint childPositionRight = childPositionLeft + 1;

			// Check if position matches
			if (top.position == position)
			{
				top.node->value = value;
				addedNode = true;
				break;
			}
			else if (childPositionLeft == position)
			{
				if (!top.node->left)
				{
					top.node->left = make_unique<BTreeNode>(value);
				}
				else
				{
					top.node->left->value = value;
				}
				addedNode = true;
				break;
			}
			else if (childPositionRight == position)
			{
				if (!top.node->right)
				{
					top.node->right = make_unique<BTreeNode>(value);
				}
				else
				{
					top.node->right->value = value;
				}
				addedNode = true;
				break;
			}

			// Add children nodes to queue for later processing
			if (top.node->left)
			{
				fifo.push({top.node->left.get(), childPositionLeft});
			}
			if (top.node->right)
			{
				fifo.push({top.node->right.get(), childPositionRight});
			}
		}

		if (!addedNode)
		{
			throw "Position does not exist in tree";
		}
	}
}


template<typename T>
vector<T> BTree<T>::printLevelOrder()
{
	BTreeNode * top = nullptr;
	queue<BTreeNode *> fifo;
	vector<T> output;

	if (!root)
	{
		cout << "NULL" << endl;
		return output;
	}

	fifo.push(root.get());
	while (!fifo.empty())
	{
		top = fifo.front();
		fifo.pop();

		cout << top->value << " ";
		output.push_back(top->value);

		if (top->left)
		{
			fifo.push(top->left.get());
		}
		if (top->right)
		{
			fifo.push(top->right.get());
		}
	}
	cout << endl;

	return output;
}


/* Bottom-up approach */
template<typename T>
int BTree<T>::balancedHeight(BTreeNode *node)
{
	if (nullptr == node)
	{
		return 0;
	}

	int leftHeight = balancedHeight(node->left.get());
	int rightHeight = balancedHeight(node->right.get());

	if (leftHeight == -1 || rightHeight == -1)
	{
		return -1;
	}
	else if (abs(leftHeight - rightHeight) > 1)
	{
		return -1;
	}

	return max(leftHeight, rightHeight) + 1;
}


template<typename T>
bool BTree<T>::isBalanced()
{
	return (-1 == balancedHeight(root.get())) ? false : true;
}


template<typename T>
int BTree<T>::longestConsecutiveBranchHelper(BTreeNode *node, int count)
{
	if (nullptr == node)
	{
		return count;
	}

	int leftMaxCount = 0;
	int rightMaxCount = 0;

	if (node->left)
	{
		leftMaxCount = longestConsecutiveBranchHelper(node->left.get(),
			(node->value + 1 == node->left->value) ? count + 1 : 1);
	}

	if (node->right)
	{
		rightMaxCount = longestConsecutiveBranchHelper(node->right.get(),
			(node->value + 1 == node->right->value) ? count + 1 : 1);
	}

	if (count > leftMaxCount && count > rightMaxCount)
	{
		return count;
	}
	else if (leftMaxCount > rightMaxCount)
	{
		return leftMaxCount;
	}
	else
	{
		return rightMaxCount;
	}
}


template<typename T>
int BTree<T>::longestConsecutiveBranch()
{
	if (!root)
	{
		return 0;
	}

	return longestConsecutiveBranchHelper(root.get(), 1);
}


template<typename T>
void BTree<T>::treeToLinkedListHelper(BTreeNode *node, list<T> &linkedList)
{
	if (nullptr == node)
	{
		return;
	}

	if (node->left)
	{
		treeToLinkedListHelper(node->left.get(), linkedList);
	}

	linkedList.push_back(node->value);

	if (node->right)
	{
		treeToLinkedListHelper(node->right.get(), linkedList);
	}
}


template<typename T>
list<T> BTree<T>::treeToLinkedList()
{
	list<T> linkedList;
	treeToLinkedListHelper(root.get(), linkedList);
	return linkedList;
}


template<typename T>
bool BTree<T>::pathToHelper(BTreeNode *node, T val, stack<T> &path)
{
	if (nullptr == node)
	{
		return false;
	}

	// Add current node to path
	path.push(node->value);

	// Check if found and return as done
	if (val == node->value)
	{
		return true;
	}

	// If not found search left and right
	bool foundLeft = (node->left) ? pathToHelper(node->left.get(), val, path) : false;
	bool foundRight = (!foundLeft && node->right) ? pathToHelper(node->right.get(), val, path) : false;

	// If not found in children pop off current parent
	if (!foundLeft && !foundRight)
	{
		path.pop();
	}

	return foundLeft || foundRight;
}


template<typename T>
bool BTree<T>::pathTo(T val, stack<T> &path)
{
	if (root)
	{
		return pathToHelper(root.get(), val, path);
	}

	return false;
}


// This could have been made to take node's and return node pointer
// 1) Pre-process and find paths to nodes with value O(n), then compare paths to find common ancestor O(logn) => O(n)
// 2) Search tree for nodes and if found return true up the tree to parent, if both left and right are true found and return node O(n)
template<typename T>
bool BTree<T>::lowestCommonAncester(T val1, T val2, T &lca)
{
	stack<T> path1, path2;

	if (root)
	{
		if (val1 == val2)
		{
			lca = val1;
			return true;
		}
	}

	if (pathTo(val1, path1) && pathTo(val2, path2))
	{
		while (path1.size() > path2.size())
		{
			path1.pop();
		}

		while (path2.size() > path1.size())
		{
			path2.pop();
		}

		if (path1.empty() || path2.empty())
		{
			return false;
		}

		while (path1.top() != path2.top())
		{
			path1.pop();
			path2.pop();
		}

		lca = path1.top();
		return true;
	}

	return false;
}


template<typename T>
bool BTree<T>::lowestCommonAncester2Helper(BTreeNode *node,
		T val1, bool &foundVal1,
		T val2, bool &foundVal2,
		T &lca)
{
	if (nullptr == node)
	{
		return false;
	}
	else if (node->value == val1)
	{
		foundVal1 = true;
 		return true;
	}
	else if (node->value == val2)
	{
		foundVal2 = true;
 		return true;
	}

	bool isLeft = false;
	bool isRight = false;

	isLeft = (node->left) ?
			lowestCommonAncester2Helper(node->left.get(),
					val1, foundVal1,
					val2, foundVal2,
					lca) :
			false;

	isRight = (node->right) ?
			lowestCommonAncester2Helper(node->right.get(),
					val1, foundVal1,
					val2, foundVal2,
					lca) :
			false;

	if (isLeft && isRight)
	{
		lca = node->value;
		return true;
	}
	else if (isLeft || isRight)
	{
		return true;
	}

	return false;
}


template<typename T>
bool BTree<T>::lowestCommonAncester2(T val1, T val2, T &lca)
{
	if (root)
	{
		if (val1 == val2)
		{
			lca = val1;
			return true;
		}

		bool foundVal1 = false,
			 foundVal2 = false;
		return (lowestCommonAncester2Helper(root.get(), val1, foundVal1, val2, foundVal2, lca) &&
				foundVal1 &&
				foundVal2);
	}

	return false;
}


/* Print out inorder without recursion */
template<typename T>
void BTree<T>::printInOrderGoLeft(BTreeNode* node, stack<BTreeNode *> &st)
{
	while (nullptr != node)
	{
		st.push(node);
		node = node->left.get();
	}
}


// Time: O(n) since hitting each node once
// Space: O(n) worst case if tree was one path (all node on one path) so stack will contain all nodes
template<typename T>
void BTree<T>::printInOrder()
{
	stack<BTreeNode *> st;

	// Go left and push to stack
	printInOrderGoLeft(root.get(), st);

	while (!st.empty())
	{
		BTreeNode *top = st.top();
		st.pop();

		cout << top->value << " ";

		if (nullptr != top->right)
		{
			printInOrderGoLeft(top->right.get(), st);
		}
	}

	cout << endl;
}


/* 1) DFS with inorder traversal where each path returns max of children then node can compare
 * left max < node < right min
 * 2) DFS inorder traversal and just track previous nodes value and make sure next is greater since
 * hitting all nodes in order of expected greatness
 * left, node, right
 * 3) Pass down to each node the allowed range for it's node value and check is in range
 */

template<typename T>
void BTree<T>::isBinarySearchTree_DFSInOrderHelper(BTreeNode *node, vector<T> &inOrder)
{
	if (nullptr == node)
	{
		return;
	}

	if (node->left)
	{
		isBinarySearchTree_DFSInOrderHelper(node->left.get(), inOrder);
	}

	inOrder.push_back(node->value);

	if (node->right)
	{
		isBinarySearchTree_DFSInOrderHelper(node->right.get(), inOrder);
	}
}

template<typename T>
bool BTree<T>::isBinarySearchTree_DFSInOrder()
{
	vector<int> inOrder;
	isBinarySearchTree_DFSInOrderHelper(root.get(), inOrder);

	for (uint i = 1; i < inOrder.size(); ++i)
	{
		if (inOrder[i - 1] > inOrder[i])
		{
			return false;
		}
	}

	return true;
}


/* Note can't just check node->left <= node < node->right cause won't validate grandparents to children
 * ex. 5   => node 2 is good but node 5 bad
 *    /\
 *   2  7
 *  /\  /\
 * 1  9 6 8
 *
 * That's why passing down range
 * */
template<typename T>
bool BTree<T>::isBinarySearchTree(BTreeNode *node, T min, T max)
{
	if (nullptr == node)
	{
		return true;
	}
	else if (node->value < min || max <= node->value)
	{
		return false;
	}

	bool leftIsBst = true;
	bool rightIsBst = true;

	if (node->left)
	{
		leftIsBst = isBinarySearchTree(node->left.get(), min, node->value);
	}

	if (node->right)
	{
		rightIsBst = isBinarySearchTree(node->right.get(), node->value + 1, max);
	}

	return leftIsBst && rightIsBst;
}

template<typename T>
bool BTree<T>::isBinarySearchTree()
{
	return isBinarySearchTree(root.get(), std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}



int binaryTreeMain()
{
	bool pass = true;
	BTree<int> bTree;

	/*  1
	  /   \
	 2      3
	/ \   /  \
   4   5 6    7
   -------------
    \    /\   /\
     8  9 10 11 12
       /
      13

	*/

	// Added to tree using level order
	bTree.insertLevelOrder(1);

	bTree.insertLevelOrder(2);
	bTree.insertLevelOrder(3);

	bTree.insertLevelOrder(4);
	bTree.insertLevelOrder(5);

	bTree.insertLevelOrder(6);
	bTree.insertLevelOrder(7);

	// Print and assert for level order insert
	assert(pass &= (vector<int>{1,2,3,4,5,6,7} == bTree.printLevelOrder()));

	// Insert remaining in random order
	bTree.insert(8, 9);
	bTree.insert(9, 12);
	bTree.insert(10, 13);
	bTree.insert(11, 14);
	bTree.insert(12, 15);
	bTree.insert(13, 24);

	cout << "Print InOrder:" << endl;
	bTree.printInOrder();

	// Print and assert for level order insert
	assert(pass &= (vector<int>{1,2,3,4,5,6,7,8,9,10,11,12,13} == bTree.printLevelOrder()));

	// Check if balanced
	assert(pass &= (true == bTree.isBalanced()));

	// Make tree not balanced
	bTree.insert(13, 49);
	assert(pass &= (false == bTree.isBalanced()));

	// Get longest branch with consecutive incrementing values
	assert(pass &= (2 == bTree.longestConsecutiveBranch()));

	// Convert tree1 to linked list
	list<int> linkedList = bTree.treeToLinkedList();
	for (const int &elem : linkedList)
	{
		cout << "<->" << elem;
	}
	cout << endl;
	linkedList.clear();

	int lca;
	assert(pass &= (bTree.lowestCommonAncester(8, 5, lca)));
	assert(pass &= (lca == 2));
	assert(pass &= (bTree.lowestCommonAncester2(8, 5, lca)));
	assert(pass &= (lca == 2));

	assert(pass &= (bTree.lowestCommonAncester(2, 3, lca)));
	assert(pass &= (lca == 1));
	assert(pass &= (bTree.lowestCommonAncester2(2, 3, lca)));
	assert(pass &= (lca == 1));

	assert(pass &= (bTree.lowestCommonAncester(11, 9, lca)));
	assert(pass &= (lca == 3));
	assert(pass &= (bTree.lowestCommonAncester2(11, 9, lca)));
	assert(pass &= (lca == 3));

	assert(pass &= (false == bTree.lowestCommonAncester(15, 9, lca)));
	assert(pass &= (false == bTree.lowestCommonAncester2(15, 9, lca)));

	// Make new tree
	/*      0:1
	 *   /      \
	 *  1:2      2:1
	 *  /  \     /  \
 	 * 1:1 2:3  1:1 3:2*/
	BTree<int> bTree2;
	bTree2.insertLevelOrder(0);

	bTree2.insertLevelOrder(1);
	bTree2.insertLevelOrder(2);

	bTree2.insertLevelOrder(1);
	bTree2.insertLevelOrder(2);
	bTree2.insertLevelOrder(1);
	bTree2.insertLevelOrder(3);
	// Get longest branch with consecutive incrementing values for new tree
	assert(pass &= (3 == bTree2.longestConsecutiveBranch()));

	// Convert tree2 to linked list
	linkedList = bTree2.treeToLinkedList();
	for (const int &elem : linkedList)
	{
		cout << "<->" << elem;
	}
	cout << endl;
	linkedList.clear();

	// 3
	// Make new tree
	/*      10
	 *    /    \
	 *   5      15
	 *  / \    /  \
	 * 1   8  12  20
	 *    / \
	 *   6   9
	 *   */
	BTree<int> bTree3;
	bTree3.insertLevelOrder(10);

	bTree3.insertLevelOrder(5);
	bTree3.insertLevelOrder(15);

	bTree3.insertLevelOrder(1);
	bTree3.insertLevelOrder(8);
	bTree3.insertLevelOrder(12);
	bTree3.insertLevelOrder(20);
	bTree3.insert(6, 10);
	bTree3.insert(9, 11);
	bTree3.printInOrder();

	assert(pass &= bTree3.isBinarySearchTree_DFSInOrder());
	assert(pass &= bTree3.isBinarySearchTree());

	cout << "Pass: " << pass << endl;

	return 0;
}
