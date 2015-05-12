

#ifndef __Ponies__ITimer__
#define __Ponies__ITimer__

#include "EventHandler.h"

class ITimer {

public:

    virtual ~ITimer() { }
    virtual float getTime() const = 0;
    virtual void stop() = 0;
    virtual void start(float time) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    Listener::EventHandler<float> onFinish;
};

#endif /* defined(__Ponies__ITimer__) */
