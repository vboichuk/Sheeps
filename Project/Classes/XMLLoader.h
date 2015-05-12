#ifndef __XMLLoader_H_
#define __XMLLoader_H_

#include <string>
#include "support/tinyxml2/tinyxml2.h"
#include "platform/CCFileUtils.h"
#include "cocoa/CCGeometry.h"
#include "ICollisionDetector.h"
#include "Animal.h"
#include "Dog.h"
#include "Sheep.h"

class GameObjectLoader {
public:
    static void loadObjectFromXML(const tinyxml2::XMLElement *pElement, GameObject *object) {
		printf("GameObjectLoader::loadObjectFromXML\n");
		cocos2d::CCSize size = CCSizeZero;
        cocos2d::CCPoint pos = CCPointZero;

		pElement->QueryFloatAttribute("w", &size.width);
		pElement->QueryFloatAttribute("h", &size.height);
        
        pElement->QueryFloatAttribute("x", &pos.x);
		pElement->QueryFloatAttribute("y", &pos.y);
        
		object->setSize(size);
        object->setLocation(pos);
    }
};

class AnimalLoader : GameObjectLoader {
public:
	static void loadObjectFromXML(const tinyxml2::XMLElement *pElement, Animal* animal) {
        GameObjectLoader::loadObjectFromXML(pElement, animal);
		float s;
		pElement->QueryFloatAttribute("speed", &s);
		 animal->setSpeed(s);
    }
};

class DogLoader : public GameObjectLoader {
public:
	static void loadObjectFromXML(const tinyxml2::XMLElement *pElement, Dog* dog) {
		AnimalLoader::loadObjectFromXML(pElement, dog);
		float r;
		pElement->QueryFloatAttribute("radius", &r);
		dog->setRadius(r);
    }
};

class SheepLoader : public GameObjectLoader {
public:
	static void loadObjectFromXML(const tinyxml2::XMLElement *pElement, Sheep* sheep) {
		AnimalLoader::loadObjectFromXML(pElement, sheep);
	}
};

class PolygonObstacleLoader {
public:
	static PolygonObstacle *createObjectFromXML(const tinyxml2::XMLElement *pElement) {
		std::vector<cocos2d::CCPoint> vec;
		for (const tinyxml2::XMLElement *pPoint = pElement->FirstChildElement("point"); pPoint ; pPoint = pPoint->NextSiblingElement("point")) {
			cocos2d::CCPoint p = cocos2d::CCPointZero;
			pPoint->QueryFloatAttribute("x", &p.x);
			pPoint->QueryFloatAttribute("y", &p.y);
			vec.push_back(p);
		}
		return new PolygonObstacle(vec);
	}
};

#endif //__XMLLoader_H_
