#ifndef __GameDelegate_H_
#define __GameDelegate_H_

#include <string>
#include "support/tinyxml2/tinyxml2.h"
#include "platform/CCFileUtils.h"
#include "cocoa/CCGeometry.h"
#include "Animal.h"
#include "Dog.h"
#include "Sheep.h"
#include "Paddock.h"

class IGameDelegate {

public:

    virtual void onDogAdd(const Dog *) = 0;

    virtual void onSheepAdd(const Sheep *) = 0;

    virtual void onAnimalMoved(const Animal *) { }

    virtual void onAnimalRotated(const Animal *) { }

    virtual void onPaddockCreate(const Paddock *gameObject)  = 0;

    virtual void onDogSelected(const Animal *) { }

    virtual void onGameFinish()  = 0;

    virtual void onTimeIsOut() = 0;

    virtual ~IGameDelegate() { }

};
#endif //__GameDelegate_H_

