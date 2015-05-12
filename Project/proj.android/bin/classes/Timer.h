

#ifndef __Ponies__Timer__
#define __Ponies__Timer__

#include "ITimer.h"
#include "cocos2d.h"

class Timer : public ITimer, public cocos2d::CCObject {
protected:
	float mTime;
	float mTotalTime;
	bool running;
	virtual void update(float dt) {
		mTime += dt;
		if (mTime >= mTotalTime) {
			this->stop();
			this->onFinish.invoke(this, mTime);
		}
	}
public:
	Timer():running(false), mTime(0) { }
    virtual ~Timer() { }
    virtual float getTime() const { return mTime; }
    virtual void stop() {
    	if (running)
    		cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(Timer::update), this);
    	running = false;
    }

    virtual void start(float time) {
    	if (running) return;
    	mTime = 0;
    	mTotalTime = time;
    	cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(Timer::update), this, 1.f/60.f, false);
    	running = true;
    }
    virtual void pause() {
    	cocos2d::CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
    }
    virtual void resume() {
    	cocos2d::CCDirector::sharedDirector()->getScheduler()->resumeTarget(this);
    }
};

#endif /* defined(__Ponies__Timer__) */
