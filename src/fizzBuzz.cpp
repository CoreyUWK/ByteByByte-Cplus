/*
 * fizzBuzz.cpp
 *
 *  Created on: 2019-08-29
 *      Author: ckirsch
 */
#include "fizzBuzz.h"
#include <iostream>

using namespace std;

void fizzBuzz(int x)
{
	for (int i = 1; i <= x; ++i)
	{
		bool fizz = (i % 3) == 0;
		bool buzz = (i % 5) == 0;

		if (fizz && buzz)
		{
			cout << "FizzBuzz" << endl;
		}
		else if (fizz)
		{
			cout << "Fizz" << endl;
		}
		else if (buzz)
		{
			cout << "Buzz" << endl;
		}
		else
		{
			cout << i << endl;
		}
	}
}

int fizzBuzzMain()
{
	fizzBuzz(20);

	return 0;
}



