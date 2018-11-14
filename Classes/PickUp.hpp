#ifndef PickUp_hpp
#define PickUp_hpp
#include "Actor.hpp"
#include "Player.hpp"

class PickUp: public Actor{
public:
    PickUp();
    virtual ~PickUp();
    bool init()override;
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    virtual void effectsOnPlayer(Player *player);
    void createBody();
    static void resetStaticPickUpTag(){
        mStaticTag = Globals::TAG_PICKUP_START;
    }
    
protected:
    Player *mPlayer;
    std::string mSpritePath;
    std::string mParticlePath;
    static unsigned int mStaticTag;
    unsigned int generateTag();
    
};

#endif /* PickUp_hpp */
