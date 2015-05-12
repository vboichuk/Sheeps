

#ifndef COLLISIONDETECTOR_H_
#define COLLISIONDETECTOR_H_

#include "IMovingDelegate.h"
#include <vector>
#include "cocos2d.h"

class Obstacle {
public:
	virtual ~Obstacle() { }
	virtual bool collision(const cocos2d::CCPoint &p1, const cocos2d::CCPoint &p2) const { return false; }
};

///////////////////////////////////////////////////////////////////

class PolygonObstacle : public Obstacle {

protected:
	cocos2d::CCRect mRect;

public:
	const std::vector<cocos2d::CCPoint> points;
	const cocos2d::CCRect &getRect() const { return mRect; }
	PolygonObstacle(const std::vector<cocos2d::CCPoint> vec);
	virtual ~PolygonObstacle() { }
	virtual bool collision(const cocos2d::CCPoint &p1, const cocos2d::CCPoint &p2) const;
};

///////////////////////////////////////////////////////////////////

class ICollisionDetector : public IMovingDelegate {

protected:

	std::vector<const Obstacle*> mObstacles;

public:

	void addObstacle(const Obstacle *p) { mObstacles.push_back(p); }
	void clearObstacles();

	virtual ~ICollisionDetector();

	virtual bool tryMove(const cocos2d::CCPoint &p1, const cocos2d::CCPoint &p2) const;
};

#endif /* COLLISIONDETECTOR_H_ */
