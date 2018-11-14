#include "GameOverLayer.hpp"
#include "reader/CreatorReader.h"
#include "Globals.h"

USING_NS_CC;

bool GameOverLayer::init(){
    if (!Layer::init())
    {
        CCLOG("failed to initialize PauseLayer");
        return false;
    }
    
    loadScene();
    setupButtonCallbacks();
    
    return true;
}

void GameOverLayer::loadScene(){
    auto reader = creator::CreatorReader::createWithFilename("creator/scenes/GameOverPopUp.ccreator");
    if (!reader)
    {
        CCLOG("PauseLayer reader == null");
        return ;
    }
    reader->setup();
    mCCScene = reader->getSceneGraph();
    this->addChild(mCCScene);
}

void GameOverLayer::setupButtonCallbacks(){
    auto ButtonPlayAgain = static_cast<ui::Button*>(mCCScene->getChildByName("PlayAgain"));
    ButtonPlayAgain->addClickEventListener(CC_CALLBACK_0(GameOverLayer::restartButtonCallback, this));
    
    auto ButtonMainMenu = static_cast<ui::Button*>(mCCScene->getChildByName("MainMenu"));
    ButtonMainMenu->addClickEventListener(CC_CALLBACK_0(GameOverLayer::menuButtonCallback, this));
}

void GameOverLayer::restartButtonCallback()
{
    EventCustom event(Globals::EVENT_PLAY_AGAIN_MENU);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void GameOverLayer::menuButtonCallback()
{
    EventCustom event(Globals::EVENT_EXIT_TO_MENU);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void GameOverLayer::onEnter()
{
    Layer::onEnter();
}

void GameOverLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}

void GameOverLayer::onExit()
{
    Layer::onExit();
}

