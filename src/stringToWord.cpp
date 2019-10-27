/*
 * stringToWord.cpp
 *
 *  Created on: 2019-08-26
 *      Author: ckirsch
 */
#include "stringToWord.h"
#include <iostream>
#include <cassert>
#include <unordered_set>
#include <queue>
#include <unordered_map>
using namespace std;

/* Given a string and a dictionary HashSet, write a function to determine the minimum number of
 * characters to delete to make a word. */


// 1) go through all substrings of query O(n!) and check if it exists as a word in dictionary, if it does
// take size difference and update minDiff
// - Recursion for substrings, but this will not do breadth first search but depth
// - or queue for substrings will do breadth first search and so first found match will be the best answer and can stop search
// 2) (Does Not Work cause of hash losses order) Turn query into hash map O(n), for each dictionary item O(m) go through it's characters (limited
// by length of query) O(n) and check if characters exist in query, if so then get how many the same and
// update minDiff with difference count
int stringToWord1(string query, const unordered_set<string> &dictionary)
{
	queue<string> bfsQueue;

	// Extra: To ensure no duplicates in bfsQueue, this will only help with performance if no substring of
	// query is in dictionary as this will reduce number of entries in bfsQueue on lowest level (leafs)
	// Also, increases memory space, but only needs to contain none processed entries as going from
	// big to small substrings and once substring processed will not insert another of that size into bfs
	// queue
	unordered_set<string> duplicateHash;

	// Loop through breadth first search of query substrings
	bfsQueue.push(query);
	duplicateHash.insert(query);
	while (!bfsQueue.empty())
	{
		string top = bfsQueue.front();
		bfsQueue.pop();
		duplicateHash.erase(top);

		// Check if found
		if (dictionary.find(top) != dictionary.end())
		{
			return query.size() - top.size();
		}

		// go through substrings (-1 element)
		for (uint i = 0; i < top.size(); ++i)
		{
			string subString = top.substr(0, i) + top.substr(i + 1, top.size() - (i + 1));
			if (duplicateHash.find(subString) == duplicateHash.end())
			{
				bfsQueue.push(subString);
				duplicateHash.insert(subString);
			}
		}
	}

	return -1;
}


// Doesn't work as hash doesn't take order into account
int stringToWord2(string query, const unordered_set<string> &dictionary)
{
	int minDiff = -1;

	// Iterate over dictionary strings to see if any contained in query
	for (auto itr = dictionary.begin(); itr != dictionary.end(); ++itr)
	{
		string dictString{*itr};

		// Skip entries larger than query
		if (dictString.size() > query.size())
		{
			continue;
		}

		// Set up Hash Map of query - try to move out
		unordered_map<char, int> map;
		for (char c : query)
		{
			++map[c];
		}

		// Loop through dictionary string to see if substring of query
		int diffCount = query.size();
		bool process = true;
		for (const char &c : *itr)
		{
			// if query string does not contain dictionary string character than go to next dictionary string
			if (map.find(c) == map.end())
			{
				process = false;
				break;
			}
			else
			{
				--map[c];
				if (map[c] == 0)
				{
					map.erase(c);
				}
				--diffCount;
			}
		}

		if (process && (minDiff == -1 || minDiff > diffCount))
		{
			minDiff = diffCount;
		}
	}

	return minDiff;
}


int stringToWordMain()
{
	bool pass = true;

	// 1
	string query = "abc";
	unordered_set<string> dictionary = {"a", "aa", "aaa"};

	assert(pass &= (2 == stringToWord1(query, dictionary)));
	assert(pass &= (2 == stringToWord2(query, dictionary)));

	// 2
	string query2 = "abc";
	unordered_set<string> dictionary2 = {"adfe", "asb", "lbpo"};

	assert(pass &= (-1 == stringToWord1(query2, dictionary2)));
	assert(pass &= (-1 == stringToWord2(query2, dictionary2)));

	// 2
	string query3 = "abcdefg";
	unordered_set<string> dictionary3 = {"adfe", "asb", "lbpo", "adg"};

	assert(pass &= (4 == stringToWord1(query3, dictionary3)));
	assert(pass &= (4 != stringToWord2(query3, dictionary3))); // Issue with this implementation casue of hash

	cout << "Pass: " << pass << endl;

	return 0;
}
