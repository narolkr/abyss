#ifndef _INC_GLOBAL_CONSTS_H_
#define _INC_GLOBAL_CONSTS_H_

#include<string>

namespace Globals
{
	//collisions tags
	const int TAG_PLAYER = 2;
	const int TAG_SWORD = 4;
	const int TAG_ENEMY_BOUNDARY = 5;
	const int TAG_PROJECTILE = 10;
	const int TAG_FLOOR = 1;
	const int TAG_WALL = 3;
    const int TAG_SPIKE = 20;
	const int TAG_ENEMY_START = 21;
	const int TAG_ENEMY_END = 60;
	const int TAG_TRIGGER_START = 11;
	const int TAG_TRIGGER_END = 20;
    const int TAG_PICKUP_START = 61;
    const int TAG_PICKUP_END = 90;
    
    //input ID for character states
    const int INPUT_RRUN_STATE = 0;
    const int INPUT_LRUN_STATE = 1;
    const int INPUT_JUMP_STATE = 2;
    const int INPUT_IDEAL_STATE = 3;
    const int INPUT_ATTACK_STATE = 4;
    const int INPUT_DEAD_STATE = 5;


	extern const std::string EVENT_PLAYER_GOT_HIT;
	extern const std::string EVENT_PLAYER_DIED;
	extern const std::string EVENT_LEVEL_CLEARED;
	extern const std::string EVENT_COIN_COLLECTED;
	extern const std::string EVENT_REMOVE_PAUSE_MENU;
	extern const std::string EVENT_ADD_PAUSE_MENU;
	extern const std::string EVENT_EXIT_TO_MENU;
    extern const std::string EVENT_GAME_OVER_MENU;
    extern const std::string EVENT_PLAY_AGAIN_MENU;
	extern const std::string EVENT_JUNGLE_BOSS_AREA;
	extern const std::string EVENT_SPAWN_EXPLOSION;
	extern const std::string EVENT_SPAWN_ORIENTED_EXPLOSION;
	extern const std::string EVENT_SHAKE_SCREEN;

	struct GameData
	{
		static float levelX1;
		static float levelY1;
		static float levelX2;
		static float levelY2;
		static bool isScreenShaking;
	};

	inline bool inTriggerRange(unsigned tag){
		return (tag >= TAG_TRIGGER_START && tag <= TAG_TRIGGER_END);
	}
	inline bool inEnemyRange(unsigned tag){
		return (tag >= TAG_ENEMY_START && tag <= TAG_ENEMY_END);
	}

	enum class EEffectType
	{

	};
}

#endif
