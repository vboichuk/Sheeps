

#ifndef __Ponies__SheepSprite__
#define __Ponies__SheepSprite__

#include <iostream>
#include "sprite_nodes/CCSprite.h"

class SheepSprite : public cocos2d::CCSprite {

protected:

    void setupAnimation(float dt);

public:

    virtual bool init();

    CREATE_FUNC(SheepSprite);
    
    virtual void setRotation(float fRotation);
};

#endif /* defined(__Ponies__SheepSprite__) */
