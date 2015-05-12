/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "AppDelegate.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include <vector>
#include <string>

#include "GameScene.h"

USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate() { }

AppDelegate::~AppDelegate()  { }


bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	CCSize frameSize = pEGLView->getFrameSize();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
#else
    CCSize designSize = frameSize; //CCSize(1776, 960);
    pEGLView->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	std::vector<std::string> searchPaths;
	searchPaths.push_back("assets");
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
#endif

    CCLog("frame size = %f %f", frameSize.width, frameSize.height);

    pDirector->setDisplayStats(false);

    pDirector->setAnimationInterval(1.0 / 60);
	
    CCScene *pScene = GameScene::create();
    
    pDirector->runWithScene(pScene);

    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    
    cocos2d::CCDirector::sharedDirector()->pause();
    cocos2d::CCDirector::sharedDirector()->stopAnimation();
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {

    cocos2d::CCDirector::sharedDirector()->resume();
    cocos2d::CCDirector::sharedDirector()->startAnimation();
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
#endif

}

void AppDelegate::keyBackClicked() {
    CCDirector::sharedDirector()->end();
}

void AppDelegate::keyMenuClicked() { }
