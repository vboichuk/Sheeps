
#include "GameModel.h"
#include "touch_dispatcher/CCTouch.h"

#ifndef __GameController_H_
#define __GameController_H_

class GameController {

protected:

    GameModel* const gameModel;

public:

    GameController(GameModel *pModel);

    void touchBegan(cocos2d::CCTouch * pTouch, cocos2d::CCEvent * pEvent) const ;
    void touchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) const ;
    void touchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) const;
    void touchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) const ;
};


#endif //__GameController_H_
