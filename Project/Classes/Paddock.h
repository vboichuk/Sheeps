
#ifndef __Ponies__Paddock__
#define __Ponies__Paddock__

#include <iostream>
#include "cocos2d.h"
#include "ICollisionDetector.h"

class Paddock { 
protected:

	const PolygonObstacle mObstacle;

public:

	const PolygonObstacle &getObstacle()  const { return mObstacle; }

	Paddock(PolygonObstacle o);

	bool viaDoor(const cocos2d::CCPoint &p1, const cocos2d::CCPoint &p2) const;
};

#endif /* defined(__Ponies__Paddock__) */
