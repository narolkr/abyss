#include "IdleState.h"
#include "RunState.h"
#include "JumpState.h"
#include "DeadState.h"
#include "AttackState.h"
#include "Globals.h"

CharacterState* IdleState::handleInput(int inputId){
    mCharacter->mPrevInputID = Globals::INPUT_IDEAL_STATE;
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
    if(inputId == 4){
        return new AttackState();
    }
    if(inputId == 5){
        return new DeadState();
    }
    return NULL;
}

void IdleState::update(float delta){
    //character->getPhysicsBody()->setVelocity(cocos2d::Vec2(0,character->getPhysicsBody()->getVelocity().y));
}
    
void IdleState::enter(Character* character){
	mCharacter = character;
	mCharacter->playAnimation(EAnimIDs::IDLE);
}

