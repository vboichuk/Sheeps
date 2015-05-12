
#include "DogSprite.h"

bool DogSprite::init() {
    if (! CCSprite::initWithSpriteFrameName("dog.png"))
    	return false;

    return true;
}
