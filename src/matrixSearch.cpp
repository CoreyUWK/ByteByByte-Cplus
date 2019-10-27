/*
 * matrixSearch.cpp
 *
 *  Created on: 2019-08-26
 *      Author: ckirsch
 */
#include "matrixSearch.h"
#include <iostream>
#include <cassert>

using namespace std;


/* Could do with binary search -> O(MlogN)
 * This solution is O(M + N) since this search can only move in one direction through matrix
 * that is each time either a row or column is removed from search so if you start from top right
 * and move to bottom left of matrix it takes M + N - 1 at most. */
template <int M, int N>
bool matrixSearch(int matrix[N][M], int x)
{
	if (N == 0 || M == 0) return false;

	int row = 0;
	int col = M - 1;

	while (row < N && col >= 0)
	{
		if (matrix[row][col] == x)
		{
			return true;
		}
		else if (matrix[row][col] > x)
		{
			--col;
		}
		else
		{
			++row;
		}
	}

	return false;
}


int matrixSearchMain()
{
	bool pass = true;

	int matrix1[4][4] = {
			{0, 1, 6, 12},
			{3, 4, 7, 13},
			{5, 8, 9, 17},
			{10, 15, 19, 20}
	};

	// Check if all elements can be found
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			assert(pass &= (matrixSearch<4,4>(matrix1, matrix1[i][j])));
		}
	}

	// Check none exists elements can not be found
	assert(pass &= (false == matrixSearch<4,4>(matrix1, 2)));

	cout << "Pass: " << pass << endl;

	return 0;
}

