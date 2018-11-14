#ifndef Actor_hpp
#define Actor_hpp

#include "cocos2d.h"

class  Actor : public cocos2d::Node{
    
public:
    
    Actor(){}
    virtual ~Actor(){}
    
    cocos2d::Size getSize(){
        return mSprite->getBoundingBox().size;
    }

    cocos2d::Sprite* getSprite(){
        return mSprite;
    }

	bool init()override { cocos2d::Node::init(); return true; }

protected:
    
    cocos2d::Vec2 mPosition;
    cocos2d::Sprite *mSprite;
    float mScaleFactor;
    
};

#endif /* Actor_hpp */
