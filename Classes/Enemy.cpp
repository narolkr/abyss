#include "Enemy.h"
#include "Player.hpp"
#include "SimpleAudioEngine.h"
#include "AttackState.h"
#include "RunState.h"
#include "IdleState.h"

using namespace Globals;
using namespace cocos2d;

unsigned int Enemy::mStaticTag = Globals::TAG_ENEMY_START;


bool Enemy::init()
{
	Character::init();

	setCollisionListeners();
	mRestricted = true;
	mDestroyOnCollision = false;
	mCanBeKilled = true;

	return true;
}
void Enemy::createBody(std::string path){
    
    this->mSprite = cocos2d::Sprite::create(path);
    this->addChild(this->mSprite);
    this->mSprite->setPosition(cocos2d::Vec2(0,0));
    this->mSprite->setScale(mScaleFactor,mScaleFactor);
    
    auto physicsBody = cocos2d::PhysicsBody::create();
    if(this->getTag() == Globals::TAG_SPIKE){
        physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(getSize().width-5.0f,5.0f),cocos2d::PhysicsMaterial(0.5f, 0.0f, 0.5f));
        physicsBody->setPositionOffset(cocos2d::Vec2(0.0f,4.0f));
    }else{
        physicsBody = cocos2d::PhysicsBody::createBox(this->getSize(),cocos2d::PhysicsMaterial(0.5f, 0.0f, 0.5f));
    }
    physicsBody->setContactTestBitmask(0xFFFFFFFF);
    physicsBody->setCategoryBitmask(0x01);
    physicsBody->setCollisionBitmask(0x02);
    physicsBody->setRotationEnable(false);
    this->addComponent(physicsBody);
 
}

void Enemy::setCollisionListeners()
{
	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Enemy::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(Enemy::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void Enemy::update(float delta){
    mState->update(delta);
}

void Enemy::attack(Player *player){
    this->setTarget(player);
    this->handleInput(Globals::INPUT_ATTACK_STATE);
}


bool Enemy::onContactBegin(cocos2d::PhysicsContact& contact){
    auto nodeA = contact.getShapeA()->getBody()->getNode();    
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    Player *player = NULL;

	if (!nodeA && !nodeB) return false;

	int tagA = nodeA->getTag();
	int tagB = nodeB->getTag();

    //attacking player
    if(nodeA->getTag() == Globals::TAG_PLAYER && nodeB->getTag() == getTag()){
        player = (Player*) nodeA;
    }else if(nodeB->getTag() == Globals::TAG_PLAYER && nodeA->getTag() == getTag()){
        player = (Player*) nodeB;
    }
    if(player!=NULL)
	{       
		if (!GameData::isScreenShaking)
		{
			EventCustom shakeEvent(Globals::EVENT_SHAKE_SCREEN);
			_eventDispatcher->dispatchEvent(&shakeEvent);
		}

		if(!mDestroyOnCollision)
			this->attack(player);
		else
		{
			auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
			audio->playEffect(getAudioPath());
			auto action1 = cocos2d::TintTo::create(0.2f, 255.0f, 0.0f, 0.0f);
			auto action2 = cocos2d::TintTo::create(0.0f, 255.0f, 255.0f, 255.0f);
			auto sequence = cocos2d::Sequence::create(action1, action2, NULL);
			player->getSprite()->runAction(sequence);
			player->setHealthByPer(getDamangePer());
			this->runAction(cocos2d::RemoveSelf::create());

			Vec2 position = getPosition();
			EventCustom spawnEvent(Globals::EVENT_SPAWN_EXPLOSION);
			spawnEvent.setUserData(&position);
			_eventDispatcher->dispatchEvent(&spawnEvent);
		}
    }
    
    if((nodeA->getTag() == Globals::TAG_ENEMY_BOUNDARY && nodeB->getTag() == getTag()) || (nodeB->getTag() == Globals::TAG_ENEMY_BOUNDARY && nodeA->getTag() == getTag())){
		if (mRestricted)
			mMoveType->flip(this);
    }
    
	onCollisionBegin(tagA, tagB);

    return true;
}

void Enemy::onContactSeparate(cocos2d::PhysicsContact& contact){
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (!nodeA || !nodeB) return;

    if((nodeB->getTag() == Globals::TAG_PLAYER && nodeA->getTag() == Globals::TAG_SPIKE) || (nodeA->getTag() == Globals::TAG_PLAYER &&nodeB->getTag() == Globals::TAG_SPIKE)){
		this->handleInput(Globals::INPUT_IDEAL_STATE);
    }
    else if((nodeA->getTag() == Globals::TAG_PLAYER && inEnemyRange(getTag())) ||(nodeB->getTag() == Globals::TAG_PLAYER && inEnemyRange(getTag()))){
        this->handleInput(mMoveType->mDir);
    }
}
