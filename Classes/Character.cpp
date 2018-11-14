#include "Character.hpp"
#include "CharacterState.h"
#include "Movement.hpp"
#include"Animator.h"

bool Character::init()
{

	Actor::init();
	mAnimator = nullptr;
	mAnimNames.reserve(EAnimIDs::MAX);
	for (int count = 0 ; count < EAnimIDs::MAX ; ++count)
		mAnimNames.push_back("");
	return true;
}

void Character::onExit()
{
	Actor::onExit();

	if(mAnimator)
		delete mAnimator;
}

void Character::handleInput(int inputId)
{
    CharacterState* state_ = mState->handleInput(inputId);
    if(state_ != NULL){
        delete mState;
        mState = state_;
        mState->enter(this);
    }
}

void Character::playAnimation(EAnimIDs id,bool loop)
{
	if (!mAnimator) return;
	std::string animString = getAnimString(id);
	if (!animString.empty())
		mAnimator->playAnimation(mSprite, animString, loop);
}

float Character::getAnimDuration(EAnimIDs id)
{
	std::string animString = getAnimString(id);
	if (animString.empty())
		return 0.0f;
	else
		return mAnimator->getDuration(animString);
}
