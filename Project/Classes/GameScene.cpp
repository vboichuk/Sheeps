
#include "GameScene.h"
#include <iomanip>

using namespace cocos2d;

GameScene::GameScene()
:gameModel(0x0)
,gameController(0x0)
,gameView(0x0)
,mTimeLabel(0x0)
,level(0)
,mMenu(0x0)
{ }

GameScene::~GameScene() {
    CCLog("======================");
    CCLog("===== ~GameScene =====");
    CCLog("======================");

    this->removeAllChildren();

    delete gameController;
    delete gameView;
    delete gameModel;
}

bool GameScene::init() {
    
    if ( ! CCScene::init() )
        return false;

    gameModel = new GameModel();
    gameController = new GameController(gameModel);
    gameView = new GameView (gameModel, gameController);

    gameView->init();
    this->addChild(gameView);

	gameModel->setDelegate(gameView); 
	gameModel->onGameOver += new Listener::MethodDelegateData<GameScene, bool> (this, &GameScene::onGameOver);

	mTimeLabel = CCLabelBMFont::create("", "fonts/scorefont.fnt");
	mTimeLabel->setAnchorPoint(ccp(0.5f, 1.1f));
	mTimeLabel->ignoreAnchorPointForPosition(false);
	mTimeLabel->setPosition(ccp(m_obContentSize.width/2, m_obContentSize.height));
	this->addChild(mTimeLabel);

	this->prepareMenu();

    return true;
}

void GameScene::prepareMenu() {

	std::string textFromLocalizer = "Tap to start";

	CCLabelBMFont *label = CCLabelBMFont::create(textFromLocalizer.c_str(), "fonts/scorefont.fnt");
	CCMenuItem *playItem = CCMenuItemLabel::create(label, this, menu_selector(GameScene::onPlayTapped));

	mMenu = CCMenu::create(playItem, NULL);
	this->addChild(mMenu);
}

void  GameScene::onEnter() {
	CCScene::onEnter();
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameScene::updateTimeLabel), this, 0.5f, false);
}

void  GameScene::onExit() {
	CCScene::onExit();
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(GameScene::updateTimeLabel), this);
}


void GameScene::onPlayTapped(cocos2d::CCObject *sender) {
	restart();
	disableMenu();
}

void GameScene::enableMenu() {
	mMenu->setEnabled(true);
	mMenu->runAction(CCFadeIn::create(0.3f));
}

void GameScene::disableMenu() {
	mMenu->setEnabled(false);
	mMenu->runAction(CCFadeOut::create(0.3f));
}


void GameScene::updateTimeLabel(float dt) {

	std::stringstream st;

	st << std::setfill('0') << std::setw(3) << (int)floor(gameModel->getTime()) << "/" << std::setw(3) <<  (int)floor(gameModel->getTotalTime());

	mTimeLabel->setString(st.str().c_str());
}

void GameScene::onGameOver(void *sender, bool success) {

	// CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(GameScene::updateTimeLabel), this);
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(gameView);

	if (success) {
		this->showCongratulations();
		level = (++level) % 5;
	}
	else {
		this->showYouAreLooser();
		level = 1;
	}
}


void GameScene::showCongratulations() {
	std::stringstream st;

	// todo: make localizer :)
	st << "Congratulations!\nYou have collected all the sheep in " << (int)floor(gameModel->getTime()) << " seconds!\n";

	CCLabelBMFont *label = CCLabelBMFont::create(st.str().c_str(), "fonts/scorefont.fnt");
	label->setPosition(this->getContentSize() / 2);
	label->setAlignment(kCCTextAlignmentCenter);
	this->addChild(label);

	label->setOpacity(0);
    
    
	label->setScale(0);
    float targetScale = this->getContentSize().width / label->getContentSize().width * 0.9f;
    
	label->runAction(
			CCSequence::create(
					CCEaseExponentialOut::create(CCSpawn::createWithTwoActions(CCScaleTo::create(1.2f, targetScale), CCFadeIn::create(1.2f))),
					CCDelayTime::create(1.f),
					CCFadeOut::create(0.3f),
					CCCallFunc::create(label, callfunc_selector(CCNode::removeFromParent)),
					CCCallFunc::create(this, callfunc_selector(GameScene::enableMenu)),
					NULL
			)
	);
}

void GameScene::showYouAreLooser() {
	std::stringstream st;
	st << "Time is over... Try again";

	CCLabelBMFont *label = CCLabelBMFont::create(st.str().c_str(), "fonts/scorefont.fnt");
	label->setPosition(ccp(m_obContentSize.width/2, m_obContentSize.height));
	label->setAnchorPoint(ccp(0.5f, -0.1f));
	label->setAlignment(kCCTextAlignmentCenter);
	this->addChild(label);

    float targetScale = this->getContentSize().width / label->getContentSize().width * 0.8f;
    label->setScale(targetScale);
    
	label->runAction(
			CCSequence::create(
					CCEaseBounceOut::create(CCMoveTo::create(2.f, this->getContentSize()/2)),
					CCDelayTime::create(1.f),
					CCFadeOut::create(0.3f),
					CCCallFunc::create(label, callfunc_selector(CCNode::removeFromParent)),
					CCCallFunc::create(this, callfunc_selector(GameScene::enableMenu)),
					NULL
			)
	);
}


void GameScene::restart() {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(gameView, 0, 1);
    // CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GameScene::updateTimeLabel), this, 0.5f, false);
    gameView->reset();
    gameModel->init(level,  "data/config.xml", this->getContentSize());
    gameModel->startGame();
}
