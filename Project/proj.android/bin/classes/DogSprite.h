

#ifndef __Ponies__DogSprite__
#define __Ponies__DogSprite__

#include <iostream>
#include "cocos2d.h"

class DogSprite : public cocos2d::CCSprite {
public:
    virtual bool init();
    CREATE_FUNC(DogSprite)
};

#endif /* defined(__Ponies__DogSprite__) */
