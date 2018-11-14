//
//  Player.hpp
//  abyss
//
//  Created by Longkumer, Narosenla on 05/06/18.
//

#ifndef Player_hpp
#define Player_hpp

#include "Character.hpp"
#include "Animator.h"
#include "CharacterState.h"
#include "Globals.h"
#include "Enemy.h"

class Player: public Character{
    
public:
    
    Player(){}
    ~Player(){}
    
    virtual bool init() override;

    virtual void setHealthByPer(float percentage) override;
	    
    void update(float delta) override;
    
	void loopPosition();
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void attack(Enemy* enemy);
    int getScore(){
        return mScore;
    }
    void setScore(int score){
        mScore = score;
    }
    
    
    CREATE_FUNC(Player);
    
private:    
    
    cocos2d::Sprite *sword;
    int mScore;
    
};

#endif /* Player_hpp */
