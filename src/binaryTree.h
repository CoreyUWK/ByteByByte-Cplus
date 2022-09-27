/*
 * binaryTree.h
 *
 *  Created on: 2019-08-03
 *      Author: ckirsch
 */

#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <memory>
#include <queue>
#include <vector>
#include <list>
#include <stack>
using namespace std;

/* Note:
 * To create binary tree in C would have a node struct and then API interfaces:
 * 	Node * createNode(int value)
 * 	void insert(Node *root, int data) - based on left < right */

/* Q: Given a binary tree, write a function to test if the tree is a binary search tree. */

template <typename T>
class BTree
{
	struct BTreeNode
	{
		T value;
		unique_ptr<BTreeNode> left;
		unique_ptr<BTreeNode> right;

		BTreeNode(T value) : value(value) {}
	};

	unique_ptr<BTreeNode> root;

	int balancedHeight(BTreeNode * node);
	int longestConsecutiveBranchHelper(BTreeNode *node, int count);
	void treeToLinkedListHelper(BTreeNode *node, list<T> &linkedList);

	bool pathToHelper(BTreeNode *node, T val, stack<T> &path);
	bool lowestCommonAncester2Helper(BTreeNode *node,
			T val1, bool &foundVal1,
			T val2, bool &foundVal2,
			T &lca);

	void printInOrderGoLeft(BTreeNode* node, stack<BTreeNode *> &st);

	void isBinarySearchTree_DFSInOrderHelper(BTreeNode *node, vector<T> &inOrder);
	bool isBinarySearchTree(BTreeNode *node, T min, T max);

public:
	void insertLevelOrder(T value);
	void insertLevelOrder(const vector<T>& values);
	void insert(T value, uint position);
	vector<T> printLevelOrder();
	void printInOrder();

	bool isBalanced();
	int longestConsecutiveBranch();
	list<T> treeToLinkedList();

	bool pathTo(T val, stack<T> &path);
	bool lowestCommonAncester(T val1, T val2, T &lca);
	bool lowestCommonAncester2(T val1, T val2, T &lca);

	bool isBinarySearchTree_DFSInOrder();
	bool isBinarySearchTree();
};


int binaryTreeMain();

#endif /* BINARYTREE_H_ */
