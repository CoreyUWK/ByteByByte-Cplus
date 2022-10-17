/*
 * nthToLastLinkedList.cpp
 *
 *  Created on: 2019-09-08
 *      Author: ckirsch
 */
#include "nthToLastLinkedList.h"
#include <iostream>
#include <cassert>
#include <forward_list>
using namespace std;

class LinkedList {
public:
    class Node {
        public:
            int data;
            Node *next;
            
            Node(int data, Node *next = nullptr) : data(data), next(next) {}
    };
    
private:
    Node *head;

    Node* nthToLastHelper(int k, Node *cur, int &count) {
        if (cur == nullptr) {
            return nullptr;
        }
        
        Node *next = nthToLastHelper(k, cur->next, count);
        count += 1;
        if (count == k) {
            return cur;
        }
        return next;
    }

public:
    LinkedList() : head(nullptr) {}
	~LinkedList() {
		Node *cur = head;
		while (cur != nullptr) {
			Node *del = cur;
			cur = cur->next;
			delete del;
		}
	}

    void append(int data) {
        Node *newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node *cur = head;
            while (cur->next != nullptr) {
                cur = cur->next;
            }
            
            cur->next = newNode;
        }
    }
    
    Node* nthToLast(int k) {
        int count = 0;
        Node *nth = nthToLastHelper(k, head, count);
        return nth;
    }
    
    bool deleteNode(Node *n) {
        if (n == nullptr || n->next == nullptr) {
            return false;
        }
        
        n->data = n->next->data;
        n->next = n->next->next;
        return true;
    }
};


forward_list<int>::iterator nthToLastLinkedList(forward_list<int> &list, int n)
{
	auto follower = list.begin();
	auto cur = list.begin();

	for (int i = 0; cur != list.end() && i < n; ++i)
	{
		cur = next(cur);
	}

	if (cur == list.end())
	{
		return list.end();
	}

	while (next(cur) != list.end())
	{
		cur = next(cur);
		follower = next(follower);
	}

	return follower;
}


void nthToLastLinkedListMain()
{
	bool pass = true;

	forward_list<int> list = {1, 2, 3, 4, 5};

	assert(pass &= (5 == *nthToLastLinkedList(list, 0)));
	assert(pass &= (4 == *nthToLastLinkedList(list, 1)));
	assert(pass &= (3 == *nthToLastLinkedList(list, 2)));
	assert(pass &= (2 == *nthToLastLinkedList(list, 3)));
	assert(pass &= (1 == *nthToLastLinkedList(list, 4)));
	assert(pass &= (list.end() == nthToLastLinkedList(list, 5)));

   	LinkedList ll;
    for (int i = 1; i <= 10; ++i) {
        ll.append(i);
    }
    
    LinkedList::Node *nth = ll.nthToLast(3);
    assert(pass &= (8 == nth->data));
 
	cout << "Pass: " << pass << endl;
}


