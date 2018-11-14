#include "MainMenu.h"
#include "reader/CreatorReader.h"
#include"MainGameScene.h"

using namespace cocos2d;

Scene* MainMenu::mCCScene = nullptr;

cocos2d::Scene * MainMenu::createScene()
{
	creator::CreatorReader* reader = creator::CreatorReader::createWithFilename("creator/scenes/MainMenuScene.ccreator");
	if (!reader)
	{
		CCLOG("failed to load cocos creator scene");
		return nullptr;
	}
	reader->setup();
	mCCScene = reader->getSceneGraph();
	auto layer = MainMenu::create();
	mCCScene->addChild(layer);
	return mCCScene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		CCLOG("failed to initialize Layer in Main Menu Scene");
		return false;
	}
	return true;
}

void MainMenu::onEnter()
{
	Layer::onEnter();

	setTouchCallbacks();
	setButtonsCallbacks();
}

void MainMenu::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}

void MainMenu::onExit()
{
	Layer::onExit();
}

bool MainMenu::onTouchBegan(cocos2d::Touch * pTouch, cocos2d::Event * pEvent)
{
	return true;
}

void MainMenu::setTouchCallbacks()
{

}

void MainMenu::setButtonsCallbacks()
{
	auto PlayButton = static_cast<ui::Button*>(mCCScene->getChildByName("ButtonPlay"));
	PlayButton->addClickEventListener(CC_CALLBACK_1(MainMenu::onPlayButtonPressed,this));
	
}


void MainMenu::onPlayButtonPressed(cocos2d::Ref* ref)
{
	auto action = TransitionSplitCols::create(1.0f,MainGameScene::createScene());
	Director::getInstance()->replaceScene(action);
}
