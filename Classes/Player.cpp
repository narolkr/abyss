#include "Player.hpp"
#include "cocos2d.h"
#include "IdleState.h"
#include "SimpleAudioEngine.h"
#include "Walk.hpp"
#include "Movement.hpp"
#include"Globals.h"

USING_NS_CC;
using namespace Globals;

bool Player::init(){
    
	Character::init();
    //assigning default values
    mMoveType = new Walk();
    mMoveType->mDir = Movement::EDIR::right;
    mMoveType->setSpeed(200.0f);
    mTotalHealth = 100.0f;
    mJumpForce = 350000.0f;
    mCurrentHealth = mTotalHealth;
    
    mAudioPath = "Sounds/player_attack.wav";
    
    //setting Sprite
    mSprite = cocos2d::Sprite::create("player/player.png");
    this->addChild(mSprite);
    mSprite->setPosition(cocos2d::Vec2(0,0));
    
    //adding Physics Body
    auto playerPhysics = PhysicsBody::createBox(Size(30,38),PhysicsMaterial(1.0f, 0.0f, 1.0f));
    playerPhysics->setContactTestBitmask(0xFFFFFFFF);
    playerPhysics->setRotationEnable(false);
    playerPhysics->setPositionOffset(Vec2(-10,-5));
    playerPhysics->setCategoryBitmask(0x02);
    playerPhysics->setCollisionBitmask(0x01);
    this->addComponent(playerPhysics);
    this->getPhysicsBody()->getNode()->setTag(Globals::TAG_PLAYER);
    
    //adding collider for sword
    sword = Sprite::create();
    auto swordPhysics = PhysicsBody::createBox(Size(18.0f,10.0f),PhysicsMaterial(1.0f, 0.0f, 1.0f));
    swordPhysics->setContactTestBitmask(0xFFFFFFFF);
    swordPhysics->setRotationEnable(false);
    swordPhysics->setDynamic(false);
    sword->addComponent(swordPhysics);
    sword->getPhysicsBody()->getNode()->setTag(Globals::TAG_SWORD);
    this->addChild(sword);
    sword->setPosition(Vec2(14,-8));
    
    //collider Listener
    auto contactListener = cocos2d::EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Player::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
	mAnimator = new Animator();

    mAnimNames[EAnimIDs::RUN] = "run_";
    mAnimNames[EAnimIDs::IDLE] = "idle_";
    mAnimNames[EAnimIDs::DEATH] = "dead";
	mAnimNames[EAnimIDs::JUMP] = "jump_";
	mAnimator->addAnimation(mAnimNames[EAnimIDs::RUN],6);
	mAnimator->addAnimation(mAnimNames[EAnimIDs::IDLE], 4);
    mAnimator->addAnimation(mAnimNames[EAnimIDs::DEATH],12);
	mAnimator->addAnimation(mAnimNames[EAnimIDs::JUMP],4);
    mState = new IdleState();
    mState->enter(this);

    this->scheduleUpdate();
    
    return true;
}


void Player::loopPosition()
{
	auto pos = getPosition();
    float playerWidth = getSize().width;
	float playerHalfWidth = playerWidth / 2.0f;
	float levelMinWidth = Globals::GameData::levelX1;
	float levelMaxWidth = Globals::GameData::levelX2;

	if (pos.x + playerHalfWidth < levelMinWidth)
		this->setPositionX(levelMaxWidth);
	if ((pos.x - playerHalfWidth) > levelMaxWidth)
		this->setPositionX(levelMinWidth);
}

void Player::update(float delta){
    mState->update(delta);
    if(mMoveType->mDir){
        this->getPhysicsBody()->setPositionOffset(Vec2(10,-5));
        sword->setPosition(Vec2(-14,-8));
    }else{
        this->getPhysicsBody()->setPositionOffset(Vec2(-10,-5));
        sword->setPosition(Vec2(14,-8));
    }

	loopPosition();
}

bool Player::onContactBegin(PhysicsContact& contact){
	auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

	int tagA = nodeA->getTag();
	int tagB = nodeB->getTag();
    
    //grounded
    if((Globals::TAG_FLOOR == tagA && Globals::TAG_PLAYER == tagB) || (Globals::TAG_FLOOR == tagB && Globals::TAG_PLAYER == tagA)){
        mGrounded = true;
		return true;
    }
    
    //attacking enemy
	if ((Globals::TAG_SWORD == tagA && inEnemyRange(tagB)))
	{
		auto enemy = (Enemy*)nodeB;
		if(enemy->getCanBeKilled())
			this->attack(enemy);
		return true;
	}
	else if ((Globals::TAG_SWORD == tagB && inEnemyRange(tagA)))
	{
		auto enemy = (Enemy*)nodeA;
		if (enemy->getCanBeKilled())
			this->attack(enemy);
	}

	//checking for triggers
	if ((inTriggerRange(tagA) && Globals::TAG_PLAYER == tagB) || (inTriggerRange(tagB) && Globals::TAG_PLAYER == tagA))
		return false;

	
}

void Player::attack(Enemy* enemy){
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect(mAudioPath);
    mScore +=1;
    enemy->handleInput(Globals::INPUT_DEAD_STATE);
	
}

void Player::setHealthByPer(float percentage)
{
	Character::setHealthByPer(percentage);
    if(getHealth() <= 0.0f){
        handleInput(Globals::INPUT_DEAD_STATE);
    }
	EventCustom event(Globals::EVENT_PLAYER_GOT_HIT);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}
