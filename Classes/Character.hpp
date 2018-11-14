#ifndef Character_hpp
#define Character_hpp

#include "Actor.hpp"
#include "stdio.h"
#include<vector>
#include<cassert>

class CharacterState;
class Movement;
class Animator;


enum EAnimIDs
{
	MIN = 0,
	IDLE ,
	RUN,
	JUMP,
	ATTACK,
	ATTACK_LOOP,
	DEATH,
	MAX
};

class Character: public Actor
{
public:
    bool mGrounded;
    Movement *mMoveType;    
	bool init()override;
	void onExit()override;
    void handleInput(int inputId);
    int mPrevInputID =3;

    Character(){}
    virtual ~Character(){}
    
    //getter setter
    float getHealth(){
        return mCurrentHealth;
    }

	void playAnimation(EAnimIDs id,bool loop = true);
	float getAnimDuration(EAnimIDs id);

    float getDamangePer(){
        return mDamagePer;
    }
        
    virtual void setHealthByPer(float percentage){
        if(mTotalHealth < mCurrentHealth +(mTotalHealth*(percentage/100.0f))){
            mCurrentHealth = mTotalHealth;
        }        
        else{
            mCurrentHealth += (mTotalHealth*(percentage/100.0f));
        }
        
    }
    
    Animator* getAnimator(){
        return mAnimator;
    }
        
    float getJumpForce(){
        return mJumpForce;
    }
    
    const char* getAudioPath(){
        return mAudioPath;
    }
    
    Character* getTarget(){
        return mTarget;
    }
    
    void setTarget(Character* target){
        mTarget = target;
    }

	inline Movement* getMoveType()
	{
		return mMoveType;
	}

	inline std::string getAnimString(EAnimIDs animID)
	{
		bool result = animID > EAnimIDs::MIN && animID < EAnimIDs::MAX;
		if (!result) 
		{
			cocos2d::log("Animation ID is out of limits");
			return "";
		}
		return mAnimNames[animID];
	}
    
protected:
    
	std::vector<std::string> mAnimNames;
    Animator* mAnimator;
    float mCurrentHealth;
    float mTotalHealth;
    float mDamagePer;
    float mJumpForce;
    CharacterState *mState;
    const char* mAudioPath;
    Character *mTarget;
};

#endif /* Character_hpp */


