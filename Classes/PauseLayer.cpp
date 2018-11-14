#include"PauseLayer.h"
#include"Player.hpp"
#include"reader/CreatorReader.h"
#include"Globals.h"


using namespace cocos2d;

PauseLayer::PauseLayer() 
{
}

bool PauseLayer::init()
{
	if (!Layer::init())
	{
		CCLOG("failed to initialize PauseLayer");
		return false;
	}

	loadScene();
	setupButtonCallbacks();

	return true;
}


void PauseLayer::setupButtonCallbacks()
{
	auto ButtonMoveLeft = static_cast<ui::Button*>(mCCScene->getChildByName("ButtonResume"));
	ButtonMoveLeft->addClickEventListener(CC_CALLBACK_0(PauseLayer::resumeButtonCallback, this));

	auto ButtonExit = static_cast<ui::Button*>(mCCScene->getChildByName("ButtonExit"));
	ButtonExit->addClickEventListener(CC_CALLBACK_0(PauseLayer::exitButtonCallback, this));
}


void PauseLayer::resumeButtonCallback()
{
	EventCustom event(Globals::EVENT_REMOVE_PAUSE_MENU);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void PauseLayer::exitButtonCallback()
{		
	EventCustom event(Globals::EVENT_EXIT_TO_MENU);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}


void PauseLayer::loadScene()
{
	auto reader = creator::CreatorReader::createWithFilename("creator/scenes/PausePopUp.ccreator");
	if (!reader)
	{
		CCLOG("PauseLayer reader == null");
		return ;
	}
	reader->setup();
	mCCScene = reader->getSceneGraph();
	this->addChild(mCCScene);
}

void PauseLayer::onEnter()
{
	Layer::onEnter();
}

void PauseLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();	
}

void PauseLayer::onExit()
{
	Layer::onExit();
}