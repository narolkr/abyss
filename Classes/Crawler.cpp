#include "Crawler.hpp"
#include "RunState.h"
#include "Walk.hpp"
#include "Movement.hpp"

bool Crawler::init(){
    
	Character::init();
    mMoveType = new Walk();
    mMoveType->setSpeed(20.0f);
    mMoveType->mDir = Movement::EDIR::right;
    mDamage = 10.0f;
    mScaleFactor = 2;
    mAudioPath = "Sounds/creeper_attack.wav";
    this->setTag(generateTag());
    this->createBody("Enemies/Crawler/crawler0.png");
    mRunAnimName = "crawler";
    mDyingAnimName = "crawlerDying";
    mAnimator.addAnimation(mRunAnimName,3);
    mAnimator.addAnimation(mDyingAnimName,4);
    mState = new RunState();
    mState->enter(this);
    return true;

}
