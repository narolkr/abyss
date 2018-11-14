#include "JumpState.h"
#include "RunState.h"
#include "IdleState.h"
#include "DeadState.h"
#include "AttackState.h"
#include "Globals.h"

CharacterState* JumpState::handleInput(int inputId){
    mCharacter->mPrevInputID = Globals::INPUT_JUMP_STATE;
    if(inputId == 0){
		mCharacter->mMoveType->mDir = Movement::EDIR::right;
        return  new RunState();
    }
    if(inputId == 1){
        mCharacter->mMoveType->mDir = Movement::EDIR::left;
        return  new RunState();
    }
    if(inputId == 3){
        return new IdleState();
    }
    if(inputId == 4){
        return new AttackState();
    }
    if(inputId == 5){
        return new DeadState();
    }
    return NULL;
}
    
void JumpState::enter(Character* character){    
	mCharacter = character;
}
    
		

void JumpState::update(float delta){
    if(mCharacter->mPrevInputID != Globals::INPUT_IDEAL_STATE){
        mCharacter->mMoveType->move(mCharacter,delta);
    }
    if(mCharacter->mGrounded){
        mCharacter->getPhysicsBody()->applyImpulse(cocos2d::Vec2(0.0f,mCharacter->getJumpForce()));
        mCharacter->mGrounded = false;
		mCharacter->playAnimation(EAnimIDs::JUMP);
    }
}


    

