/*
 * buildOrder.cpp
 *
 *  Created on: 2019-08-31
 *      Author: ckirsch
 */
#include "buildOrder.h"
#include <iostream>
#include <cassert>
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/* Given a list of packages and their dependencies to be built, determine valid build order
 * Q:
 * - How input format will look
 * - will there be cycles
 * - will there be decencies to none existing packages
 * - will the input list be sorted by build order */


/* For every package O(n) have to go over each depency O(m), and need to do this over again for each package O(n)
 * Time: O(n^2 * m) but sam say's O(n!)? */
vector<int> buildOrder_bruteForce(const vector<vector<int>> &dependencyList)
{
	vector<int> buildOrder;
	unordered_set<int> builtPackages;

	bool toProcess = true;
	while (toProcess && builtPackages.size() < dependencyList.size())
	{
		toProcess = false;

		// Loop through packages
		for (uint packageIdx = 0; packageIdx < dependencyList.size(); ++packageIdx)
		{
			if (builtPackages.find(packageIdx) != builtPackages.end())
			{
				continue;
			}

			bool allDepenciesBuilt = true;

			// Loop through package dependices
			for (uint depencies = 0; depencies < dependencyList[packageIdx].size(); ++depencies)
			{
				// Check if all package depencies have been built, so package can now be built
				if (builtPackages.find(dependencyList[packageIdx][depencies]) == builtPackages.end())
				{
					allDepenciesBuilt = false;
					break;
				}
			}

			// If all depencies have been built, build package
			if (allDepenciesBuilt)
			{
				buildOrder.push_back(packageIdx);
				builtPackages.insert(packageIdx);

				toProcess = true;
			}
		}
	}

	return buildOrder;
}


/* Go through dependency list O(n) n times => O(n*n) = O(n^2)  */
vector<int> buildOrder_Quadrdic(const vector<vector<int>> &dependencyList)
{
	vector<int> buildOrder;
	unordered_set<int> builtPackages;

	// Loop through packages
	for (uint packageIdx = 0; packageIdx < dependencyList.size(); ++packageIdx)
	{
		// Find first packages with no dependicies
		if (dependencyList[packageIdx].size() == 0)
		{
			buildOrder.push_back(packageIdx);
			builtPackages.insert(packageIdx);
		}
	}

	bool toProcess = true;
	while (toProcess && builtPackages.size() < dependencyList.size())
	{
		toProcess = false;

		// Loop through packages
		for (uint packageIdx = 0; packageIdx < dependencyList.size(); ++packageIdx)
		{
			if (builtPackages.find(packageIdx) != builtPackages.end())
			{
				continue;
			}

			bool allDepenciesBuilt = true;

			// Loop through package dependices
			for (uint depencies = 0; depencies < dependencyList[packageIdx].size(); ++depencies)
			{
				// Check if all package depencies have been built, so package can now be built
				if (builtPackages.find(dependencyList[packageIdx][depencies]) == builtPackages.end())
				{
					allDepenciesBuilt = false;
					break;
				}
			}

			// If all depencies have been built, build package
			if (allDepenciesBuilt)
			{
				buildOrder.push_back(packageIdx);
				builtPackages.insert(packageIdx);

				toProcess = true;
			}
		}
	}

	return buildOrder;
}


/* Go through dependency list O(n) n times  */
vector<int> buildOrder_Linear(const vector<vector<int>> &dependencyList)
{
	vector<int> buildOrder;
	unordered_set<int> builtPackages;
	unordered_map<int, vector<int>> parentHash; //[idx] (depends) -> {list} lookup
	queue<int> processQueue;

	// Setup depencies lookup O(n*m)
	for (uint package = 0; package < dependencyList.size(); ++package)
	{
		for (uint depencies = 0; depencies < dependencyList[package].size(); ++depencies)
		{
			parentHash[dependencyList[package][depencies]].push_back(package);
		}
	}

	// Add packages without any dependies O(n)
	for (uint package = 0; package < dependencyList.size(); ++package)
	{
		if (dependencyList[package].empty())
		{
			processQueue.push(package);
		}
	}

	// Check if not found start
	if (processQueue.empty())
	{
		return buildOrder;
	}

	// Process queue'd packages O(n)
	while (!processQueue.empty())
	{
		int top = processQueue.front();
		processQueue.pop();

		// Update output build order
		buildOrder.push_back(top);
		builtPackages.insert(top);

		// Check all pakages that depend on top are can be processed (have no other depending
		// packages that have not been processed)
		for (auto parentPackage : parentHash[top])
		{
			// skip if package already processed, though think is impossible cause were checking future packages
			if (builtPackages.find(parentPackage) != builtPackages.end())
			{
				continue;
			}

			bool allProcessed = true;

			// Check all dependies of parent package have been processed
			for (uint depencies = 0; depencies < dependencyList[parentPackage].size(); ++depencies)
			{
				// Check if not processed
				if (builtPackages.find(dependencyList[parentPackage][depencies]) == builtPackages.end())
				{
					allProcessed = false;
					break;
				}
			}

			if (allProcessed)
			{
				processQueue.push(parentPackage);
			}
		}
	}

	return buildOrder;
}


void buildOrder_TopologicalDFS_Visit(int node, const vector<vector<int>> &dependencyList,
		unordered_set<int> &tmpMarks,
		unordered_set<int> &permMarks,
		vector<int> &output)
{
	// Check if already visited node
	if (permMarks.end() != permMarks.find(node))
	{
		return;
	}

	tmpMarks.insert(node);

	auto children = dependencyList[node];
	for (int child : children)
	{
		buildOrder_TopologicalDFS_Visit(child, dependencyList, tmpMarks, permMarks, output);
	}

	output.push_back(node);
	permMarks.insert(node);
	tmpMarks.erase(node);
}

/* Go through dependency list O(n) n times  */
vector<int> buildOrder_TopologicalDFS(const vector<vector<int>> &dependencyList)
{
	unordered_set<int> tmpMarks;
	unordered_set<int> permMarks;
	vector<int> output;

	// Could set up a parent hash like before to reduce number of checks of already processed nodes
	// by starting at highest dependent nodes
	// Or just calculate most dependent nodes

	// Loop over all nodes and perfrom DFS
	for (uint i = 0; i < dependencyList.size(); ++i)
	{
		// Only visit a node once
		// Visit node -> recursive
		buildOrder_TopologicalDFS_Visit(i, dependencyList, tmpMarks, permMarks, output);
	}

	return output;
}


int buildOrderMain()
{
	bool pass = true;

	// 1
	/*  In graph dependent package points to dependent (confusing)
	 *      1 <-
	 *     /    \
	 * 0 <-      <-3 <-4
	 *     \    /
	 *      2 <-
	 * */
	vector<vector<int>> dependencyList = {
			{},
			{0},
			{0},
			{1,2},
			{3}
	};
	assert(pass &= (vector<int>{0, 1, 2, 3, 4} == buildOrder_bruteForce(dependencyList)));
	assert(pass &= (vector<int>{0, 1, 2, 3, 4} == buildOrder_Quadrdic(dependencyList)));
	assert(pass &= (vector<int>{0, 1, 2, 3, 4} == buildOrder_Linear(dependencyList)));
	assert(pass &= (vector<int>{0, 1, 2, 3, 4} == buildOrder_TopologicalDFS(dependencyList)));

	// 2
	dependencyList = {
				{1},
				{2,3},
				{4},
				{4},
				{}
		};
	assert(pass &= (vector<int>{4,2,3,1,0} == buildOrder_bruteForce(dependencyList)));
	assert(pass &= (vector<int>{4,2,3,1,0} == buildOrder_Quadrdic(dependencyList)));
	assert(pass &= (vector<int>{4,2,3,1,0} == buildOrder_Linear(dependencyList)));
	assert(pass &= (vector<int>{4,2,3,1,0} == buildOrder_TopologicalDFS(dependencyList)));

	// 3
	dependencyList = {
				{1},
				{3},
				{4},
				{},
				{3,5},
				{},
				{0,2},
				{2,5}
		};
	assert(pass &= (vector<int>{3,5,1,4,0,2,6,7} == buildOrder_bruteForce(dependencyList)));
	assert(pass &= (vector<int>{3,5,1,4,0,2,6,7} == buildOrder_Quadrdic(dependencyList)));
	assert(pass &= (vector<int>{3,5,1,4,0,2,6,7} == buildOrder_Linear(dependencyList)));
	assert(pass &= (vector<int>{3,1,0,5,4,2,6,7} == buildOrder_TopologicalDFS(dependencyList)));

	cout << "Pass: " << pass << endl;

	return 0;
}
