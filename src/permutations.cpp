#include "permutations.h"
#include <iostream>
#include <memory>
#include <queue>
#include <cstring>
#include <cassert>
#include <chrono>
#include <algorithm>
#include <array>

using namespace std;
using namespace std::chrono;


int factorial(int n)
{
	if (n <= 2)
	{
		return n;
	}

	return n * factorial(n - 1);
}


void permutationsString(string prefix, string suffix, vector<string> &permList)
{
	if (suffix.empty())
	{
		permList.push_back(prefix);
	}
	else
	{
		for (uint i = 0; i < suffix.size(); ++i)
		{
			// not performing string concatenation as need to pass new string
			permutationsString(prefix + suffix[i], // Add index to prefix
					suffix.substr(0, i) + // Take from beginning to index
					suffix.substr(i + 1, suffix.size() - (i + 1)), // Take from after index to end
					permList);
		}
	}
}


vector<string> permutationsString(string s)
{
	vector<string> permList;

	if (s.empty() || s.size() == 1)
	{
		permList.push_back(s);
		return permList;
	}

	permList.reserve(factorial(s.size()));

	permutationsString("", s, permList);
	return permList;
}


vector<string> permutationsStringFast(string s)
{
	vector<string> permList;

	if (s.empty() || s.size() == 1)
	{
		permList.push_back(s);
		return permList;
	}

	permList.reserve(factorial(s.size()));
	sort(s.begin(), s.end());
	do
	{
		permList.push_back(s);
	} while (next_permutation(s.begin(), s.end()));

	return permList;
}


// Could make similar to string permutation function, however would require more flags to track data
// and new arrays would have to be created.
template<int N>
void permutationsInt (array<int, N> &arr, uint start, vector<array<int, N>> &permList)
{
	if (start >= (N - 1))
	{
		permList.push_back(arr);
	}
	else
	{
		for (uint i = start; i < arr.size(); ++i)
		{
			if (i != start) swap(arr[i], arr[start]);
			permutationsInt<N>(arr, start + 1, permList);
			if (i != start) swap(arr[i], arr[start]);
		}
	}
}


template<int N>
vector<array<int,N>> permutationsInt (array<int, N> arr)
{
	vector<array<int, N>> permList;
	permutationsInt<N>(arr, 0, permList);

	return permList;
}


int permutationsMain()
{
	// 1
	auto start = high_resolution_clock::now();
	vector<string> permList = permutationsString("abcdef");
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: "
		 << duration.count() << " microseconds and " << permList.size() << " permutations" << endl;

#ifdef PERMUTATION_DEBUG_PRINT
	for (string &s : permList)
	{
		cout << s << endl;
	}
#endif

	// 2
	permList.empty();
	start = high_resolution_clock::now();
	permList = permutationsStringFast("abcdef");
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
   		 << duration.count() << " microseconds and " << permList.size() << " permutations" << endl;

#ifdef PERMUTATION_DEBUG_PRINT
    for (string &s : permList)
	{
		cout << s << endl;
	}
#endif

    // 3
    const int size = 6;
    vector<array<int, size>> permIntList;
    start = high_resolution_clock::now();
    permIntList = permutationsInt<size>({1,2,3,4,5,6});
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
   		 << duration.count() << " microseconds and " << permIntList.size() << " permutations" << endl;

#ifdef PERMUTATION_DEBUG_PRINT
    for (auto &arr : permIntList)
	{
    	for (auto &i : arr)
    	{
    		cout << i;
    	}
    	cout << endl;
	}
#endif

	return 0;
}
