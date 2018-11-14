#include "Trigger.h"
#include"Globals.h"

using namespace cocos2d;


unsigned Trigger::triggerCount = Globals::TAG_TRIGGER_START;

bool Trigger::init()
{
	Node::init();

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Trigger::onContactBegin,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	
	int tag = triggerCount;
	setTag(tag);
	triggerCount++;

	return true;
}

void Trigger::update(float)
{
}

bool Trigger::onContactBegin(cocos2d::PhysicsContact & contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if ((Globals::TAG_PLAYER == nodeA->getTag() && getTag() == nodeB->getTag()) || (Globals::TAG_PLAYER == nodeB->getTag() && getTag() == nodeA->getTag()) )
	{
		//int tag = getTag();
		cocos2d::EventCustom triggerEvent(mEventID);
		triggerEvent.setUserData(this);
		cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&triggerEvent);
		if(mShouldTriggerOnce)
			runAction(cocos2d::RemoveSelf::create(true));
		return false;
	}
	return true;
}


