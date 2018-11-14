//Attack State is only for Enemies

#ifndef AttackState_h
#define AttackState_h

#include "CharacterState.h"
#include <ctime>

class Character;

class AttackState:public CharacterState{
public:    
    CharacterState* handleInput(int inputId)override;
    void update(float delta)override;
    void enter(Character* character);
private:
    bool mAttacking = true;
    time_t t1;
    time_t t2;
    Character* mTarget;
};


#endif /* AttackState_h */
