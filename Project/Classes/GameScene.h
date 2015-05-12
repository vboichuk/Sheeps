
#ifndef __Ponies__GameScene__
#define __Ponies__GameScene__

#include <iostream>

#include "cocos2d.h"
#include "GameScene.h"
#include "GameView.h"
#include "GameController.h"
#include "GameModel.h"
//#include "Menu.h"

class GameScene : public cocos2d::CCScene {
private:

	int level;

protected:

    GameController *gameController;
    GameModel *gameModel;
    GameView *gameView;

    cocos2d::CCMenu *mMenu;
    void prepareMenu();

    cocos2d::CCLabelBMFont *mTimeLabel;
    void updateTimeLabel(float dt);

    void showCongratulations();
    void showYouAreLooser();

    void restart();

    void enableMenu();
    void disableMenu();

public:
    
    GameScene();
    
    virtual ~GameScene();
    
    virtual bool init();  
    
    CREATE_FUNC(GameScene);

    void onGameOver(void* sender, bool success);

    virtual void onEnter();
    virtual void onExit();

    void onPlayTapped(cocos2d::CCObject *sender);
};


#endif /* defined(__Ponies__GameScene__) */
