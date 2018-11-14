#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"

class GameOverLayer : public cocos2d::Layer{
public:
    bool init() override;
    void onEnter() override;
    void onEnterTransitionDidFinish() override;
    void onExit() override;
    
    void loadScene();
    void setupButtonCallbacks();
    
    void restartButtonCallback();
    void menuButtonCallback();
    
    CREATE_FUNC(GameOverLayer);
    
private:
    cocos2d::Scene* mCCScene;
};
#endif /* GameOverLayer_hpp */
