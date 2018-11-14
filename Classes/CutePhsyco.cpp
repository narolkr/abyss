#include"CutePhsyco.h"
#include"Animator.h"
#include"Walk.hpp"
#include"RunState.h"
#include"Globals.h"
#include "SimpleAudioEngine.h"
#include"MainGameScene.h"
#include"Player.hpp"

using namespace cocos2d;

bool CutePhysco::init()
{
	Enemy::init();

	mSprite = Sprite::createWithSpriteFrameName("bomber_run0.png");
	this->addChild(mSprite);
	this->setScale(3.0f);
	auto physicsBody = cocos2d::PhysicsBody::createBox(this->getSize(), cocos2d::PhysicsMaterial(0.5f, 0.0f, 0.5f));
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	physicsBody->setCategoryBitmask(0x01);
	physicsBody->setCollisionBitmask(0x02);
	physicsBody->setRotationEnable(false);
	this->addComponent(physicsBody);
	this->setTag(generateTag());

	mAnimator = new Animator();

	mAudioPath = "Sounds/bomber_damage.wav";

	mAnimNames[EAnimIDs::RUN] = "bomber_run";
	mAnimNames[EAnimIDs::ATTACK] = "suicide_start";
	mAnimNames[EAnimIDs::ATTACK_LOOP] = "suicide_loop";

	mAnimator->addAnimation(mAnimNames[EAnimIDs::RUN],12,.02);
	mAnimator->addAnimation(mAnimNames[EAnimIDs::ATTACK],3,0.07);
	mAnimator->addAnimation(mAnimNames[EAnimIDs::ATTACK_LOOP],2);

	mMoveType = new Walk();
	mMoveType->setSpeed(100.0f);
	mMoveType->mDir = Movement::EDIR::left;
	
	mState = new RunState();
	mState->enter(this);

	mTransformed = false;

	mDamagePer = -50.0f;

	this->scheduleUpdate();

	return true;
}


void CutePhysco::onCollisionBegin(int tagA,int tagB)
{
	if ((tagA == Globals::TAG_WALL && tagB == getTag()) || (tagB == Globals::TAG_WALL && tagA == getTag()))
	{
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->playEffect(getAudioPath());
		this->runAction(RemoveSelf::create());

		Vec2 position = getPosition();
		Vec2 direction(-1.0f,0.0f);
		if (mMoveType->mDir == Movement::EDIR::left)
			direction.x = 1.0f;
		Vec4 data(position.x,position.y,direction.x,direction.y);
		EventCustom spawnEvent(Globals::EVENT_SPAWN_ORIENTED_EXPLOSION);
		spawnEvent.setUserData(&data);
		_eventDispatcher->dispatchEvent(&spawnEvent);
	}
}


void CutePhysco::transform()
{
	mTransformed = true;
	
	auto firstAnim = [=]() {playAnimation(EAnimIDs::ATTACK, false); };
	auto secondAnim = [=]() {playAnimation(EAnimIDs::ATTACK_LOOP); };
	auto increaseSpeed = [=]() 
	{
		mMoveType->setSpeed(300.0f); 
	};
	float firstAnimTime = getAnimDuration(EAnimIDs::ATTACK);
	float secondAnimTime = getAnimDuration(EAnimIDs::ATTACK_LOOP);

	auto action1 = CallFunc::create(firstAnim);
	auto action2 = CallFunc::create(increaseSpeed);
	auto action3 = CallFunc::create(secondAnim);

	auto seq = Sequence::create(action1,DelayTime::create(firstAnimTime),action2,action3,nullptr);
	this->runAction(seq);

	setBoundaryRestriction(false);
	mCanBeKilled = false;

}


void CutePhysco::checkForTarget()
{
	auto player = MainGameScene::getInstance()->mPlayer;
	if (!player)return;
	Vec2 toTarget = player->getPosition() - getPosition();
	toTarget.normalize();
	Vec2 currentDirection = Vec2(1.0f,0.0f);
	if (Movement::EDIR::left == mMoveType->mDir)
		currentDirection = Vec2(-1.0f,0.0f);
	float dot = toTarget.dot(currentDirection);
	dot -= .25;
	log("%f",dot);
	if (dot > .74000)
	{
		transform();
		getPhysicsBody()->setGravityEnable(false);
	}
}

void CutePhysco::update(float delta)
{
	mState->update(delta);
	if (!mTransformed)
		checkForTarget();
}
