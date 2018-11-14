#ifndef JumpState_h
#define JumpState_h

#include "CharacterState.h"

class JumpState: public CharacterState{
public:
    CharacterState* handleInput(int inputId) override;
    void enter(Character* character) override;
    void update(float delta) override;
};
#endif /* JumpState_h */
