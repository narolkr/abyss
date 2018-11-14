#ifndef _INC_HUD_INPUT_LAYER_H_
#define _INC_HUD_INPUT_LAYER_H_

#include"cocos2d.h"
#include"cocos/ui/CocosGUI.h"
#include "stdio.h"


class Player;

class HUDInputLayer : public cocos2d::Layer
{
public:	

	HUDInputLayer();
	HUDInputLayer(Player* pPlayer);
	bool init()override;
	void onEnter()override;
	void onEnterTransitionDidFinish()override;
	void onExit()override;

	void loadScene();
	void setupButtonCallbacks();
    void setupLabel();
	void setEventCallbacks();
	void createHealthBar();

	void onEventPlayerGotHit(cocos2d::EventCustom* pEvent);

	void leftButtonCallback(cocos2d::Ref*,cocos2d::ui::Widget::TouchEventType type);
	void rightButtonCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type);
	void crossButtonCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type);
	void pauseButtonCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type);

	void setButtonsState(bool state);
    
    cocos2d::Label* getTimerLabel(){
        return mTimer;
    }
    cocos2d::Label* getScoreLabel(){
        return mScore;
    }

	CREATE_FUNC(HUDInputLayer);
	

private:

	Player * mPlayer;
	cocos2d::Scene* mCCScene;

    enum EINPUT{        
        MoveRight,
        MoveLeft,
        Jump,
        Idle,
        Dead
    };
    
    EINPUT mInput;
    EINPUT mPrevInput;
	
	cocos2d::ui::LoadingBar* mHealthBar;

	cocos2d::ui::Button* mPauseButton;
	cocos2d::ui::Button* mLeftButton;
	cocos2d::ui::Button* mRightButton;
	cocos2d::ui::Button* mJumpButton;
    
    cocos2d::Label* mScore;
    cocos2d::Label* mTimer;
};

#endif
