#pragma once
#include"cocos2d.h"

class MainMenu : cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	bool init()override;
	void onEnter()override;
	void onEnterTransitionDidFinish()override;
	void onExit()override;

	//touch callbacks
	bool onTouchBegan(cocos2d::Touch* pTouch,cocos2d::Event* pEvent);

	void setTouchCallbacks();
	void setButtonsCallbacks();

	void onPlayButtonPressed(cocos2d::Ref*);

	static cocos2d::Scene* mCCScene;

	CREATE_FUNC(MainMenu);
};

