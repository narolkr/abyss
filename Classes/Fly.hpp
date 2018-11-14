#ifndef Fly_hpp
#define Fly_hpp

#include "Movement.hpp"

class Fly:public Movement{
public:
    
    Fly(float flyingDistance=0.0f, float theta=0.0f, float movementAmplitude=0.0f, float movementFrequency=0.0f){
        mFlyingDistance = flyingDistance;
        mTheta = theta;
        mMovementAmplitude = movementAmplitude;
        mMovementFrequency = movementFrequency;
    }
    
    void move(Character *character,float delta) override;
    
private:
    float mFlyingDistance;
    float mTheta;
    float mMovementAmplitude;       //more the value, the more distance it will oscillate
    float mMovementFrequency;       //more the value, faster will oscillate
};

#endif /* Fly_hpp */
