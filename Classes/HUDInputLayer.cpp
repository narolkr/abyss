#include"HUDInputLayer.h"
#include"Player.hpp"
#include"reader/CreatorReader.h"
#include"Globals.h"
#include"PauseLayer.h"

using namespace cocos2d;

HUDInputLayer::HUDInputLayer() : mPlayer(nullptr)
{
	Layer();
}

HUDInputLayer::HUDInputLayer(Player* pPlayer) : mPlayer(pPlayer)
{
	Layer();
}

bool HUDInputLayer::init()
{
	if (!Layer::init())
	{
		CCLOG("failed to initialize HUDInputLayer");
		return false;
	}
    
    mPrevInput = EINPUT::Idle;
	loadScene();
	setupButtonCallbacks();
    setupLabel();
	setEventCallbacks();
	createHealthBar();
	return true;
}

void HUDInputLayer::loadScene()
{
	auto reader = creator::CreatorReader::createWithFilename("creator/scenes/HUDInputScene.ccreator");
	if (!reader)
	{
		CCLOG("HUDInput reader == null");
		return;
	}
	reader->setup();
	mCCScene = reader->getSceneGraph();
	this->addChild(mCCScene);
}

void HUDInputLayer::setEventCallbacks()
{
	auto PlayerGotHit = CC_CALLBACK_1(HUDInputLayer::onEventPlayerGotHit,this);
	auto listener = EventListenerCustom::create(Globals::EVENT_PLAYER_GOT_HIT,PlayerGotHit);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}


void HUDInputLayer::setButtonsState(bool state)
{
	mLeftButton->setEnabled(state);
	mRightButton->setEnabled(state);
	mPauseButton->setEnabled(state);
	mJumpButton->setEnabled(state);
}

void HUDInputLayer::setupButtonCallbacks()
{
	mLeftButton= static_cast<ui::Button*>(mCCScene->getChildByName("ButtonMoveLeft"));
	mLeftButton->addTouchEventListener(CC_CALLBACK_2(HUDInputLayer::leftButtonCallback, this));
	mRightButton = static_cast<ui::Button*>(mCCScene->getChildByName("ButtonMoveRight"));
	mRightButton->addTouchEventListener(CC_CALLBACK_2(HUDInputLayer::rightButtonCallback, this));
	mJumpButton = static_cast<ui::Button*>(mCCScene->getChildByName("ButtonJump"));
	mJumpButton->addTouchEventListener(CC_CALLBACK_2(HUDInputLayer::crossButtonCallback, this));
	mPauseButton = static_cast<ui::Button*>(mCCScene->getChildByName("ButtonPause"));
	mPauseButton->addTouchEventListener(CC_CALLBACK_2(HUDInputLayer::pauseButtonCallback, this));
}

void HUDInputLayer::setupLabel(){
    mTimer = Label::create();
    mTimer->setString("0.0");
    mTimer->setColor(Color3B::RED);
    mTimer->setPosition(Vec2(420,720));
    this->addChild(mTimer);
    
    mScore = Label::create();
    mScore->setString("0");
    mScore->setColor(Color3B::RED);
    mScore->setPosition(Vec2(420,700));
    this->addChild(mScore);
    
}

void HUDInputLayer::createHealthBar()
{
	auto pos = mCCScene->getChildByName("HealthBarPos")->getPosition();
	mHealthBar = ui::LoadingBar::create("player/health bar.png");
	mHealthBar->setPosition(pos);
	mHealthBar->setDirection(ui::LoadingBar::Direction::LEFT);
	mHealthBar->setScale(2.0);
	this->addChild(mHealthBar,10);
	mHealthBar->setPercent(mPlayer->getHealth());
}


void HUDInputLayer::leftButtonCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
            mInput = EINPUT::MoveLeft;
            mPrevInput = EINPUT::MoveLeft;
            mPlayer->handleInput(mInput);
            break;
	case ui::Widget::TouchEventType::ENDED:
            mInput = EINPUT::Idle;
            mPrevInput = EINPUT::Idle;
            mPlayer->handleInput(mInput);
            break;
	};
}

void HUDInputLayer::rightButtonCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
            mInput = EINPUT::MoveRight;
            mPrevInput = EINPUT::MoveRight;
            mPlayer->handleInput(mInput);
            break;
	case ui::Widget::TouchEventType::ENDED:
            mInput = EINPUT::Idle;
            mPrevInput = EINPUT::Idle;
            mPlayer->handleInput(mInput);
            break;
	};
}

void HUDInputLayer::crossButtonCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
            mInput = EINPUT::Jump;
            mPlayer->handleInput(mInput);
            break;
        case ui::Widget::TouchEventType::ENDED:
            mPlayer->handleInput(mPrevInput);
            break;
    };
    
}

void HUDInputLayer::pauseButtonCallback(cocos2d::Ref *, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		EventCustom event(Globals::EVENT_ADD_PAUSE_MENU);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}

void HUDInputLayer::onEnter()
{
	Layer::onEnter();
}

void HUDInputLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}

void HUDInputLayer::onExit()
{
	Layer::onExit();
}

void HUDInputLayer::onEventPlayerGotHit(cocos2d::EventCustom* mEvent)
{
	mHealthBar->setPercent(mPlayer->getHealth());
}


