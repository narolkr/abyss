#ifndef CharacterState_h
#define CharacterState_h
#include "cocos2d.h"
#include "Character.hpp"
#include "Movement.hpp"

class CharacterState{
    
public:
    virtual ~CharacterState(){}
    virtual CharacterState* handleInput(int nextStateID)=0;
    virtual void update(float delta)=0;
    virtual void enter(Character* pCharacter)=0;
protected:
	Character * mCharacter;
};

#endif /* CharacterState_h */
