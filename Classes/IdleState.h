#ifndef IdleState_h
#define IdleState_h
#include "CharacterState.h"

class IdleState: public CharacterState{

public:
  
    CharacterState* handleInput(int inputId);
    void update(float delta);    
    void enter(Character* character);
};
#endif /* IdleState_h */
