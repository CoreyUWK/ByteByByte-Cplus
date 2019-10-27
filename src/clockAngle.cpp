/*
 * clockAngle.cpp
 *
 *  Created on: 2019-08-26
 *      Author: ckirsch
 */
#include "clockAngle.h"
#include <iostream>
#include <cassert>

using namespace std;

#define DEGREES_IN_CLOCK (360)
#define HOURS_IN_CLOCK (12)
#define MINUTES_IN_HOURTICK (5)
#define MINUTES_IN_HOUR (60)
#define ANGLE_PER_HOUR (DEGREES_IN_CLOCK / HOURS_IN_CLOCK)
#define ANGLE_PER_MINUTE (ANGLE_PER_HOUR / MINUTES_IN_HOURTICK)
// #define ANGLE_PER_MINUTE (DEGREES_IN_CLOCK / MINUTES_IN_HOUR) same as above but more readable maybe


uint clockAngle(uint hour, uint minute)
{
	uint percentDegreeOfMinuteToHourHand = ((double)minute / MINUTES_IN_HOUR) * ANGLE_PER_HOUR;
	int degreeInHour = (hour * ANGLE_PER_HOUR) + percentDegreeOfMinuteToHourHand;
	int degreeInMinute = minute * ANGLE_PER_MINUTE;

	uint clockAngle = abs(degreeInHour - degreeInMinute);
	return (clockAngle <= (DEGREES_IN_CLOCK / 2.0)) ? clockAngle : DEGREES_IN_CLOCK - clockAngle;
}


int clockAngleMain()
{
	bool pass = true;

	assert(pass &= (85 == clockAngle(11, 10)));

	cout << "Pass: " << pass << endl;

	return 0;
}
