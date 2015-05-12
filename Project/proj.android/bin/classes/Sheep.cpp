

#include "Sheep.h"

Sheep::Sheep()
:mTarget(0x0)
, mIsFree(true)
{
}

void Sheep::setTarget(Animal *data) {
    
    if (mTarget)
        mTarget->onLocationChange -= new Listener::MethodDelegateData<Sheep, cocos2d::CCPoint>(this, &Sheep::onTargetMoved);
    
    mTarget = data;

    if (mTarget) {
        mTarget->onLocationChange += new Listener::MethodDelegateData<Sheep, cocos2d::CCPoint>(this, &Sheep::onTargetMoved);
        gotoLocation(mTarget->getLocation());
    }
}

void Sheep::onTargetMoved(void *sender, cocos2d::CCPoint prev) {
    this->gotoLocation(mTarget->getLocation());
}
