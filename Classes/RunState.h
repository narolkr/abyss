#ifndef RunState_h
#define RunState_h

#include "CharacterState.h"

class RunState: public CharacterState{
    
public:
    
    CharacterState* handleInput(int inputId) override;
    void enter(Character* character) override;
    void update(float delta) override;
    
};
#endif /* RunState_h */
