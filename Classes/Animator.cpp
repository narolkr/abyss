#include"Animator.h"
#include<sstream>

using namespace cocos2d;
using namespace std;

Animator::Animator() 
{
	mFrameCache = SpriteFrameCache::getInstance();
}

Animator::~Animator()
{

}

void Animator::addAnimation(const std::string & name, int numberOfAnimations,float delayPerUnit)
{
	std::string extension = ".png";
	Animate* animateAction;
	string spriteName = name;
	cocos2d::SpriteFrame* spriteFrame = nullptr;
	Animation* animation = Animation::create();
	for (int index = 0; index < numberOfAnimations; ++index)
	{
        stringstream ss;
		ss<<index;
		spriteName = name + ss.str() + extension;
		spriteFrame = mFrameCache->getSpriteFrameByName(spriteName);
		animation->addSpriteFrame(spriteFrame);
        spriteName.clear();
        ss.str("");
	}
	
	animation->setDelayPerUnit(delayPerUnit);
	animateAction = Animate::create(animation);
	animateAction->retain();
	mAnimations[name] = animateAction;
	mDurations[name] = delayPerUnit * numberOfAnimations;
}

void Animator::playAnimation(cocos2d::Sprite* sprite,const std::string & name,bool repeatForever)
{
	sprite->stopAllActions();
	if (repeatForever)
		sprite->runAction(RepeatForever::create(mAnimations[name]));
	else
		sprite->runAction(mAnimations[name]);    
}

void Animator::playEffect(cocos2d::Sprite* sprite, const std::string& name)
{
	auto seq = Sequence::create(mAnimations[name],RemoveSelf::create(),nullptr);
	sprite->runAction(seq);
}

float Animator::getDuration(const std::string & name) 
{
	return mDurations[name];
}


