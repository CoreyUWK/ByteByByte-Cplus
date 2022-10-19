/*
 * zeroMatrix.cpp
 *
 *  Created on: 2019-08-30
 *      Author: ckirsch
 */
#include "zeroMatrix.h"
#include <iostream>
#include <cassert>

using namespace std;

/* Given bool matrix, update it so that if any cell is true make rest of row and column true */

/* 1) Brute force method O(n^2), will need to make a new temporary matrix so that
 *  a set true doesn't get mistaken as an actual true
 * 2) Rows[3] Cols[3] to track if a row or col should be set to true
 * Hence, pre-process in O(n), then set in O(n), but extra space
 * 3)  */
template<int rows, int cols>
void zeroMatrix(bool matrix[rows][cols])
{
	bool rowZero = false;
	bool colZero = false;

	// 1) Find if first row and column should be set to true O(max(row, col))
	for (int col = 0; col < cols; ++col)
	{
		if (matrix[0][col])
		{
			rowZero = true;
			break;
		}
	}

	for (int row = 0; row < rows; ++row)
	{
		if (matrix[row][0])
		{
			colZero = true;
			break;
		}
	}

	// 2) Since we now processing the first row and column can modify it
	// go through inner matrix and if true update first row and column O((n-1)(m-1))
	for (int row = 1; row < rows; ++row)
	{
		for (int col = 1; col < cols; ++col)
		{
			if (matrix[row][col])
			{
				matrix[0][col] = true;
				matrix[row][0] = true;
			}
		}
	}

	// 3) Process the results of 2) in row zero by pushing the true down the inner
	for (int col = 1; col < cols; ++col)
	{
		if (matrix[0][col])
		{
			for (int row = 1; row < rows; ++row)
			{
				matrix[row][col] = true;
			}
		}
	}

	// Process the results of 2) in column zero by pushing the true down the inner
	for (int row = 1; row < rows; ++row)
	{
		if (matrix[0][row])
		{
			for (int col = 1; col < cols; ++col)
			{
				matrix[row][col] = true;
			}
		}
	}

	// 4) Process 1) finding of if the first row and column should be all true
	if (colZero)
	{
		for (int col = 0; col < cols; ++col)
		{
			matrix[0][col] = true;
		}
	}
	if (rowZero)
	{
		for (int row = 0; row < rows; ++row)
		{
			matrix[row][0] = true;
		}
	}
}


template<int rows, int cols>
void zeroMatrixPrint(bool matrix[rows][cols])
{
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			cout << matrix[row][col] << " ";
		}
		cout << endl;
	}
}


template<int rows, int cols>
void zeroMatrixTest(bool matrix[rows][cols])
{
	static int numCalls = 1;

	cout << "Matrix " << numCalls++ << endl;

	zeroMatrixPrint<rows,cols>(matrix);

	zeroMatrix<rows,cols>(matrix);

	cout << endl;
	zeroMatrixPrint<rows,cols>(matrix);
}


int zeroMatrixMain()
{
	// 1
	bool matrix1[3][3] =
	{
			{true, false, false},
			{false, false, false},
			{false, false, false}
	};

	// 2
	bool matrix2[3][3] =
	{
			{false, false, true},
			{false, true, false},
			{false, false, true}
	};

	// 3
	bool matrix3[3][3] =
	{
			{false, false, false},
			{false, true, false},
			{false, false, true}
	};

	zeroMatrixTest<3,3>(matrix1);
	zeroMatrixTest<3,3>(matrix2);
	zeroMatrixTest<3,3>(matrix3);

	return 0;
}

