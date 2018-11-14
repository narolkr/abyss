#ifndef _INC_ANIMATOR_H_
#define _INC_ANIMATOR_H_

#include<map>
#include"cocos2d.h"

class Animator
{
public:
	Animator();
	~Animator();
	void addAnimation(const std::string& name,  int numberOfAnimations,float DelayPerUnit = 0.1f);
	void playAnimation(cocos2d::Sprite* sprite, const std::string& name,bool repeatForever = true);
	void playEffect(cocos2d::Sprite* sprite,const std::string& name);
	float getDuration(const std::string& name);
private:
	std::map<std::string, cocos2d::Animate*> mAnimations;
	std::map<std::string, float> mDurations;
	cocos2d::SpriteFrameCache* mFrameCache;
    float mAnimationSpeed;
};

#endif
