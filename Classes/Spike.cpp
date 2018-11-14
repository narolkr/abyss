#include "Spike.h"
#include "IdleState.h"
#include "Globals.h"
#include"Animator.h"

USING_NS_CC;

bool Spike::init(){
    
	Enemy::init();

    mState = new IdleState();
    mState->enter(this);
    mDamagePer = -10.0f;
    mScaleFactor = 0.8f;
    mAudioPath = "Sounds/spike.wav";
    this->setTag(Globals::TAG_SPIKE);
    this->createBody("Enemies/Cactus/cactus0.png");
    this->getPhysicsBody()->setDynamic(false);

	mAnimator = new Animator();
    mAnimNames[EAnimIDs::IDLE] = "cactus";
    mAnimator->addAnimation(mAnimNames[EAnimIDs::IDLE],5);
    mState = new IdleState();
    mState->enter(this);
    return true;
    
}
