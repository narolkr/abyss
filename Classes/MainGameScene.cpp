#include"MainGameScene.h"

#include"Player.hpp"
#include"GameLayer.h"
#include"TMXLevel.h"
#include"HUDInputLayer.h"
#include"reader/CreatorReader.h"
#include"PauseLayer.h"
#include"MainMenu.h"
#include "GameOverLayer.hpp"
#include "Enemy.h"
#include "PickUp.hpp"
#include<sstream>

using namespace cocos2d;

MainGameScene* MainGameScene::mInstance = nullptr;
MainGameScene::MainGameScene() : mPauseLayer(nullptr)
{
}

cocos2d::Scene * MainGameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f,-700));
	mInstance = MainGameScene::create();
	scene->addChild(mInstance);
	return scene;
}

MainGameScene* MainGameScene::getInstance() { return mInstance; }
bool MainGameScene::init()
{
	if (!Scene::init())
	{
		CCLOG("failed to init MainGameScene");
		return false;
	}

	mFrameCacheInst = cocos2d::SpriteFrameCache::getInstance();

	loadAssets();
	initObjects();
	addLayers();
	setEventCallbacks();

	scheduleUpdate();
	return true;
}


void MainGameScene::loadAssets()
{
	//load all plist
	mFrameCacheInst->addSpriteFramesWithFile("player/Ninja2.plist");
    mFrameCacheInst->addSpriteFramesWithFile("Enemies/Cat/cat.plist");
    mFrameCacheInst->addSpriteFramesWithFile("Enemies/Flyer/flyer.plist");
    mFrameCacheInst->addSpriteFramesWithFile("Enemies/Cactus/Cactus.plist");
	mFrameCacheInst->addSpriteFramesWithFile("Enemies/Bosswasp/fly.plist");
    mFrameCacheInst->addSpriteFramesWithFile("player/playerDead.plist");
	mFrameCacheInst->addSpriteFramesWithFile("Enemies/Bomber/cute_phsyco.plist");
	mFrameCacheInst->addSpriteFramesWithFile("Effects/plane explosion/orien_explosion.plist");
	mFrameCacheInst->addSpriteFramesWithFile("Effects/explosion/explosion.plist");
	//load all sprites
}

void MainGameScene::addLayers()
{
	mGameLayer = new GameLayer(mPlayer);
	mGameLayer->init();
	this->addChild(mGameLayer,-1);

	mHUDInputLayer = new HUDInputLayer(mPlayer);
	mHUDInputLayer->init();
	this->addChild(mHUDInputLayer,1);

	auto bg = Sprite::create("creator/textures/bg.png");
	bg->setScale(.8);
	bg->setPosition(Vec2(240,400));
	this->addChild(bg,-2);
}


void MainGameScene::setEventCallbacks()
{
	auto onPause = CC_CALLBACK_1(MainGameScene::onEventAddPauseLayer, this);
	auto listener1 = EventListenerCustom::create(Globals::EVENT_ADD_PAUSE_MENU, onPause);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);

	auto onResume = CC_CALLBACK_1(MainGameScene::onEventRemovePauseLayer, this);
	auto listener2 = EventListenerCustom::create(Globals::EVENT_REMOVE_PAUSE_MENU, onResume);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, this);

	auto onExit = CC_CALLBACK_1(MainGameScene::onEventExitToMenu, this);
	auto listener3 = EventListenerCustom::create(Globals::EVENT_EXIT_TO_MENU, onExit);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener3, this);

	auto onTrigger = CC_CALLBACK_1(MainGameScene::onEventBossArea, this);
	auto listener4 = EventListenerCustom::create(Globals::EVENT_JUNGLE_BOSS_AREA, onTrigger);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener4, this);

	/*auto onTrigger2 = CC_CALLBACK_1(MainGameScene::onEventLevelClear, this);
	auto listener5 = EventListenerCustom::create(Globals::EVENT_LEVEL_CLEARED, onTrigger2);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener5, this);*/
    
    auto onGameOver = CC_CALLBACK_1(MainGameScene::onEventAddGameOverLayer, this);
    auto listener6 = EventListenerCustom::create(Globals::EVENT_GAME_OVER_MENU, onGameOver);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener6, this);
    
    auto onPlayAgain = CC_CALLBACK_1(MainGameScene::onEventPlayAgain, this);
    auto listener7 = EventListenerCustom::create(Globals::EVENT_PLAY_AGAIN_MENU, onPlayAgain);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener7, this);

}


void MainGameScene::buttonCallback(cocos2d::Ref*)
{
	CCLOG("\n MainMenuScene::onEnter() called");
}

void MainGameScene::initObjects()
{
	mPlayer = Player::create();
    Enemy::resetStaticEnemyTag();
    PickUp::resetStaticPickUpTag();
    mCurrentTime = time(NULL);
    mTimer = 0.0f;
    mPlayer->setScore(0);
}


void MainGameScene::onEnter()
{
	Scene::onEnter();	
}

void MainGameScene::update(float delta){
    mTimer = time(NULL)-mCurrentTime;
	if (mPlayer)
	{
        std::stringstream ss;
        ss<<mTimer;
        mHUDInputLayer->getTimerLabel()->setString(ss.str());
        ss.str("");
        ss<<mPlayer->getScore();
		mHUDInputLayer->getScoreLabel()->setString(ss.str());
	}
}

void MainGameScene::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
}

void MainGameScene::onExit()
{
	Scene::onExit();

	if (mHUDInputLayer)
	{
		mHUDInputLayer->removeFromParentAndCleanup(true);
		delete mHUDInputLayer;
	}
	if (mGameLayer)
	{
		mGameLayer->removeFromParentAndCleanup(true);
		delete mGameLayer;
	}
	if (mPauseLayer)
	{
		mPauseLayer->removeFromParentAndCleanup(true);
		delete mPauseLayer;
	}
}

void MainGameScene::onEventRemovePauseLayer(cocos2d::EventCustom* pEvent)
{
	Director::getInstance()->resume();
	mPauseLayer->removeFromParentAndCleanup(true);
	delete mPauseLayer;
	mPauseLayer = nullptr;

	mHUDInputLayer->setButtonsState(true);
}


void MainGameScene::onEventAddPauseLayer(cocos2d::EventCustom* pEvent)
{
	Director::getInstance()->pause();
	mPauseLayer = new PauseLayer();
	mPauseLayer->init();
	mPauseLayer->setSwallowsTouches(true);
	this->addChild(mPauseLayer,100);

	mHUDInputLayer->setButtonsState(false);
	
}

void MainGameScene::onEventExitToMenu(cocos2d::EventCustom* pEvent)
{
	Director::getInstance()->resume();
	auto action = TransitionSplitRows::create(1.0f, MainMenu::createScene());
	Director::getInstance()->replaceScene(action);
}

void MainGameScene::onEventBossArea(cocos2d::EventCustom * pEvent)
{
	auto text = ui::Text::create("Testing","fonts/arial.ttf",30);
	text->setPosition(Vec2(240,400));
	this->addChild(text,100);
}

void MainGameScene::onEventLevelClear(cocos2d::EventCustom * pEvent)
{
	auto text = ui::Text::create("Level Cleared", "fonts/arial.ttf", 40);
	text->setPosition(Vec2(240, 400));
	this->addChild(text, 100);
	text->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
}

void MainGameScene::onEventAddGameOverLayer(cocos2d::EventCustom* pEvent)
{
    mGameOverLayer = new GameOverLayer();
    mGameOverLayer->init();
    mGameOverLayer->setSwallowsTouches(true);
    this->addChild(mGameOverLayer,100);
    mHUDInputLayer->setButtonsState(false);
	mPlayer = nullptr;
}

void MainGameScene::onEventPlayAgain(cocos2d::EventCustom* pEvent)
{
    auto action = TransitionSplitCols::create(1.0f,MainGameScene::createScene());
    Director::getInstance()->replaceScene(action);
}
