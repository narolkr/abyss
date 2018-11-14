#include "Character.hpp"
#include "Globals.h"

#ifndef Enemy_h
#define Enemy_h

class Player;

class Enemy: public Character{

public:    

	bool init()override;
    void createBody(std::string path);
    void update(float) override;
    void attack(Player *player);

	void setCollisionListeners();

    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void onContactSeparate(cocos2d::PhysicsContact& contact);
    
    static void resetStaticEnemyTag(){
        mStaticTag = Globals::TAG_ENEMY_START;
    }

	inline float getSpotDistance(){
		return mSpotDistance;
	}
    
	inline void setBoundaryRestriction(bool value)
	{
		mRestricted = value;
	}

	inline bool getCanBeKilled()
	{
		return mCanBeKilled;
	}

	inline void setDestroyOnCollision(bool value)
	{
		mDestroyOnCollision = value;
	}

	virtual void onCollisionBegin(int tagA,int tagB) {}
    
protected:   
    
    float mSpotDistance;
    static unsigned int mStaticTag;
	bool mRestricted;
	bool mDestroyOnCollision;
	bool mCanBeKilled;
    
    unsigned int generateTag(){
        unsigned int tag = mStaticTag;
        mStaticTag += 1;
        return tag;
    }    
    
};
#endif /* Enemy_h */
