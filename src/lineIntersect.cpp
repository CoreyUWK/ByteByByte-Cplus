/*
 * lineIntersect.cpp
 *
 *  Created on: 2019-08-24
 *      Author: ckirsch
 */
#include "lineIntersect.h"
#include <cassert>
#include <iostream>

using namespace std;


int lineIntersectMain()
{
	bool pass = true;

	Line line1(0, 1);
	Line line2(1, 1);
	assert(pass &= line1.intersect(line2));

	Line line3(0, 1);
	Line line4(0, 1);
	assert(pass &= line3.intersect(line4));

	Line line5(0, 1);
	Line line6(0, 2);
	assert(pass &= (false == line5.intersect(line6)));

	cout << "Pass: " << pass << endl;

	return 0;
}

