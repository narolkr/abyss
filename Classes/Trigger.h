#ifndef _INC_TRIGGER_H_
#define _INC_TRIGGER_H_

#include"cocos2d.h"
#include<string>

class Trigger : public cocos2d::Node
{
public:
	bool init()override;
	void update(float)override;

	inline void setEventID(const std::string& pEventID) { mEventID = pEventID; }
	inline std::string getEventID() { return mEventID; }
	inline void setShouldTriggerOnce(bool val) { mShouldTriggerOnce = val; }
	inline bool getShouldTriggerOnce() { return mShouldTriggerOnce; }

	bool onContactBegin(cocos2d::PhysicsContact& contact);
	
	CREATE_FUNC(Trigger);
private:
	
	std::string mEventID;
	static unsigned triggerCount;
	bool mShouldTriggerOnce;
};

#endif
