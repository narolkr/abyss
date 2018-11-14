#include "AttackState.h"
#include "IdleState.h"
#include "RunState.h"
#include "JumpState.h"
#include "DeadState.h"
#include "SimpleAudioEngine.h"
#include "Globals.h"

CharacterState* AttackState::handleInput(int inputId){
    mCharacter->mPrevInputID = Globals::INPUT_ATTACK_STATE;
    mTarget->getSprite()->runAction(cocos2d::TintTo::create(0.0f, 255.0f, 255.0f, 255.0f));
    if(inputId == 0){
        mCharacter->mMoveType->mDir = Movement::EDIR::right;
        return  new RunState();
    }
    if(inputId == 1){
        mCharacter->mMoveType->mDir = Movement::EDIR::left;
        return  new RunState();
    }
    if(inputId == 2){
        return new JumpState();
    }
    if(inputId == 3){
        return new IdleState();
    }
    if(inputId == 5){
        return new DeadState();
    }
    return NULL;
}

void AttackState::enter(Character* character){
	mCharacter = character;
    mAttacking = false;
    mTarget = character->getTarget();
	t1 = time(NULL);
}

void AttackState::update(float delta){
    if(mAttacking == false){
        t1 = time(NULL);        
        mAttacking = true;
        if(mTarget->getHealth()>0.0f){
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
            audio->playEffect(mCharacter->getAudioPath());
            auto action1 = cocos2d::TintTo::create(0.1f, 255.0f, 0.0f, 0.0f);
            auto action2 = cocos2d::TintTo::create(0.0f, 255.0f, 255.0f, 255.0f);
            auto sequence = cocos2d::Sequence::create(action1,action2, NULL);
            mTarget->getSprite()->runAction(sequence);
            mTarget->setHealthByPer(mCharacter->getDamangePer());
			mCharacter->playAnimation(EAnimIDs::ATTACK);
        }
    }
    t2 = time(NULL);
    if(difftime(t2, t1)>=1.0f){
        mAttacking=false;
    }
    
}
