#include"TMXLevel.h"
#include"Cat.hpp"
#include"BeeMinion.hpp"
#include"Spike.h"
#include"Trigger.h"
#include"Globals.h"
#include"GameLayer.h"
#include"CutePhsyco.h"
#include "PickUp.hpp"
#include "Health.hpp"

using namespace cocos2d;

TMXLevel::TMXLevel() : mTileMapNode(nullptr), mScaleFactor(1.0f)
{
	
}

TMXLevel::TMXLevel(GameLayer* pGameLayer,const std::string & path,float pLevelScale) 
	:
	mScaleFactor(pLevelScale),
	mParentLayer(pGameLayer)
{
	mTileMapNode = TMXTiledMap::create(path);
	if (!mTileMapNode)
	{
		log("\nError : failed to load tilemap");
		return;
	}
	mTileMapNode->setScale(mScaleFactor);
	this->addChild(mTileMapNode);

	mWidth = mTileMapNode->getMapSize().width;
	mHeight = mTileMapNode->getMapSize().height;
	mTileWidth = mTileMapNode->getTileSize().width;
	mTileHeight = mTileMapNode->getTileSize().height;

	loadColliders();
	loadEnemies();
	loadPositions();
	loadTriggers();
    loadPickUps();
}


void TMXLevel::loadColliders()
{
	//loading colliders
	auto collidersObjects = mTileMapNode->objectGroupNamed("Colliders")->getObjects();
	for (auto colliderObject : collidersObjects)
	{
		auto colliderMap = colliderObject.asValueMap();
		float x = colliderMap["x"].asFloat();
		float y = colliderMap["y"].asFloat();
		float width = colliderMap["width"].asFloat();
		float height = colliderMap["height"].asFloat();
		int tag = colliderMap["Tag"].asInt();

		auto colliderNode = Node::create();
		colliderNode->setContentSize(Size(width, height) * mScaleFactor);
		colliderNode->setPosition(Vec2(x, y) * mScaleFactor);

		auto physicsBody = PhysicsBody::createBox(colliderNode->getContentSize(),PhysicsMaterial(1.0f,0.0f,1.0f));
		physicsBody->setDynamic(false);
		physicsBody->setContactTestBitmask(0xFFFFFFFF);
		
		switch (tag)
		{
		case 0:
			physicsBody->setTag(Globals::TAG_WALL);
			colliderNode->setTag(Globals::TAG_WALL);
			break;
		case 1:
			physicsBody->setTag(Globals::TAG_FLOOR);
			colliderNode->setTag(Globals::TAG_FLOOR);
			break;
		};

		colliderNode->addComponent(physicsBody);

		this->addChild(colliderNode);
	}
}

void TMXLevel::loadPositions()
{
	auto positionObjects = mTileMapNode->objectGroupNamed("Positions")->getObjects();
	
	auto PlayerPosMap = positionObjects.at(0).asValueMap();
	float x = PlayerPosMap["x"].asFloat();
	float y = PlayerPosMap["y"].asFloat();
	mPlayerPosition = Vec2(x, y) * mScaleFactor;

	auto BossPosMap = positionObjects.at(1).asValueMap();
	x = BossPosMap["x"].asFloat();
	y = BossPosMap["y"].asFloat();
	mBossPosition = Vec2(x, y) * mScaleFactor;
}

void TMXLevel::loadEnemies()
{
	//creating enemies
    auto collidersObjects = mTileMapNode->objectGroupNamed("Enemies")->getObjects();
	for (auto colliderObject : collidersObjects)
	{
		auto colliderMap = colliderObject.asValueMap();
		float x = colliderMap["x"].asFloat();
		float y = colliderMap["y"].asFloat();
		int ID = colliderMap["ID"].asInt();
		Node* enemy = nullptr;
		switch (ID)
		{
		case 0: enemy = Cat::create(); break;
		case 1: enemy = Spike::create(); break;
		case 2: enemy = BeeMinion::create(); break;
		case 3:
			auto bomber = CutePhysco::create();
			bomber->setTargetNode(mParentLayer->getPlayerNode());
			bomber->setDestroyOnCollision(true);
			enemy = bomber;
			break;
		};
		enemy->setPosition(cocos2d::Vec2(x,y) * mScaleFactor);
		this->addChild(enemy,100);
	}
    
    //creating tile boundaries for the enemies
    auto tileBoundarys = mTileMapNode->objectGroupNamed("Tile boundaries")->getObjects();
    for (auto tileBoundary : tileBoundarys)
    {
        auto colliderMap = tileBoundary.asValueMap();
        float x = colliderMap["x"].asFloat();
        float y = colliderMap["y"].asFloat();
        float width = colliderMap["width"].asFloat();
        float height = colliderMap["height"].asFloat();
        
        auto boundaryNode = Node::create();
        boundaryNode->setTag(5);
        boundaryNode->setContentSize(Size(width, height) * mScaleFactor);
        boundaryNode->setPosition(Vec2(x, y) * mScaleFactor);
        
        auto physicsBody = PhysicsBody::createBox(boundaryNode->getContentSize(),PhysicsMaterial(1.0f,0.0f,1.0f));
        physicsBody->setDynamic(false);
        physicsBody->setContactTestBitmask(0xFFFFFFFF);
        physicsBody->setCategoryBitmask(0x02);
        physicsBody->setCollisionBitmask(0x01);
        boundaryNode->addComponent(physicsBody);
        
        this->addChild(boundaryNode);
        
    }
    
}


void TMXLevel::loadTriggers()
{
	//creating enemies
	auto collidersObjects = mTileMapNode->objectGroupNamed("Triggers")->getObjects();
	for (auto colliderObject : collidersObjects)
	{
		auto colliderMap = colliderObject.asValueMap();
		float x = colliderMap["x"].asFloat();
		float y = colliderMap["y"].asFloat();
		float width = colliderMap["width"].asFloat();
		float height = colliderMap["height"].asFloat();
		int ID = colliderMap["TriggerID"].asInt();

		auto triggerNode = Trigger::create();
		triggerNode->setContentSize(Size(width, height) * mScaleFactor);
		triggerNode->setPosition(Vec2(x, y) * mScaleFactor);

		auto physicsBody = PhysicsBody::createBox(triggerNode->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
		physicsBody->setDynamic(false);
		physicsBody->setRotationEnable(false);
		physicsBody->setContactTestBitmask(0xFFFFFFFF);
		physicsBody->setCategoryBitmask(0x03);
		physicsBody->setCollisionBitmask(0x02);
		triggerNode->addComponent(physicsBody);

		switch (ID)
		{
		case 0:
			triggerNode->setEventID(Globals::EVENT_JUNGLE_BOSS_AREA);
			triggerNode->setShouldTriggerOnce(true);
			break;
		case 1:
			triggerNode->setEventID(Globals::EVENT_LEVEL_CLEARED);
			break;
		};

		this->addChild(triggerNode);
	}
}

void TMXLevel::loadPickUps()
{
    //creating enemies
    auto collidersObjects = mTileMapNode->objectGroupNamed("PickUps")->getObjects();
    for (auto colliderObject : collidersObjects)
    {
        auto colliderMap = colliderObject.asValueMap();
        float x = colliderMap["x"].asFloat();
        float y = colliderMap["y"].asFloat();
        int ID = colliderMap["ID"].asInt();
        Node* pickUp = nullptr;
        switch (ID)
        {
            case 0: pickUp = Health::create(); break;
        };
        pickUp->setPosition(Vec2(x,y) * mScaleFactor);
        this->addChild(pickUp,100);
    }   
}


TMXLevel::~TMXLevel()
{
}
