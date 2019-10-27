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
using namespace std;


namespace shortestPath
{
struct Node
{
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
	}

	nodes[0]->neighbours.push_back(nodes[1]);
	nodes[1]->neighbours.push_back(nodes[4]);
	nodes[4]->neighbours.push_back(nodes[3]);
	nodes[3]->neighbours.insert(nodes[3]->neighbours.end(), {nodes[2], nodes[0]});
	nodes[2]->neighbours.push_back(nodes[0]);

	auto path = shortestPath::shortestPath(nodes[1], nodes[2]);

	assert(pass &= (vector<Node*>({nodes[1], nodes[4], nodes[3], nodes[2]}) == path));

	cout << "Pass: " << pass << endl;

	return 0;
}
