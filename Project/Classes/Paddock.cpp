
#include "Paddock.h"
#include "Geometry.h"

using namespace cocos2d;

Paddock::Paddock(PolygonObstacle o):mObstacle(o) { }

bool Paddock::viaDoor(const cocos2d::CCPoint &p1, const cocos2d::CCPoint &p2) const {

	if (mObstacle.points.size() < 2)
		return false;

	if (!mObstacle.getRect().containsPoint(p1) && !mObstacle.getRect().containsPoint(p2)) {
		return false;
	}

	return Geometry::intersect(p1, p2, *mObstacle.points.begin(), *(mObstacle.points.end()-1));
}
