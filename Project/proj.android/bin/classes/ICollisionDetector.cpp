

#include "ICollisionDetector.h"
#include "cocos2d.h"
#include "Geometry.h"

PolygonObstacle::PolygonObstacle(const std::vector<cocos2d::CCPoint> vec)
	: points(vec)
{
	float x1=0, x2=0, y1=0, y2=0;
	if ( ! points.empty()) {
		x1 = x2 = (*points.begin()).x;
		y1 = y2 = (*points.begin()).y;
	}
	for (int i = 1; i < points.size(); ++i) {
		x1 = MIN(x1, points[i].x);
		x2 = MAX(x2, points[i].x);
		y1 = MIN(y1, points[i].y);
		y2 = MAX(y2, points[i].y);
	}

	mRect = cocos2d::CCRect(x1, y1, x2-x1, y2-y1);
}


bool PolygonObstacle::collision(const cocos2d::CCPoint &p1, const cocos2d::CCPoint &p2) const {
	if ( ! mRect.containsPoint(p1) && ! mRect.containsPoint(p2))
		return false;

	for (int i = 0; i < points.size()-1; ++i) {
		if (Geometry::intersect(p1, p2, points[i], points[i+1]))
			return true;
	}

	return false;
}

ICollisionDetector::~ICollisionDetector() {
	clearObstacles();
}

void ICollisionDetector::clearObstacles() {
	for (std::vector<const Obstacle*>::iterator it = mObstacles.begin(); it != mObstacles.end(); ++it) {
		delete *it;
	}
	mObstacles.clear();
}

bool ICollisionDetector::tryMove(const cocos2d::CCPoint &p1, const cocos2d::CCPoint &p2) const {
	for (int i = 0; i < mObstacles.size(); ++i) {
		if (mObstacles[i]->collision(p1, p2))
			return false;
	}
	return true;
}

