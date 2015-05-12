
#include "GameView.h"
#include "DogSprite.h"
#include "SheepSprite.h"

const int backgroundTag = 640;

using namespace cocos2d;

GameView::GameView(GameModel *pModel, GameController *pController)
        :gameModel(pModel)
        ,gameController(pController)
		,mSelectedDog(0x0)
{ 
	
}


bool GameView::init() {
    
    if ( ! CCSpriteBatchNode::initWithFile("art/game.png", kDefaultSpriteBatchCapacity)) return false;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("art/game.plist");

    this->setContentSize(CCDirector::sharedDirector()->getWinSize());
    
    this->prepareBackground();

    return true;
}

void GameView::reset() {

	mAnimals.clear();

	mSelectedDog = 0x0;

	for (int i = getChildrenCount()-1; i >= 0; i--) {
		CCNode *child = (CCNode*)getChildren()->objectAtIndex(i);
		if (child->getTag() != backgroundTag)
			child->removeFromParent();
	}
}


bool GameView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    gameController->touchBegan(pTouch, pEvent);
    return true; 
}
void GameView::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    gameController->touchMoved(pTouch, pEvent);
}
void GameView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    gameController->touchEnded(pTouch, pEvent);
}
void GameView::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    gameController->touchCancelled(pTouch, pEvent);
}

#pragma mark -


void GameView::onDogAdd(const Dog* dog) { 
	DogSprite *s = DogSprite::create();
	s->setPosition(dog->getLocation());
	s->setRotation(dog->getAngle());
	this->addChild(s);
	mAnimals[dog] = s;
}

void GameView::onSheepAdd(const Sheep* sheep) { 
	SheepSprite *s = SheepSprite::create();
	s->setPosition(sheep->getLocation());
	s->setRotation(sheep->getAngle());
	this->addChild(s);
	mAnimals[sheep] = s;
}

void GameView::onAnimalMoved(const Animal* animal) { 
	mAnimals[animal]->setPosition(animal->getLocation());
}

void GameView::onAnimalRotated(const Animal *animal) {
    float angle = animal->getAngle();
    angle *= -1;
	mAnimals[animal]->setRotation(angle);
}

void GameView::onDogSelected(const Animal *aConst) {
    if (mSelectedDog)
        mSelectedDog->setScale(1);
    if (aConst && mAnimals[aConst])
        mAnimals[aConst]->setScale(1.2f);
    mSelectedDog = mAnimals[aConst];
}

void GameView::prepareBackground() {

    srand((unsigned int) time(0x0));

    CCSize tiled = CCSizeZero;

    CCSpriteFrame *frame1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tile_1.png");

    while (tiled.height < m_obContentSize.height) {
        tiled.width = 0;
        while (tiled.width  < m_obContentSize.width ) {
            CCSprite *s = CCSprite::createWithSpriteFrame(frame1);
            s->setAnchorPoint(CCPointZero);
            s->setPosition(tiled);
            s->setTag(backgroundTag);
            this->addChild(s);
            tiled.width += frame1->getRect().size.width;
        }
        tiled.height += frame1->getRect().size.height;
    }

	CCSpriteFrame *flowerFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("flower.png");
	int rnd = 16 + (rand() % 8);
	for (int i = 0; i < rnd; i++) {
		CCSprite *s = CCSprite::createWithSpriteFrame(flowerFrame);
        s->setPosition(ccp(this->getContentSize().width * CCRANDOM_0_1(), this->getContentSize().height * CCRANDOM_0_1()));
		s->setRotation(rand() % 360);
		s->setTag(backgroundTag);
        this->addChild(s);
	}
}

void GameView::onPaddockCreate(const Paddock *gameObject) {

	std::vector<cocos2d::CCPoint> points = gameObject->getObstacle().points;

	for (int i = 0; i < points.size() - 1; i++) {
		CCPoint v = points[i+1] - points[i];
		float len = v.getLength();

		CCSprite *s = CCSprite::createWithSpriteFrameName("fence1.png");
		s->setScaleX(len / s->getContentSize().height);
		s->setAnchorPoint(ccp(0, 0.5f));
		s->ignoreAnchorPointForPosition(false);
		s->setPosition(points[i]);

		s->setRotation(-CC_RADIANS_TO_DEGREES(v.getAngle()));
		this->addChild(s);
	}

	for (int i = 0; i < points.size(); i++) {
			CCSprite *s = CCSprite::createWithSpriteFrameName("fence2.png");
			s->setPosition(points[i]);
			this->addChild(s);
		}
}

void GameView::onGameFinish() { }

void GameView::onTimeIsOut() { }
