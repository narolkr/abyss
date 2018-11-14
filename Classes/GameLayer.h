#ifndef _INC_GAME_LAYER_H_
#define _INC_GAME_LAYER_H_

#include"cocos2d.h"
#include "SimpleAudioEngine.h"

#include"Trigger.h"

//forward declarations to eliminate compilation time
class TMXLevel;
class Player;

class GameLayer : public cocos2d::Layer
{
public:
	GameLayer();
	GameLayer(Player* pPlayer);
	bool init()override;
	void onEnter()override;
	void onEnterTransitionDidFinish()override;
	void onExit()override;
	void update(float) override;
	
	void setEventCallbacks();

	void loadLevel();
    void loadAudio();
	void setCamera();	
	void initObjects();
	void onEventSpawnOrientedExplosion(cocos2d::EventCustom* mData);
	void onEventSpawnExplosion(cocos2d::EventCustom* mData);

	cocos2d::Node* getPlayerNode();

	void onEventShakeScreen(cocos2d::EventCustom* cEvent);
	void shakeScreen(float dt);

	CREATE_FUNC(GameLayer);

private:
	TMXLevel * mLevel;
	Player* mPlayer;
    CocosDenshion::SimpleAudioEngine *mAudio;
	class Animator* mAnimator;

	float mShakeTime;
	bool mShaking;
	float mShakeElapsed;

	cocos2d::Vec2 mLayerPosition;
	cocos2d::Vector<cocos2d::FiniteTimeAction*> mShakeActions;
};

#endif
