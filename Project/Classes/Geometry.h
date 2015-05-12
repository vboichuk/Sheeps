//
// Created by v.boichuk on 7/11/14.
//

#ifndef __Geometry_H_
#define __Geometry_H_

#include "cocos2d.h"

class Geometry {
public:
	static bool intersect(
			const cocos2d::CCPoint &p1,
			const cocos2d::CCPoint &p2,
			const cocos2d::CCPoint &t1,
			const cocos2d::CCPoint &t2
		)
		{
		float A1 = p1.y - p2.y;
		float B1 = p2.x - p1.x;
		float C1 = p1.x * p2.y - p2.x * p1.y;

		float A2 = t1.y - t2.y;
		float B2 = t2.x - t1.x;
		float C2 = t1.x * t2.y - t2.x * t1.y;

		if (A1 * B2 == A2 * B1)
			return false;

		cocos2d::CCPoint p;
		p.x = (B1 * C2 - B2 * C1) / (A1 * B2 - A2 * B1);
		p.y = (C1 * A2 - C2 * A1) / (A1 * B2 - A2 * B1);

		bool b1;
		bool b2;

		if (fabs(B1) > fabs(A1))
			b1 = p.x <= MAX(p1.x, p2.x) && p.x >= MIN(p1.x, p2.x);
		else
			b1 = p.y <= MAX(p1.y, p2.y) && p.y >= MIN(p1.y, p2.y);


		if (fabs(B2) > fabs(A2))
			b2 = p.x <= MAX(t1.x, t2.x) && p.x >= MIN(t1.x, t2.x);
		else
			b2 = p.y <= MAX(t1.y, t2.y) && p.y >= MIN(t1.y, t2.y);

		return (b1 && b2);
	}
};

#endif //__Geometry_H_
