#include "PickUp.hpp"
//ß#include "CCParticleSystem.h"

using namespace cocos2d;

unsigned int PickUp::mStaticTag = Globals::TAG_PICKUP_START;

PickUp::PickUp()
{
    
}


PickUp::~PickUp()
{
    
}

bool PickUp::init()
{
    Actor::init();
	return true;
}

unsigned int PickUp::generateTag(){
    unsigned int tag = mStaticTag;
    mStaticTag += 1;
    return tag;
}

void PickUp::createBody(){
    //adding sprite
    this->mSprite = Sprite::create(mSpritePath);
    this->addChild(this->mSprite);
    this->mSprite->setPosition(Vec2(0,0));
    this->mSprite->setScale(mScaleFactor,mScaleFactor);
    
    //adding physicsbody for collision
    auto physicsBody = PhysicsBody::create();
    physicsBody = PhysicsBody::createBox(this->getSize(),PhysicsMaterial(0.5f, 0.0f, 0.5f));
    physicsBody->setContactTestBitmask(0xFFFFFFFF);
    physicsBody->setCategoryBitmask(0x01);
    physicsBody->setCollisionBitmask(0x02);
    physicsBody->setDynamic(false);
    this->addComponent(physicsBody);
    
    //adding particles
    ParticleSystemQuad *effects = ParticleSystemQuad::create(mParticlePath);
    effects->setPosition(Vec2(0.0f,0.0f));
    addChild(effects,100);
    
    //contact Listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(PickUp::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool PickUp::onContactBegin(PhysicsContact& contact){
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    if (!nodeA && !nodeB) return false;
    
    if(nodeA->getTag() == Globals::TAG_PLAYER && nodeB->getTag() == getTag()){
        this->effectsOnPlayer((Player*) nodeA);
    }
    else if(nodeB->getTag() == Globals::TAG_PLAYER && nodeA->getTag() == getTag()){
        this->effectsOnPlayer((Player*) nodeB);
    }
    
    return true;
}

void PickUp::effectsOnPlayer(Player *player)
{
    
}
