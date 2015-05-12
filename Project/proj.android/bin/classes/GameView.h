
#ifndef __Ponies__GameLayer__
#define __Ponies__GameLayer__

#include <iostream>
#include <vector>
#include <deque>
#include <map>

#include "cocos2d.h"
#include "Animal.h"
#include "Dog.h"
#include "Sheep.h"
#include "GameModel.h"
#include "GameController.h"
#include "IGameDelegate.h"

class GameView : public cocos2d::CCSpriteBatchNode, public IGameDelegate, public cocos2d::CCTargetedTouchDelegate {

protected:

    const GameModel* const gameModel;
    const GameController* gameController;

    std::map<const Animal*, cocos2d::CCNode*> mAnimals;
    cocos2d::CCNode *mSelectedDog;

    void prepareBackground();

public:

    GameView(GameModel *pModel, GameController *pController);

    virtual ~GameView() { }
    
    virtual bool init();
    
    void reset();

    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	virtual void onDogAdd(const Dog* dog);
	virtual void onSheepAdd(const Sheep* sheep);
    virtual void onAnimalMoved(const Animal*);
	virtual void onAnimalRotated(const Animal*);
    virtual void onDogSelected(const Animal*);
    virtual void onPaddockCreate(const Paddock *gameObject);

    virtual void onGameFinish();
    virtual void onTimeIsOut();
};

#endif /* defined(__Ponies__GameLayer__) */
