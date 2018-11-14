#ifndef _INC_PAUSE_LAYER_H_
#define _INC_PAUSE_LAYER_H_

#include"cocos2d.h"
#include"cocos/ui/CocosGUI.h"

class PauseLayer : public cocos2d::Layer
{
public:
	PauseLayer();
	bool init()override;
	void onEnter()override;
	void onEnterTransitionDidFinish()override;
	void onExit()override;

	void loadScene();
	void setupButtonCallbacks();

	void resumeButtonCallback();
	void exitButtonCallback();

	CREATE_FUNC(PauseLayer);

private:
	cocos2d::Scene* mCCScene;	
};

#endif