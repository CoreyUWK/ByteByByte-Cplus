//============================================================================
// Name        : ByteByByte.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Byte-By-Byte Code problems
//============================================================================

#include "permutations.h"
#include "NStack.h"
#include "palidrome.h"
#include "rotateBits.h"
#include "threeSum.h"
#include "zeroSumSubArray.h"
#include "pairSum.h"
#include "mergeArrays.h"
#include "binaryTree.h"
#include "greyNumber.h"
#include "stackFromQueues.h"
#include "longestCommonSubString.h"
#include "printReversedLinkedList.h"
#include "sortStack.h"
#include "lineIntersect.h"
#include "treeToLinkedList.h"
#include "clockAngle.h"
#include "matrixSearch.h"
#include "noTmpSwap.h"
#include "reverseStackNoExtraDataStructs.h"
#include "stringToWord.h"
#include "dedupLinkedList.h"
#include "mergeSort.h"
#include "mergeKSortedArrays.h"
#include "bigIntModulus.h"
#include "randomLinkedList.h"
#include "fizzBuzz.h"
#include "squareSubmatrix.h"
#include "shortestPath.h"
#include "twoMissingNumbers.h"
#include "randomBinaryTree.h"
#include "zeroMatrix.h"
#include "consecutiveArray.h"
#include "buildOrder.h"
#include "linkedListCycle.h"
#include "autoComplete.h"
#include "integerToRomanNumeral.h"
#include "findAllDuplicates.h"
#include "knapsack.h"
#include "fibonacci.h"
#include "priorityQueue.h"
#include "medianOfArrays.h"
#include "nthToLastLinkedList.h"
#include "smallestChange.h"
#include "numberOfOnesInBinary.h"
#include "maxStack.h"
#include "anagrams.h"
#include "stringCompression.h"
#include "kthMostFrequentString.h"
#include "splitLinkedList.h"
#include "reverseLinkedList.h"
#include "targetSum.h"
#include "histogramLargestRectangle.h"
#include "nQueen.h"

#include <iostream>
#include <memory>
#include <queue>
#include <cstring>
#include <cassert>
#include <chrono>
#include <algorithm>
#include <array>
#include <forward_list>
#include <stack>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using namespace std::chrono;


int main()
{
	try
	{
		cout << "fizzBuzzMain() ->" << endl;
		fizzBuzzMain();

		cout << "NStackMain() ->" << endl;
		NStackMain();

		cout << endl << "permutationsMain() ->" << endl;
		permutationsMain();

		cout << endl << "palidromeMain() ->" << endl;
		palidromeMain();

		cout << endl << "rotateBitesMain() ->" << endl;
		rotateBitesMain();

		cout << endl << "threeSumMain() ->" << endl;
		threeSumMain();

		cout << endl << "zeroSumSubArrayMain() ->" << endl;
		zeroSumSubArrayMain();

		cout << endl << "pairSumMain() ->" << endl;
		pairSumMain();

		cout << endl << "mergeArraysMain() ->" << endl;
		mergeArraysMain();

		cout << endl << "binaryTreeMain() ->" << endl;
		binaryTreeMain();

		cout << endl << "greyNumberMain() ->" << endl;
		greyNumberMain();

		cout << endl << "stackFromQueuesMain() ->" << endl;
		stackFromQueuesMain();

		cout << endl << "longestCommonSubStringMain() ->" << endl;
		longestCommonSubStringMain();

		cout << endl << "printReversedLinkedListMain() ->" << endl;
		printReversedLinkedListMain();

		cout << endl << "sortStackMain() ->" << endl;
		sortStackMain();

		cout << endl << "lineIntersectMain() ->" << endl;
		lineIntersectMain();

		cout << endl << "treeToLinkedListMain() ->" << endl;
		treeToLinkedListMain();

		cout << endl << "clockAngleMain() ->" << endl;
		clockAngleMain();

		cout << endl << "matrixSearchMain() ->" << endl;
		matrixSearchMain();

		cout << endl << "noTmpSwapMain() ->" << endl;
		noTmpSwapMain();

		cout << endl << "reverseStackNoExtraDataStructsMain() ->" << endl;
		reverseStackNoExtraDataStructsMain();

		cout << endl << "stringToWordMain() ->" << endl;
		stringToWordMain();

		cout << endl << "dedupLinkedListMain() ->" << endl;
		dedupLinkedListMain();

		cout << endl << "mergeSortMain() ->" << endl;
		mergeSortMain();

		cout << endl << "mergeKSortArraysMain() ->" << endl;
		mergeKSortArraysMain();

		cout << endl << "bigIntModuluMain() ->" << endl;
		bigIntModulusMain();

		cout << endl << "randomLinkedListMain() ->" << endl;
		randomLinkedListMain();

		cout << endl << "squareSubmatrixMain() ->" << endl;
		squareSubmatrixMain();

		cout << endl << "shortestPathMain() ->" << endl;
		shortestPathMain();

		cout << endl << "twoMissingNumbersMain() ->" << endl;
		twoMissingNumbersMain();

		cout << endl << "randomBinaryTreeMain() ->" << endl;
		randomBinaryTreeMain();

		cout << endl << "zeroMatrixMain() ->" << endl;
		zeroMatrixMain();

		cout << endl << "consecutiveArrayMain() ->" << endl;
		consecutiveArrayMain();

		cout << endl << "buildOrderMain() ->" << endl;
		buildOrderMain();

		cout << endl << "linkedListCycleMain" << endl;
		linkedListCycleMain();

		cout << endl << "autoCompleteMain" << endl;
		autoCompleteMain();

		cout << endl << "integerToRomanNumeralMain" << endl;
		integerToRomanNumeralMain();

		cout << endl << "findAllDuplicatesMain" << endl;
		findAllDuplicatesMain();

		cout << endl << "knapsackMain" << endl;
		knapsackMain();

		cout << endl << "fibonacciMain" << endl;
		fibonacciMain();

		cout << endl << "priorityQueueMain" << endl;
		priorityQueueMain();

		cout << endl << "medianOfArraysMain" << endl;
		medianOfArraysMain();

		cout << endl << "nthToLastLinkedListMain" << endl;
		nthToLastLinkedListMain();

		cout << endl << "smallestChangeMain" << endl;
		smallestChangeMain();

		cout << endl << "numberOfOnesInBinaryMain" << endl;
		numberOfOnesInBinaryMain();

		cout << endl << "maxStackMain" << endl;
		maxStackMain();

		cout << endl << "anagramsMain" << endl;
		anagramsMain();

		cout << endl << "stringCompressionMain" << endl;
		stringCompressionMain();

		cout << endl << "kthMostFrequentStringMain" << endl;
		kthMostFrequentStringMain();

		cout << endl << "splitLinkedListMain" << endl;
		splitLinkedListMain();

		cout << endl << "reverseLinkedListMain" << endl;
		reverseLinkedListMain();

		cout << endl << "targetSumMain" << endl;
		targetSumMain();

		cout << endl << "histogramLargestRectangleMain" << endl;
		histogramLargestRectangleMain();

		cout << endl << "nQueenMain" << endl;
		nQueenMain();
	}
	catch (const exception &e)
	{
		cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}
