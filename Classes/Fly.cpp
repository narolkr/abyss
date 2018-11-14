#include "Fly.hpp"
#include <cstdlib>
#include <cmath>

void Fly::move(Character *character,float delta){
    if(mFlyingDistance <= 0.0f){
        mFlyingDistance = 100.0f;
        if(mDir == EDIR::left){
            mDir = EDIR::right;
        }else{
            mDir = EDIR::left;
        }
    }
    
    float x1 = character->getPosition().x;
    
    character->getSprite()->setFlippedX(!mDir);
    
    if(mDir){
        character->setPositionX(character->getPosition().x + mSpeed*delta*1);
    }else{
        character->setPositionX(character->getPosition().x + mSpeed*delta*-1);
    }
    
    mTheta += (mMovementFrequency*delta);
    character->setPositionY(character->getPosition().y+ mMovementAmplitude*sin(mTheta));
    
    
    float x2 = character->getPosition().x;
    
    float deltaPos = abs(x2-x1);
    
    mFlyingDistance -= deltaPos;
}
