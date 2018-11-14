#ifndef _INC_MAIN_GAME_SCENE_H_
#define _INC_MAIN_GAME_SCENE_H_


#include"cocos2d.h"
#include <ctime>


//forward declarations to reduce compilation time and avoid cyclic dependecies
class HUDInputLayer;
class GameLayer;
class PauseLayer;
class Player;
class TMXLevel;
class GameOverLayer;


class MainGameScene : cocos2d::Scene
{
public:

	static MainGameScene * getInstance();
	MainGameScene();
	static cocos2d::Scene* createScene();

	bool init()override;
	void onEnter()override;
	void onEnterTransitionDidFinish()override;
	void onExit()override;
    void update(float delta) override;

	void loadAssets();
	void addLayers();
	void initObjects();

	//getters

	void buttonCallback(cocos2d::Ref*);

	void setEventCallbacks();

	//event callbacks
	void onEventRemovePauseLayer(cocos2d::EventCustom* pEvent);
	void onEventAddPauseLayer(cocos2d::EventCustom* pEvent);
	void onEventExitToMenu(cocos2d::EventCustom* pEvent);
	void onEventBossArea(cocos2d::EventCustom* pEvent);
	void onEventLevelClear(cocos2d::EventCustom* pEvent);
    void onEventAddGameOverLayer(cocos2d::EventCustom* pEvent);
    void onEventPlayAgain(cocos2d::EventCustom* pEvent);
    
    void setTimer(float time){
        mTimer = time;
    }
    float getTimer(){
        return mTimer;
    }
    
    void setScore(int score){
        mScore = score;
    }
    int getScore(){
        return mScore;
    }

	CREATE_FUNC(MainGameScene)

public:
	//Layers
	HUDInputLayer * mHUDInputLayer;
	GameLayer* mGameLayer;
	//Objects
	Player* mPlayer;
	//utilities
	cocos2d::SpriteFrameCache* mFrameCacheInst;
	PauseLayer* mPauseLayer;
    GameOverLayer* mGameOverLayer;
	static MainGameScene* mInstance;
    std::time_t mTimer;
    std::time_t mCurrentTime;
    int mScore;
};



#endif
