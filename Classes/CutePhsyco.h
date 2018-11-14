#ifndef _INC_CUTE_PHSYCO_H_
#define _INC_CUTE_PHSYCO_H_

#include"Enemy.h"

class CutePhysco : public Enemy
{
public:
	bool init()override;
	void update(float delta)override;
	inline void setTargetNode(cocos2d::Node* pTargetNode) 
	{
		mTargetNode = pTargetNode;
	}
	void transform();
	void checkForTarget();

	void onCollisionBegin(int,int)override;

	CREATE_FUNC(CutePhysco);
	
private:
	bool mTransformed;;
	cocos2d::Node* mTargetNode;
};


#endif