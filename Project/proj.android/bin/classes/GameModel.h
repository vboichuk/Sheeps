
#ifndef __GameModel_H_
#define __GameModel_H_

#include <deque>

#include "IGameDelegate.h"
#include "ICollisionDetector.h"
#include "Dog.h"
#include "Sheep.h"
#include "cocoa/CCGeometry.h"
#include "EventHandler.h"
#include "Paddock.h"
#include "ITimer.h"

class GameModel {
private:

    cocos2d::CCPoint getRandomPos() const;
    ITimer *mTimer;
    bool isRunning;
    float mLevelTime;

protected:



    IGameDelegate* mGameDelegate;
    ICollisionDetector *mCollisionDetector;

    std::vector<Dog*> mDogs;
	std::vector<Sheep*> mSheeps;

    cocos2d::CCSize fieldSize;
    
    void onCurrentDogChange(std::vector<Dog*>::iterator it);

    Paddock *mPadlock;

    void setPaddock(Paddock *p);

    void createDogs(const tinyxml2::XMLElement *pElement, unsigned int  count);
    void createSheeps(const tinyxml2::XMLElement *pElement, unsigned int count);

    void onAnimalMoved(void *animal);
    void initAnimal(Animal *animal);

    void onGameFinish();
    void onTimeIsOut(void *sender, float time);

public:

    GameModel();

    virtual ~GameModel();

    float getTime() const { return mTimer->getTime(); }
    float getTotalTime() const { return mLevelTime; }

	void setDelegate (IGameDelegate* del) { mGameDelegate = del; }

    void init(int levelNum, std::string xmlFileConfig, cocos2d::CCSize fieldSize);

    void startGame();

    void touchBegan(cocos2d::CCPoint pos);
    void touchCancelled(cocos2d::CCPoint pos);
    void touchMoved(cocos2d::CCPoint pos);
    void touchEnded(cocos2d::CCPoint pos);

    void onSheepMoved(void *sheep, cocos2d::CCPoint prev);
    void onDogMoved(void *dog, cocos2d::CCPoint prev);
    void onAnimaRotated(void *animal, float prev);

    void checkFinish();

    Listener::EventHandler<bool> onGameOver;
};


#endif //__GameModel_H_
