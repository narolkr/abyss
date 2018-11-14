#include "Health.hpp"
#include "Globals.h"

USING_NS_CC;

bool Health::init(){
    
    PickUp::init();
    mHealthPointsPer = 20.0f;
    mScaleFactor = 3.5f;
    //mAudioPath = "Sounds/spike.wav";
    this->setTag(generateTag());
    mSpritePath = "pickUps/ChickenLeg.png";
    mParticlePath = "pickUps/Particles/chicken_particle.plist";
    this->createBody();
    return true;
    
}

void Health::effectsOnPlayer(Player* player){
    player->setHealthByPer(mHealthPointsPer);
    cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
    actions.pushBack(CallFunc::create([=](){
        this->removeFromParentAndCleanup(true);
    }));
    auto sequence = cocos2d::Sequence::create(actions);
    player->getSprite()->runAction(sequence);
}
