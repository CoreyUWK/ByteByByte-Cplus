/*
 * priorityQueue.cpp
 *
 *  Created on: 2019-09-06
 *      Author: ckirsch
 */
#include "priorityQueue.h"
#include <cassert>
#include <iostream>

using namespace std;


void PriorityQueue::push(int value)
{
	// Add new item
	heap.push_back(value);

	// Bubble up new item if less/greater than parent
	int index = heap.size() - 1;
	while (index > 0)
	{
		int parentIndex = getParentIndex(index);

		if ( (PriorityQueueTypeMin == type && heap[parentIndex] <= heap[index]) ||
			 (PriorityQueueTypeMax == type && heap[parentIndex] >= heap[index])
			)
		{
			break;
		}

		swap(heap[parentIndex], heap[index]);

		// Update
		index = parentIndex;
	}
}


int PriorityQueue::pop()
{
	if (heap.size() == 0)
	{
		throw "Calling pop on empty queue";
	}

	int topToReturn = heap[0];

	// Pop top and move bottom to top
	int endIndex = heap.size() - 1;
	heap[0] = heap[endIndex];
	heap.pop_back();

	// Bubble down top
	endIndex = heap.size() - 1;
	int index = 0;

	int lastParentIndex = getParentIndex(heap.size() - 1);
	while (index <= lastParentIndex)
	{
		int leftChildIndex = getLeftChildIndex(index);
		int rightChildIndex = getRightChildIndex(index);

		if (PriorityQueueTypeMin == type)
		{
			int minChildIndex = leftChildIndex;
			if (rightChildIndex <= endIndex &&
					heap[rightChildIndex] < heap[leftChildIndex])
			{
				minChildIndex = rightChildIndex;
			}

			if (minChildIndex <= endIndex && heap[index] > heap[minChildIndex])
			{
				swap(heap[index], heap[minChildIndex]);

				// Update
				index = minChildIndex;
			}
			else
			{
				break;
			}
		}
		else if (PriorityQueueTypeMax == type)
		{
			int maxChildIndex = leftChildIndex;
			if (rightChildIndex <= endIndex &&
					heap[rightChildIndex] > heap[leftChildIndex])
			{
				maxChildIndex = rightChildIndex;
			}

			if (maxChildIndex <= endIndex && heap[index] < heap[maxChildIndex])
			{
				swap(heap[index], heap[maxChildIndex]);

				// Update
				index = maxChildIndex;
			}
			else
			{
				break;
			}
		}
	}

	return topToReturn;
}


void priorityQueueMain()
{
	bool pass = true;

	PriorityQueue pq(PriorityQueue::PriorityQueueTypeMin);
	pq.push(4);
	pq.push(6);
	pq.push(3);
	pq.push(8);
	pq.push(7);
	pq.push(1);

	assert(pass &= (1 == pq.pop()));
	assert(pass &= (3 == pq.pop()));
	assert(pass &= (4 == pq.pop()));
	assert(pass &= (6 == pq.pop()));
	assert(pass &= (7 == pq.pop()));
	assert(pass &= (8 == pq.pop()));

	cout << "Pass: " << pass << endl;
}


//------------------------------------------------------------
template<typename T>
class PriorityQueue2 {
public:
    enum Type {
        max,
        min
    };
    
private:
    vector<T> heap;
    int size;
    Type type;

public:
    PriorityQueue2(Type type) : type(type), size(0) {}
    
    int getParentIdx(int index) {
        if (index <= 0) {
            return -1;
        }
        return (index - 1) / 2;
    }
    
    int getChildLeft(int parent) {
        return (parent*2) + 1;
    }
    int getChildRight(int parent) {
        return (parent*2) + 2;
    }
    
    bool cmpParent(int index) {
        int parent = getParentIdx(index);
        if (type == max) {
            if (heap[parent] < heap[index]) {
                return true;
            }
        }
        else {
            if (heap[parent] > heap[index]) {
                return true;
            }
        }
        return false;
    }
    
    bool cmpChild(int parent) {
        int childLeft = getChildLeft(parent);
        int childRight = getChildRight(parent);
        int child;
        if (childRight < size) {
            child = childRight;
        }
        else if (childLeft < size) {
            child = childLeft;
        }
        else {
            return false;
        }
        
        if (type == max) {
            if (heap[parent] < heap[child]) {
                return true;
            }
        }
        else {
            if (heap[parent] > heap[child]) {
                return true;
            }
        }
        return false;
    }
    
    void push(T data) {
        // Push new item to end of heap
        if (size < heap.size()) {
            heap[size] = data;
        }
        else {
            heap.push_back(data);
        }
        
        int cur = size;
        while (cmpParent(cur)) {
            int parent = getParentIdx(cur);
            std::swap(heap[parent], heap[cur]);
            cur = parent;
            
            if (parent == 0) break;
        }
        ++size;
    }
    
    T pop() {
        if (size == 0) {
            throw "Empty Heap";
        }
        T top = heap[0];
        if (size > 1) {
            heap[0] = heap[size - 1];
            
            // Bubble down
            int cur = 0;
            while (cmpChild(cur)) {
                int childLeft = getChildLeft(cur);
                int childRight = getChildRight(cur);
                
                int child;
                if (childRight < size && heap[childRight] < heap[childLeft]) {
                    child = childRight;
                }
                else {
                    child = childLeft;
                }
        
                std::swap(heap[cur], heap[child]);
                cur = child;
            }
        }
        
        --size;        
        return top;
    }
    
    void debugPrint() {
        cout << "DebugPrint: ";
        for (auto i : heap) {
            cout << i << " ";
        }
        cout << endl;
    }
};

int ThisTest() {
	bool pass = true;

	PriorityQueue2<int> pq(PriorityQueue2<int>::Type::min);
	pq.push(4);
	pq.push(6);
	pq.push(3);
	pq.push(8);
	pq.push(7);
	pq.push(1);
    
    pq.debugPrint();
    
    int value;
    
    value = pq.pop();
	cout << value << endl;
    pq.debugPrint();
	assert(pass &= (1 == value));
	
	value = pq.pop();
	cout << value << endl;
    pq.debugPrint();
	assert(pass &= (3 == value));
	
	value = pq.pop();
	cout << value << endl;
	pq.debugPrint();
	assert(pass &= (4 == value));
	
	value = pq.pop();
	cout << value << endl;
	pq.debugPrint();
	assert(pass &= (6 == value));
	
	value = pq.pop();
	cout << value << endl;
	pq.debugPrint();
	assert(pass &= (7 == value));
	
	value = pq.pop();
	cout << value << endl;
	pq.debugPrint();
	assert(pass &= (8 == value));

	cout << "Pass: " << pass << endl;

    return 0;
}