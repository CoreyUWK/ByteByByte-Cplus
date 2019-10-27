/*
 * reverseStackNoExtraDataStructs.cpp
 *
 *  Created on: 2019-08-26
 *      Author: ckirsch
 */
#include "reverseStackNoExtraDataStructs.h"
#include <iostream>
#include <cassert>
#include <stack>

using namespace std;


// O(n) as for each element pop and then push back
// Space: O(n) since calling recursively for each n items
void reverseStackNoExtraDataStructsPushDown(stack<int> &st, int item)
{
	if (st.empty())
	{
		st.push(item);
	}
	else
	{
		int top = st.top();
		st.pop();
		reverseStackNoExtraDataStructsPushDown(st, item);
		st.push(top);
	}
}


// O(n^2) as for each element we pop and then call reverseStackNoExtraDataStructsPushDown (O(n))
// This first empties stack and pushes elements bottom-up back to the bottom of the stack
// ex. [1, 2, 3, 4] =>
// [] + 4
// [4] + 3 = [4, 3]
// [4, 3] + 2 = [4, 3, 2]
// [4, 3, 2] + 1 = [4, 3, 2, 1]
// Space: O(n + n) = O(n) as this calls recursively for each n items and then calls
// reverseStackNoExtraDataStructsPushDown() which using O(n) space which gets cleared after call
void reverseStackNoExtraDataStructs(stack<int> &st)
{
	if (st.empty())
	{
		return;
	}
	else
	{
		int top = st.top();
		st.pop();
		reverseStackNoExtraDataStructs(st);
		reverseStackNoExtraDataStructsPushDown(st, top);
	}
}


int reverseStackNoExtraDataStructsMain()
{
	bool pass = true;

	int size = 10;
	stack<int> st;

	// 1
	for (int i = 1; i <= size; ++i)
	{
		st.push(i);
	}
	reverseStackNoExtraDataStructs(st);
	for (int i = 1; i <= size; ++i)
	{
		assert(pass &= (i == st.top()));
		st.pop();
	}
	assert(pass &= (st.empty()));

	cout << "Pass: " << pass << endl;
	return 0;
}
