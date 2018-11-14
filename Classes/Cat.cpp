#include "Cat.hpp"
#include "RunState.h"
#include "Walk.hpp"
#include "Movement.hpp"
#include"Animator.h"

bool Cat::init(){
    
	Enemy::init();
    mMoveType = new Walk();
    mMoveType->setSpeed(30.0f);
    mMoveType->mDir = Movement::EDIR::right;
    mDamagePer = -10.0f;
    mScaleFactor = 3.0;
    mAudioPath = "Sounds/meow.wav";
    this->setTag(generateTag());
    this->createBody("Enemies/Cat/cat_walk0.png");

	mAnimator = new Animator();
    mAnimNames[EAnimIDs::RUN]= "cat_walk";
    mAnimNames[EAnimIDs::DEATH] = "cat_dead";
    mAnimNames[EAnimIDs::ATTACK]="cat_attack";
    mAnimator->addAnimation(mAnimNames[EAnimIDs::RUN],4);
    mAnimator->addAnimation(mAnimNames[EAnimIDs::DEATH],5);
    mAnimator->addAnimation(mAnimNames[EAnimIDs::ATTACK],5,0.2f);
    mState = new RunState();
    mState->enter(this);
    return true;

}
