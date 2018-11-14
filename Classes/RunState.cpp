#include "RunState.h"
#include "JumpState.h"
#include "IdleState.h"
#include "DeadState.h"
#include "AttackState.h"
#include "Movement.hpp"
#include "Globals.h"

CharacterState* RunState::handleInput(int inputId){
    if(mCharacter->mMoveType->mDir){
        mCharacter->mPrevInputID = Globals::INPUT_LRUN_STATE;
    }else{
        mCharacter->mPrevInputID = Globals::INPUT_RRUN_STATE;
    }
    if(inputId == 2){
        return new JumpState();
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

void RunState::enter(Character* character){
	mCharacter = character;
    character->playAnimation(EAnimIDs::RUN);
}
    
void RunState::update(float delta){
    mCharacter->mMoveType->move(mCharacter,delta);
}
    


