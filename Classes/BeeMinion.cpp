#include "BeeMinion.hpp"
#include "RunState.h"
#include "Fly.hpp"
#include "Movement.hpp"
#include"Animator.h"

bool BeeMinion::init(){
    
	Enemy::init();

    mDamagePer = -10.0f;
    mMoveType = new Fly(200.0f,0.0f,1.5f,7.0f);
    mMoveType->setSpeed(20.0f);
    mMoveType->mDir = Movement::EDIR::right;  
    
    mScaleFactor = 2;
    mAudioPath = "Sounds/flyer_attack.wav";
    this->setTag(generateTag());
    this->createBody("Enemies/Flyer/flyer0.png");
    this->getPhysicsBody()->setDynamic(false);

	this->setTag(generateTag());

	mAnimator = new Animator();
    mAnimNames[EAnimIDs::RUN] = "flyer";
	mAnimNames[EAnimIDs::DEATH] = "flyerDying";
    mAnimator->addAnimation(mAnimNames[EAnimIDs::RUN],3);
    mAnimator->addAnimation(mAnimNames[EAnimIDs::DEATH],4);

    mState = new RunState();
    mState->enter(this);
    return true;
}
