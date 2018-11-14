#ifndef Movement_h
#define Movement_h

#include "Character.hpp"

class Movement{    
public:
    enum EDIR{
        right = 0,
        left = 1,
    };
    
    EDIR mDir;
    virtual void move(Character *character,float delta){}
    void setSpeed(float speed){
        mSpeed = speed;
    }
    
    void flip(Character *character){
        if(mDir == EDIR::left){
            mDir = EDIR::right;
        }else{
            mDir = EDIR::left;
        }
        character->getSprite()->setFlippedX(mDir);
    }
    
protected:
    float mSpeed;
};

#endif /* Movement_h */
