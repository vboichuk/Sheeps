
#ifndef __Ponies__Dog__
#define __Ponies__Dog__

#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "Animal.h"

class Dog : public Animal {
private:
    float mRadius;
public:
	Dog() : mRadius(0) { }
    void setRadius(float d)  { if (d >= 0) mRadius = d; }
    bool inZone(cocos2d::CCPoint const aConst) const {
        cocos2d::CCPoint dist = getLocation() - aConst;
        if (fabsf(dist.x) > mRadius || fabsf(dist.y) > mRadius) return false;
        return dist.getLength() <= mRadius;
    }

};

#endif /* defined(__Ponies__Dog__) */
