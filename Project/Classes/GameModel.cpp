

#include "GameModel.h"
#include "XMLHelper.h"
#include "XMLLoader.h"
#include "Timer.h"

GameModel::GameModel()
	: mGameDelegate(NULL)
    , mPadlock (NULL)
	, mCollisionDetector(NULL)
	, isRunning(false)
	, mTimer(0x0),
	mLevelTime(0)
{
	this->mTimer = new Timer();
	this->mTimer->onFinish += new Listener::MethodDelegateData<GameModel, float>(this, &GameModel::onTimeIsOut);

	this->mCollisionDetector = new ICollisionDetector();
}

GameModel::~GameModel() {

    for (std::vector<Dog*>::iterator it = mDogs.begin(); it != mDogs.end(); delete *(it++));
    for (std::vector<Sheep*>::iterator it = mSheeps.begin(); it != mSheeps.end(); delete *(it++));

    mDogs.clear();
    mSheeps.clear();
    mTimer->stop();

    setPaddock(0x0);

    delete mTimer;
    delete mCollisionDetector;
}

void GameModel::init(int levelNum, std::string xmlFileCOnfig, cocos2d::CCSize fieldSize) {

	if (isRunning) return;

    for (std::vector<Dog*>::iterator it = mDogs.begin(); it != mDogs.end(); delete *(it++));
    for (std::vector<Sheep*>::iterator it = mSheeps.begin(); it != mSheeps.end(); delete *(it++));

    mDogs.clear();
    mSheeps.clear();

    this->mCollisionDetector->clearObstacles();

	int dogs = 0;
    int sheeps = 0;
    int levelTime = 0;
    this->fieldSize = fieldSize;

    tinyxml2::XMLDocument *doc = XMLHelper::createDocHandle(xmlFileCOnfig);
    assert(doc);

    tinyxml2::XMLElement *root = doc->FirstChildElement();
    tinyxml2::XMLElement *pLevels = root->FirstChildElement("levels");
    tinyxml2::XMLElement *pLevel = pLevels->FirstChildElement("level");

    for (tinyxml2::XMLElement *pChild = pLevels->FirstChildElement("level"); pChild ; pChild = pChild->NextSiblingElement("level")) {
        int id = -1;
        pChild->QueryIntAttribute("id", &id);
        if (id == levelNum) {
        	pLevel = pChild;
        	break;
        }
    }

    pLevel->QueryIntAttribute("dogs", &dogs);
    pLevel->QueryIntAttribute("sheeps", &sheeps);
    pLevel->QueryIntAttribute("time", &levelTime);

    this->mLevelTime = levelTime;

    PolygonObstacle *obstacle = PolygonObstacleLoader::createObjectFromXML(pLevel->FirstChildElement("paddock"));
	
	this->mPadlock = new Paddock(*obstacle);
	if (mGameDelegate) mGameDelegate->onPaddockCreate(mPadlock);

    this->mCollisionDetector->addObstacle(obstacle);

    this->createDogs(root->FirstChildElement("dog"), (unsigned int) dogs);
    this->createSheeps(root->FirstChildElement("sheep"), (unsigned int) sheeps);

    delete doc, doc = 0x0;
}

void GameModel::setPaddock(Paddock *p) {
	if (mPadlock == p) return;
	if (mPadlock) delete mPadlock;
	mPadlock = p;
}

void GameModel::startGame() {
	if (isRunning) return;
	isRunning = true;
	mTimer->start(mLevelTime);
}


cocos2d::CCPoint GameModel::getRandomPos() const {
	cocos2d::CCPoint p;
	do {
		p = cocos2d::CCPoint(CCRANDOM_0_1() * fieldSize.width, CCRANDOM_0_1() * fieldSize.height);
	}
	while (mPadlock->getObstacle().getRect().containsPoint(p));
	return p;
}

void GameModel::initAnimal(Animal *animal) {
	animal->setLocation(getRandomPos());
	animal->setAngle(rand() % 360);
	animal->onAngleChange+= new Listener::MethodDelegateData<GameModel, float>(this, &GameModel::onAnimaRotated);
	animal->setMovingDelegate(mCollisionDetector);
}

void GameModel::createDogs(const tinyxml2::XMLElement *pElement, unsigned int count) {

    mDogs.resize(count, 0x0);
    {
        Dog *oneDog = new Dog();
        DogLoader::loadObjectFromXML(pElement, oneDog);
        for (int i = 0; i < mDogs.size(); mDogs[i++] = new Dog(*oneDog));
        delete oneDog;
    }
    for (size_t i = 0; i < mDogs.size(); i++) {
    	initAnimal(mDogs[i]);
        mDogs[i]->onLocationChange += new Listener::MethodDelegateData<GameModel, cocos2d::CCPoint>(this, &GameModel::onDogMoved);
        if (mGameDelegate) mGameDelegate->onDogAdd(mDogs[i]);
    }

    this->onCurrentDogChange(mDogs.begin());
}

void GameModel::createSheeps(const tinyxml2::XMLElement *pElement, unsigned int count) {
    mSheeps.resize(count, 0x0);
    {
        Sheep *oneSheep = new Sheep();
        SheepLoader::loadObjectFromXML(pElement, oneSheep);
        for (int i = 0; i < mSheeps.size(); mSheeps[i++] = new Sheep(*oneSheep));
        delete oneSheep;
    }

    for (size_t i = 0; i < mSheeps.size(); ++i) {
        initAnimal(mSheeps[i]);
        mSheeps[i]->onLocationChange += new Listener::MethodDelegateData<GameModel, cocos2d::CCPoint>(this, &GameModel::onSheepMoved);
        if (mGameDelegate) mGameDelegate->onSheepAdd(mSheeps[i]);
    }
}


void GameModel::touchBegan(cocos2d::CCPoint p) {

	if (!isRunning) return;

    bool dogTapped = false;
    for (std::vector<Dog*>::iterator it = mDogs.begin(); it != mDogs.end(); it++ ) {
        if ((*it)->getRect().containsPoint(p)) {
            dogTapped = true;
            onCurrentDogChange(it);
            break;
        }
    }
    
    if ( ! dogTapped ) {
        (*mDogs.begin())->gotoLocation(p);
    }
}

void GameModel::touchMoved(cocos2d::CCPoint pos) {

	if (!isRunning) return;

    if(!(*mDogs.begin())->getRect().containsPoint(pos))
        (*mDogs.begin())->gotoLocation(pos);
}

void GameModel::touchCancelled(cocos2d::CCPoint pos) { }

void GameModel::touchEnded(cocos2d::CCPoint point) { }


void GameModel::onCurrentDogChange(std::vector<Dog*>::iterator it) {

    if (it == mDogs.begin())
        return;
    Dog *dog = *it;
    
    *it = *mDogs.begin();
	*mDogs.begin() = dog;
   
	if (mGameDelegate) mGameDelegate->onDogSelected(dog);
}

void GameModel::onAnimalMoved(void *animal) {
    Animal *sender = (Animal*)animal;
    if (mGameDelegate) mGameDelegate->onAnimalMoved(sender);
}

void GameModel::onAnimaRotated(void *animal, float prev) {
    Animal *sender = (Animal*)animal;
    if (mGameDelegate) mGameDelegate->onAnimalRotated(sender);
}

void GameModel::onDogMoved(void *inDog, cocos2d::CCPoint prev) {
    Dog *dog = (Dog*)inDog;
    onAnimalMoved(dog);
    const bool isMainDog = (dog == *mDogs.begin());

    for (std::vector<Sheep*>::iterator it = mSheeps.begin(); it != mSheeps.end(); ++it) {
    	if ( ! (*it)->IsFree()) continue;

    	if ( ((*it)->getTarget() == NULL) || (isMainDog && (*it)->getTarget() != dog) ) {
            if ( ! dog->inZone((*it)->getLocation()) ) continue;
            (*it)->setTarget(dog);
        }
    }
}

void GameModel::onSheepMoved(void *inSheep, cocos2d::CCPoint prev) {
    Sheep *sheep = (Sheep*)inSheep;
    onAnimalMoved(sheep);
    if (sheep->IsFree() && mPadlock->viaDoor(prev, sheep->getLocation())) {
    	sheep->setTarget(0x0);
    	CCPoint dir = (sheep->getLocation() - prev) * (rand() % 60);
    	cocos2d::CCPoint target = sheep->getLocation() + dir;
		sheep->gotoLocation(target);
		sheep->setIsFree(false);
		checkFinish();
    }
}


void GameModel::checkFinish() {
	if ( ! isRunning ) {
		cocos2d::CCLog("TIME IS OVER :(");
		return;
	}

    for (std::vector<Sheep*>::const_iterator it = mSheeps.begin(); it != mSheeps.end(); it++) {
        if ((*it)->IsFree())
            return;
    }

    this->onGameFinish();
}

void GameModel::onGameFinish() {
	mTimer->stop();
	isRunning = false;
	if (mGameDelegate) mGameDelegate->onGameFinish();
	onGameOver.invoke(this, true);
}

void GameModel::onTimeIsOut(void *sender, float time) {
	isRunning = false;
	if (mGameDelegate) mGameDelegate->onTimeIsOut();
	onGameOver.invoke(this, false);
}
