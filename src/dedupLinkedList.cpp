/*
 * dedupLinkedList.cpp
 *
 *  Created on: 2019-08-27
 *      Author: ckirsch
 */
#include "dedupLinkedList.h"
#include <iostream>
#include <cassert>
#include <forward_list>
#include <unordered_set>
#include <algorithm>
using namespace std;

/* Given an unsorted linked list, write a function to remove all duplicates.
1) Track nodes with set, and if see duplicate remove O(n)
2) brute force O(n^2) */

void dedupLinkedListRemoveDuplicate2(forward_list<int> &dedupList)
{
	if (dedupList.empty())
	{
		return;
	}

	auto itr = dedupList.begin();
	while (itr != dedupList.end())
	{
		auto itrFind = next(itr);
		auto itrFindPrev = itr;

		while (itrFind != dedupList.end())
		{
			if (*itr == *itrFind)
			{
				itrFind = next(itrFind);
				dedupList.erase_after(itrFindPrev);
			}
			else
			{
				itrFindPrev = itrFind;
				itrFind = next(itrFind);
			}
		}

		itr = next(itr);
	}
}


void dedupLinkedListRemoveDuplicate1(forward_list<int> &dedupList)
{
	if (dedupList.empty())
	{
		return;
	}

	unordered_set<int> hash;

	auto itr = dedupList.begin();
	auto itrPrev = itr;

	while (itr != dedupList.end())
	{
		if (hash.find(*itr) == hash.end())
		{
			hash.insert(*itr);

			itrPrev = itr;
			itr = next(itr);
		}
		else
		{
			itr = next(itr);
			dedupList.erase_after(itrPrev);
		}
	}
}


void dedupLinkedListTest(void (*dedupLinkedListRemoveDuplicateFunc)(forward_list<int> &))
{
	forward_list<int> dedupList = {1, 2, 3, 2, 1};
	dedupLinkedListRemoveDuplicateFunc(dedupList);
	for (const auto &node : dedupList)
	{
		cout << node << " ";
	}
	cout << endl;
}



int dedupLinkedListMain()
{
	dedupLinkedListTest(dedupLinkedListRemoveDuplicate1);
	dedupLinkedListTest(dedupLinkedListRemoveDuplicate2);

	return 0;
}
