/*
 * lineIntersect.h
 *
 *  Created on: 2019-08-24
 *      Author: ckirsch
 */

#ifndef LINEINTERSECT_H_
#define LINEINTERSECT_H_


class Line
{
	double slope;
	double yIntercept;

public:
	Line(double slope, double yIntercept) : slope(slope), yIntercept(yIntercept) {}

	// If lines intersect when:
	// 	- lines are equal (same always)
	// 	- slopes are not the same so they intersect (m1-m2)x = b2-b1 => if (m1-m2) > 0 intersect at x
	bool intersect(Line line)
	{
		if (*this == line) return true;
		if (this->slope != line.slope) return true;
		return false;
	}

	bool operator==(const Line &line) const
	{
		if (this == &line)
		{
			return true;
		}

		return (this->slope == line.slope &&
				this->yIntercept == line.yIntercept) ? true : false;
	}
};


int lineIntersectMain();


#endif /* LINEINTERSECT_H_ */
