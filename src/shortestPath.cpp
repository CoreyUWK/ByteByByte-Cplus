/*
 * shortestPath.cpp
 *
 *  Created on: 2019-08-29
 *      Author: ckirsch
 */
#include "shortestPath.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <unordered_map>
#include <list>
#include <unordered_set>

using namespace std;

/* Given a directed graph, find the shortest path between 2 nodes if one exists
eg.
1------------->2
^\			   |
| \			   |
|   -->3	   |
| /			   |
|/			   V
4<-------------5 

shortest path(2,3) = 2->5->4->3
*/

namespace shortestPath
{
struct Node
{
	int value;
	vector<Node*> neighbours;
};


// Time: O(n) as potentially might visit all nodes
// Space: O(n) if all node contained on same level
// Breadth first search is supposed to be more efficient for graphs as you don't have to search the whole tree
// as well, BFS will have a larger recursive stack if graph is large.  If graph large doing BFS
// will search children nodes of current node before going deeper
vector<Node *> shortestPath(Node *a, Node *b)
{
	vector<Node *> path;

	if (nullptr == a || nullptr == b)
	{
		return path;
	}
	else if (a == b)
	{
		path.push_back(a);
		return path;
	}

	queue<Node *> dfsQueue;
	unordered_map<Node *, Node *> visited;

	dfsQueue.push(a);
	visited[a] = nullptr;

	// DFS to fill visited nodes until find node b then will have to reverse traverse to get path
	while (!dfsQueue.empty())
	{
		Node *cur = dfsQueue.front();
		dfsQueue.pop();

		for (auto neighbour : cur->neighbours)
		{
			if (visited.find(neighbour) == visited.end())
			{
				visited[neighbour] = cur;

				// Found node b
				if (b == neighbour)
				{
					break;
				}

				dfsQueue.push(neighbour);
			}
		}
	}

	if (visited.find(b) == visited.end())
	{
		return path;
	}

	path.push_back(b);
	while (path[0] != a)
	{
		path.insert(path.begin(), visited[path[0]]);
	}

	return path;
}



void shortestPath_DFSHelper(Node *a, Node *b, list<Node*> &bestPath, list<Node*> &path, 
        unordered_set<Node*> visited) {
    path.push_back(a);
    
	// check if completed a path
	if (a == b) { 
		// Check if this path is best
        if (bestPath.empty() || path.size() < bestPath.size()) {
            bestPath.clear();
            for (auto n : path) {
                bestPath.push_back(n);
            }
        }
        return; // finished this path search
    }
    
	if (bestPath.empty() || (!bestPath.empty() && path.size() < bestPath.size()) ) {
		// continue searching current path, try per neighbour
		for (auto n : a->neighbours) {
			if (visited.find(n) == visited.end()) {
				visited.insert(n);
				shortestPath_DFSHelper(n, b, bestPath, path, visited);
			}
		}
	}

	// backtrack on path search as returning
    path.pop_back();
}

/* THis is solving with DFS, and one above from the solution performs in BFS.
BFS will not have to perform backtracking as the first time hitting the end node b, that will be the shortest path 
due to BFS searching neighbours first instead of going down path. 
Hence. BFS more efficient O(n) worst case for visiting all nodes once. Where as DFS could search each node multiple times O(n^n).*/
list<Node*> shortestPath_DFS(Node *a, Node *b) {
    list<Node*> bestPath;
    unordered_set<Node*> visited; // Prevent searching same nodes in path
    
    list<Node*> path; // tmp to track current path traversing on. When a->b complete compares to bestPath
    shortestPath_DFSHelper(a, b, bestPath, path, visited);
    
    return bestPath;
}


list<Node*> shortestPath_BFS(Node *a, Node *b) {
	list<Node*> path;
	if (a == nullptr || b == nullptr) {
		return path;
	}
	if (a == b) {
		path.push_back(a);
		return path;
	}

	queue<Node*> visited;
	unordered_map<Node*, Node*> childToParent;

	visited.push(a);
	childToParent[a] = nullptr;
	while (!visited.empty()) {
		auto top = visited.front();
		visited.pop();
        
		if (top == b) {
			break;
		}

		for (auto neighbour : top->neighbours) {
			if (childToParent.find(neighbour) != childToParent.end()) {
				continue;
			}
			visited.push(neighbour);
			childToParent[neighbour] = top;
		}
	}

	if (childToParent.find(b) != childToParent.end()) {
		path.push_front(b);
		while (path.front() != a) {
			path.push_front(childToParent[path.front()]);
		}
	}
	return path;
}

}

int shortestPathMain()
{
	typedef shortestPath::Node Node;
	bool pass = true;

	/* 0 -----> 1
	 * ^        |
	 * |\       |
	 * | -> 2   |
	 * |/       v
	 * 3 <----- 4
	 * */

	Node *nodes[5];
	for (int i = 0; i < 5; ++i)
	{
		nodes[i] = new Node();
		nodes[i]->value = i;
	}

	nodes[0]->neighbours.push_back(nodes[1]);
	nodes[1]->neighbours.push_back(nodes[4]);
	nodes[4]->neighbours.push_back(nodes[3]);
	nodes[3]->neighbours.push_back(nodes[0]);
	nodes[3]->neighbours.push_back(nodes[2]);

	auto path = shortestPath::shortestPath(nodes[1], nodes[2]);
    for (auto n : path) {
        cout << n->value << " ";
    }
    cout << endl;

	assert(pass &= (vector<Node*>({nodes[1], nodes[4], nodes[3], nodes[2]}) == path));

	cout << "Pass: " << pass << endl;

	return 0;
}
