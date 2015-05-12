
#include "GameController.h"

using namespace cocos2d;

GameController::GameController(GameModel *pModel)
: gameModel(pModel)
{
}

void GameController::touchBegan(CCTouch *pTouch, CCEvent *pEvent) const {
    gameModel->touchBegan(pTouch->getLocation());
}

void GameController::touchMoved(CCTouch *pTouch, CCEvent *pEvent) const {
    gameModel->touchMoved(pTouch->getLocation());
}

void GameController::touchCancelled(CCTouch *pTouch, CCEvent *pEvent) const {
    gameModel->touchCancelled(pTouch->getLocation());
}

void GameController::touchEnded(CCTouch *pTouch, CCEvent *pEvent) const {
    gameModel->touchEnded(pTouch->getLocation());
}
