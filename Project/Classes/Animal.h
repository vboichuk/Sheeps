


#ifndef __Ponies_Animal__
#define __Ponies_Animal__

#include <iostream>
#include "cocos2d.h"
#include "EventHandler.h"
#include "IMovingDelegate.h"

//=========================================================
//=========================================================
//=========================================================

class GameObject {

private:

    cocos2d::CCPoint mPosition;
    cocos2d::CCSize mSize;
    float mAngle;

public:

    virtual ~GameObject() { }

    const cocos2d::CCPoint getLocation() const { return mPosition; }
    virtual void setLocation(const cocos2d::CCPoint &pos) {
        if (mPosition.equals(pos)) return;
        mPosition = pos;
    }

    float getAngle() const { return mAngle; }
    virtual void setAngle(float angle) {
        if (mAngle == angle) return;
        mAngle = angle;

    }

    cocos2d::CCRect getRect() const {
        cocos2d::CCRect rect;
        rect.size = mSize;
        rect.origin = mPosition - mSize / 2;
        return rect;
    }

	virtual void setSize(const cocos2d::CCSize& size) { mSize = size; }
	const cocos2d::CCSize& getSize() const { return mSize; }
};

//=========================================================
//=========================================================
//=========================================================

class Animal : public GameObject, cocos2d::CCObject {

private:

	cocos2d::CCPoint mTargetPos;
    bool m_isRunning;

    
protected:
    
    float m_speed;

    IMovingDelegate *mDelegate;

    bool isRunning() { return m_isRunning; }

    void scheduleUpdate() { 
        if (m_isRunning) return;
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(Animal::update), this, 1.f/1000.f, false);
        m_isRunning = true;
    }
    void unscheduleUpdate() {
        if (!m_isRunning) return;
        CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(Animal::update), this);
        m_isRunning = false;
    }
    
    virtual bool isMovingDone(cocos2d::CCPoint dist, cocos2d::CCPoint delta) {
        return (fabs(delta.x) > fabs(dist.x) && fabs(delta.y) > fabs(dist.y));
    }
    
    virtual void update(float dt) {

        cocos2d::CCPoint dist = (mTargetPos - getLocation());
        cocos2d::CCPoint delta = dist.normalize() * dt * this->getSpeed();
        
		if ( ! isMovingDone(dist, delta)) {
            this->setLocation(getLocation() + delta);
		}
        else {
        	this->stopMoving();
        }
	}

public:

    Animal()
		:m_isRunning(false)
		,m_speed(0)
		,mDelegate(0x0)
	{ }

    virtual ~Animal() { }

    float getSpeed() const { return m_speed; }
    void setSpeed(float s) { m_speed = s; }

    void setMovingDelegate(IMovingDelegate *del) { mDelegate = del; }

    virtual void setAngle(float angle) {
    	float prev = getAngle();
    	GameObject::setAngle(angle);
    	onAngleChange.invoke(this, prev);
    }

	virtual void setLocation(const cocos2d::CCPoint &position) {
		if ( mDelegate == NULL || mDelegate->tryMove(getLocation(), position)) {
			cocos2d::CCPoint pos = getLocation();
			GameObject::setLocation(position);
			onLocationChange.invoke(this, pos);
		}
		else
			this->stopMoving();
	}
	void gotoLocation(cocos2d::CCPoint const aConst) {
		mTargetPos = aConst;
		cocos2d::CCPoint dir = aConst - getLocation();
        this->setAngle(CC_RADIANS_TO_DEGREES(dir.getAngle()));
        this->scheduleUpdate();
	}

    void stopMoving() {
        this->unscheduleUpdate();
        this->mTargetPos = getLocation();
    }

    mutable Listener::EventHandler<cocos2d::CCPoint> onLocationChange;
    mutable Listener::EventHandler<float> onAngleChange;
};
    
#endif /* defined(__Ponies_Animal__) */
