
#ifndef IMOVING_DELEGATE_H_
#define IMOVING_DELEGATE_H_

#include "cocos2d.h"

using namespace cocos2d;

class IMovingDelegate {

public:

	virtual ~IMovingDelegate() { }

	virtual bool tryMove(const cocos2d::CCPoint &p1, const cocos2d::CCPoint &p2) const { return true; }
};

#endif /* IMOVING_DELEGATE_H_ */
