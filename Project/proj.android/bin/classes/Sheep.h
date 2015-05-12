
#ifndef __Sheep_H_
#define __Sheep_H_

#include "Animal.h"
#include "Dog.h"

class Sheep : public Animal
{

private:

    bool mIsFree;

protected:

    const Animal *mTarget;
    virtual bool isMovingDone(cocos2d::CCPoint dist, cocos2d::CCPoint delta) {
            return (
            		fabs(dist.x) < CCRANDOM_0_1() * getSize().width / 2
            	&&  fabs(dist.y) < CCRANDOM_0_1() * getSize().height / 2);
        }
public:

    Sheep();

	virtual ~Sheep() { }

    const Animal *getTarget() const { return mTarget; }
    virtual void setTarget(Animal *data);
    void onTargetMoved(void* sender, cocos2d::CCPoint prev);

    void setIsFree(bool val) { mIsFree = val; }
    bool IsFree() const { return mIsFree; }
};


#endif //__Sheep_H_
