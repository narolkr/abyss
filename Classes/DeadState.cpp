#include <stdio.h>
#include "DeadState.h"
#include "RunState.h"
#include "JumpState.h"
#include "IdleState.h"
#include "Enemy.h"
#include "Globals.h"
#include"Animator.h"

using namespace cocos2d;

CharacterState* DeadState::handleInput(int inputId){
    //no state should transition if the character is dying
    return nullptr;
}

void DeadState::enter(Character* character){
    
	mCharacter = character;

    cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
	auto animator = character->getAnimator();
    if (mCharacter->getTag() != Globals::TAG_PLAYER)
    {
        auto removeCollAction = CallFunc::create([=]()
                                                 {
                                                     mCharacter->removeComponent(mCharacter->getPhysicsBody());
                                                 });
        actions.pushBack(removeCollAction);
    }
	if (animator)
	{
		auto playAnimation = cocos2d::CallFunc::create([=]()
		{
			character->playAnimation(EAnimIDs::DEATH);
		});
		actions.pushBack(playAnimation);

		std::string animString = character->getAnimString(EAnimIDs::DEATH);
		if (!animString.empty())
		{
			float animTime = animator->getDuration(animString);
			auto delayAction = cocos2d::DelayTime::create(animTime);
			actions.pushBack(delayAction);
		}
	}
	
	if (mCharacter->getTag() == Globals::TAG_PLAYER)
	{
		auto gameOverFunc = [=]()
		{
			cocos2d::EventCustom event(Globals::EVENT_GAME_OVER_MENU);
			cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
		};

		auto gameOverAction = CallFunc::create(gameOverFunc);
		actions.pushBack(gameOverAction);
    }
	actions.pushBack(cocos2d::RemoveSelf::create());
	
	auto sequence = cocos2d::Sequence::create(actions);

    character->runAction(sequence);
}

void DeadState::update(float delta){
    
}
