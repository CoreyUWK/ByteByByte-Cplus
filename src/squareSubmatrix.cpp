/*
 * squareSubmatrix.cpp
 *
 *  Created on: 2019-08-29
 *      Author: ckirsch
 */
#include "squareSubmatrix.h"
#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

/* Given 2D array of 1s and 0s, find largest square sub-array of all 1's and returns size nxn */

template<int rows, int cols>
void squareSubmatrixPrint(int matrix[rows][cols])
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


// O(rows * cols)
template <int rows, int cols>
int squareSubmatrixBruteForce(int matrix[rows][cols])
{
	int maxSize = 1;
	for (int row = 0; row + maxSize < rows; ++row) // +maxSize to skip if not enough to check square
	{
		for (int col = 0; col + maxSize < cols; ++col) // +maxSize to skip if not enough to check square
		{
			if (matrix[row][col]) // Check first index
			{
				int size = 2; // Needs to start from 2 always to make sure internal square is valid
				bool isSquare = true;
				while (isSquare)
				{
					// Only check right column and bottom row up to and not including index in right
					// column since internal indexes of square were already validated

					// Check right column
					for (int i = row; isSquare && i < row + size; ++i)
					{
						if (!matrix[i][col + size - 1])
						{
							isSquare = false;

							// Skip already tested index's
							if (i == row)
							{
								col += (size - 1); // -1 cause of loop ++col
							}
							break;
						}
					}

					// Check bottom row
					for (int i = col; isSquare && i < col + size - 1; ++i)
					{
						if (!matrix[row + size - 1][i])
						{
							isSquare = false;
							break;
						}
					}

					if (isSquare && maxSize < size)
					{
						maxSize = size;
					}

					++size;
				}
			}
		}
	}

	return maxSize;
}


/* Overloaded recursive function - find max square by finding min path of true */
template <int rows, int cols>
int squareSubmatrixBruteForce_Recursive(int matrix[rows][cols], int row, int col)
{
	// Base case at bottom or right of the matrix - at end
	if (row == rows || col == cols)
	{
		return 0;
	}

	// If the cell is false then it's not part of a valid submatrix
	if (!matrix[row][col])
	{
		return 0;
	}

	// Find the size of the right, bottom, and bottom right submatrices and add 1 to the minimum of
	// result
	return 1 + min({
		squareSubmatrixBruteForce_Recursive<rows,cols>(matrix, row + 1, col),
		squareSubmatrixBruteForce_Recursive<rows,cols>(matrix, row + 1, col + 1),
		squareSubmatrixBruteForce_Recursive<rows,cols>(matrix, row, col + 1),
	});
}


/* Main loop is O(rows * cols * ?)
 * the helper function is a recursive function that creates three branches on each path and the longest
 * path is row + col, so the hight of the recursive tree is O(rows + cols)
 * Hence, at each level the number of nodes gets multiplied by 3 => 3 * 3 * 3 ... = 3^(depth of recursion = rows + cols)
 *
 * Time: O((rows * cols) * 3^(rows + cols)
 * Space: Recursive stack = O(rows + cols) will exist at once*/
template <int rows, int cols>
int squareSubmatrixBruteForce_Recursive(int matrix[rows][cols])
{
	int maxSquare = 0;
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			if (matrix[row][col])
			{
				maxSquare = max(maxSquare,
						squareSubmatrixBruteForce_Recursive<rows,cols>(matrix, row, col));
			}
		}
	}

	return maxSquare;
}


/* Overloaded recursive function - find max square by finding min path of true */
template <int rows, int cols>
int squareSubmatrixBruteForce_RecursiveMemoization(int matrix[rows][cols], int cache[rows][cols],
		int row, int col)
{
	// Base case at bottom or right of the matrix - at end
	if (row == rows || col == cols)
	{
		return 0;
	}

	// If the cell is false then it's not part of a valid submatrix
	if (!matrix[row][col])
	{
		return 0;
	}

	// Check cache
	// if 0 then have not computed cache value yet, else return cache value
	if (cache[row][col])
	{
		return cache[row][col];
	}

	// Find the size of the right, bottom, and bottom right submatrices and add 1 to the minimum of
	// result
	cache[row][col] = 1 + min({
		squareSubmatrixBruteForce_Recursive<rows,cols>(matrix, row + 1, col),
		squareSubmatrixBruteForce_Recursive<rows,cols>(matrix, row + 1, col + 1),
		squareSubmatrixBruteForce_Recursive<rows,cols>(matrix, row, col + 1),
	});

	return cache[row][col];
}


/* Top-down dynamic programming
 * Cache values to avoid repeating computations
 *
 * Time: O(rows * cols * ?)
 * Since cache will allow to only compute each value once, and visit each node in constant time (for cache)
 * = O(rows * cols)
 * Space: cache + recursion = O(rows * cols + (rows + cols))
 * = O(rows * cols) */
template <int rows, int cols>
int squareSubmatrixBruteForce_RecursiveMemoization(int matrix[rows][cols])
{
	int maxSquare = 0;

	/* Cache does not need to be initialized to -1.
	 * Zero will represent not computed. */
	int cache[rows][cols] = {{0}};

	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			if (matrix[row][col])
			{
				maxSquare = max(maxSquare,
						squareSubmatrixBruteForce_Recursive<rows,cols>(matrix, row, col));
			}
		}
	}

	return maxSquare;
}


/* Using the squareSubmatrixBruteForce_RecursiveMemoization() top-down solution to flip and make DP tabular solution
 * The top-down each index represented the upper-left-hand-corner of square
 * Recursion recurses to end before working it's way up, it traverses the array backwards, and
 * starts solving subproblems with bottom-right-hand-corner if the square
 *
 * So to change from recursion to iterative will make each index = bottom-right-corner of square
 *
 * Time: O(rows * cols)
 * Space: O(rows * cols) or O(1) if using the original matrix passed in */
template<int rows, int cols>
int squareSubmatrix_DPTabular(int matrix[rows][cols])
{
	int size = 0;
	if (rows == 0 || cols == 0)
	{
		return size;
	}

	// First process matrix in O(n) by comparing current matrix value with the remaining in current
	// 2x2 square, where current matrix values makes the bottom right 2x2 entry
	for (int row = 1; row < rows; ++row)
	{
		for (int col = 1; col < cols; ++col)
		{
			if (0 == matrix[row][col])
			{
				continue;
			}

			matrix[row][col] = std::min({matrix[row-1][col-1], matrix[row-1][col], matrix[row][col-1]}) + 1;

			if (size < matrix[row][col])
			{
				size = matrix[row][col];
			}
		}
	}

	return size;
}


/* This is same as above DP method
Runs in O(row*col)
1) was thinking of a method that tracked rowZeros[] colZeros[] or counting values by rows and cols for continous 1s and if 0 then 
restarts count. However, this DP method is similar to this idea by counting at [row][col] by taking 1+min of neighbours assuming 
[row][col] is most bottom right corner of a possible 1s square. */
int squareSubmatrix(vector<vector<int>> matrix) {
    for (int row = 1; row < matrix.size(); ++row) {
        for (int col = 1; col < matrix[0].size(); ++col) {
            if (matrix[row][col] == 0) continue;
            
            int min = matrix.size();
            for (int i = row - 1; i <= row; ++i) {
                for (int j = col - 1; j <= col; ++j) {
                    if (i == row && j == col) break;
                    if (matrix[i][j] < min) {
                        min = matrix[i][j];
                    }
                }
            }
            
            matrix[row][col] += min;
        }
    }
    
    int max = 0;
    for (int row = 0; row < matrix.size(); ++row) {
        for (int col = 0; col < matrix[0].size(); ++col) {
            if (matrix[row][col] > max) {
                max = matrix[row][col];
            }
        }
    }  
    return max;
}


int squareSubmatrixMain()
{
	bool pass = true;

	int matrix[7][6] = {
			{1, 0, 1, 1, 1, 0},
			{1, 1, 0, 1, 1, 1},
			{1, 1, 1, 1, 1, 0},
			{0, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 0, 1},
			{1, 0, 1, 0, 1, 0},
			{0, 0, 0, 0, 0, 0}
	};

	squareSubmatrixPrint<7, 6>(matrix);

	int size = squareSubmatrix_DPTabular<7, 6>(matrix);
	assert(pass &= (3 == size));

	size = squareSubmatrixBruteForce<7,6>(matrix);
	assert(pass &= (3 == size));

	size = squareSubmatrixBruteForce_Recursive<7,6>(matrix);
	assert(pass &= (3 == size));

	size = squareSubmatrixBruteForce_RecursiveMemoization<7,6>(matrix);
	assert(pass &= (3 == size));

	int matrix2[7][6] = {
			{1, 0, 1, 1, 1, 0},
			{1, 1, 0, 1, 1, 1},
			{1, 1, 1, 1, 1, 1},
			{0, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 0, 1},
			{1, 0, 1, 1, 1, 1},
			{0, 0, 0, 0, 0, 0}
	};

	size = squareSubmatrix_DPTabular<7, 6>(matrix2);
	assert(pass &= (3 == size));

	size = squareSubmatrixBruteForce<7,6>(matrix2);
	assert(pass &= (3 == size));

	size = squareSubmatrixBruteForce_Recursive<7,6>(matrix2);
	assert(pass &= (3 == size));

	size = squareSubmatrixBruteForce_RecursiveMemoization<7,6>(matrix2);
	assert(pass &= (3 == size));

	cout << "Pass: " << pass << endl;

	return 0;
}
