#ifndef _INC_LEVEL_H_
#define _INC_LEVEL_H_

#include"cocos2d.h"
#include<string>

class GameLayer;
class TMXLevel : public cocos2d::Node
{
public:
	
	TMXLevel();
	TMXLevel(GameLayer* pParent,const std::string& path,float pLevelScale = 2.0f);
	~TMXLevel();
	inline float getScaleFactor() { return mScaleFactor; }
	inline int getMapWidth() const { return mWidth; }
	inline int getMapHeight() const { return mHeight; }
	inline int getTileWidth() const { return mTileWidth; }
	inline int getTileHeight() const { return mTileHeight; }
	cocos2d::Vec2 inline getPlayerPosition() { return mPlayerPosition; }
	cocos2d::Vec2 inline getBossPosition() { return mBossPosition; }

private:

	void loadColliders();
	void loadPositions();
	void loadEnemies();
	void loadTriggers();
    void loadPickUps();

	cocos2d::TMXTiledMap* mTileMapNode;
	cocos2d::Vec2 mPlayerPosition;
	cocos2d::Vec2 mBossPosition;
	int mWidth, mHeight;
	int mTileWidth, mTileHeight;
	float mScaleFactor;
	GameLayer* mParentLayer;
};

#endif
