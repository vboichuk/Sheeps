

#include "SheepSprite.h"
#include "sprite_nodes/CCAnimation.h"
#include "sprite_nodes/CCSpriteFrameCache.h"
#include "actions/CCActionInterval.h"
#include "sprite_nodes/CCAnimationCache.h"

using namespace cocos2d;

bool SheepSprite::init() {

    if ( ! CCSprite::initWithSpriteFrameName("sheep_1.png"))
        return false;

    this->scheduleOnce(schedule_selector(SheepSprite::setupAnimation), 0.5f * CCRANDOM_0_1());

    return true;
}

void SheepSprite::setRotation(float fRotation) {
    if (fabs(fRotation) < 90)
        setFlipX(false);
    else
        setFlipX(true);
}

void SheepSprite::setupAnimation(float f) {
    CCAnimation *anim = CCAnimationCache::sharedAnimationCache()->animationByName("sheep_animation");
    if ( ! anim ) {
        anim = CCAnimation::create();
        anim->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( "sheep_1.png" ));
        anim->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( "sheep_2.png" ));
        anim->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( "sheep_3.png" ));
        anim->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( "sheep_4.png" ));
        anim->setDelayPerUnit(0.2f);
        anim->setLoops(-1);
        CCAnimationCache::sharedAnimationCache()->addAnimation(anim, "sheep_animation");
    }

    CCAnimate *theAnim = CCAnimate::create (anim);
    theAnim->setTag(1);
    this->runAction(theAnim);
}
