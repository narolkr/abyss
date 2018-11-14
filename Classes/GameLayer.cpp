#include"GameLayer.h"
#include"TMXLevel.h"
#include"Player.hpp"
#include"Animator.h"

using namespace cocos2d;

GameLayer::GameLayer() : mPlayer(nullptr), mLevel(nullptr)
{

}

GameLayer::GameLayer(Player* pPlayer) : mPlayer(pPlayer), mLevel(nullptr)
{
	
}


Node* GameLayer::getPlayerNode()
{
	return mPlayer;
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		CCLOG("failed to initialize the scene");
		return false;
	}

	mShakeTime = .3f;
	mShakeElapsed = 0.0f;
	initObjects();
	loadLevel();
    loadAudio();
	setCamera();
	setEventCallbacks();

	scheduleUpdate();

	mLayerPosition = this->getPosition();

	return true;
}



void GameLayer::update(float dt)
{
	if (mShaking)
	{
		mShakeElapsed += dt;
		if (mShakeElapsed > mShakeTime)
		{
			auto scheduler = Director::getInstance()->getScheduler();
			scheduler->unschedule(SEL_SCHEDULE(&GameLayer::shakeScreen),this);
			mShaking = false;
			mShakeElapsed = 0.0f;
			Globals::GameData::isScreenShaking = false;
		}
	}
}

void GameLayer::setEventCallbacks()
{
	auto onSpawnOrientedExplosion = CC_CALLBACK_1(GameLayer::onEventSpawnOrientedExplosion, this);
	auto listener1 = EventListenerCustom::create(Globals::EVENT_SPAWN_ORIENTED_EXPLOSION, onSpawnOrientedExplosion);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);

	auto onSpawnExplosion = CC_CALLBACK_1(GameLayer::onEventSpawnExplosion, this);
	auto listener2 = EventListenerCustom::create(Globals::EVENT_SPAWN_EXPLOSION, onSpawnExplosion);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, this);

	auto onShakeScreen = CC_CALLBACK_1(GameLayer::onEventShakeScreen, this);
	auto listener3 = EventListenerCustom::create(Globals::EVENT_SHAKE_SCREEN, onShakeScreen);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener3, this);
}


void GameLayer::onEventShakeScreen(cocos2d::EventCustom* cEvent)
{
	mShaking = true;
	Globals::GameData::isScreenShaking = true;
	auto scheduler = Director::getInstance()->getScheduler();
	scheduler->schedule(SEL_SCHEDULE(&GameLayer::shakeScreen),this,.1f,false);
}

void GameLayer::shakeScreen(float dt)
{
	float randX = cocos2d::random<int>(-70.0f,70.0f);
	float randY = cocos2d::random<int>(-70.0f, 70.0f);

	auto action = MoveBy::create(.2,Vec2(randX,randY));
	this->runAction(action);
}

void GameLayer::loadLevel()
{
    mLevel = new TMXLevel(this,"tilemaps/Jungle/Grassland.tmx");
	this->addChild(mLevel);
	this->addChild(mPlayer);
	auto playerPosition = mLevel->getPlayerPosition();
	mPlayer->setPosition(playerPosition);
}

void GameLayer::loadAudio(){
    //load BGM and sound effects for GrasslandLevel
    mAudio = CocosDenshion::SimpleAudioEngine::getInstance();
    mAudio->preloadBackgroundMusic("Music/Grassland.wav");
    mAudio->preloadEffect("Sounds/creeper_attack.wav");
    mAudio->preloadEffect("Sounds/flyer_attack.wav");
    mAudio->preloadEffect("Sounds/player_attack.wav");
    mAudio->playBackgroundMusic("Music/Grassland.wav");
}

void GameLayer::setCamera()
{
	float x1 = 0.0f;
	float y1 = -150;
	float x2 = mLevel->getMapWidth() * mLevel->getTileWidth();
	float y2 = mLevel->getMapHeight() * mLevel->getTileHeight() + 400;
	auto followPlayerAction = Follow::create(mPlayer, Rect(x1,y1,x2,y2));
	this->runAction(followPlayerAction);

	Globals::GameData::levelX1 = x1;
	Globals::GameData::levelY1 = y1;
	Globals::GameData::levelX2 = x2;
	Globals::GameData::levelY2 = y2;
}


void GameLayer::initObjects()
{
	mAnimator = new Animator();
	mAnimator->addAnimation("explosion",8);
	mAnimator->addAnimation("orien_explosion", 10);
}

void GameLayer::onEnter()
{
	Layer::onEnter();
}


void GameLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}


void GameLayer::onExit()
{
	Layer::onExit();
}


void GameLayer::onEventSpawnOrientedExplosion(cocos2d::EventCustom * mData)
{
	auto data = static_cast<Vec4*>(mData->getUserData());
	auto sprite = Sprite::create();

	auto position = Vec2(data->x,data->y);
	auto direction = Vec2(data->z,data->w);
	sprite->setPosition(position);
	if (direction.dot(Vec2(1.0f, 0.0f)) > 0.0f)
		sprite->setRotation(90.0f);
	else
		sprite->setRotation(-90.0f);
	this->addChild(sprite,100);
	mAnimator->playEffect(sprite, "orien_explosion");
}

void GameLayer::onEventSpawnExplosion(cocos2d::EventCustom * mData)
{
	auto position = static_cast<Vec2*>(mData->getUserData());
	auto sprite = Sprite::create();;
	sprite->setPosition(*position);
	this->addChild(sprite, 100);
	mAnimator->playEffect(sprite, "explosion");
}
