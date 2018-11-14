#ifndef DeadState_h
#define DeadState_h

#include "CharacterState.h"

class DeadState : public CharacterState{
public:
    CharacterState* handleInput(int inputId);
    void enter(Character* character);
    void update(float delta);
};
#endif /* DeadState_h */
